#include "pch.h"
#include "Actor.h"
#include "preDefines.h"
#include "World.h"
#include "SceneComp.h"
#include "AniInfo.h"

#include "MainScene.h"

#include "BarComponent.h"
#include "MovementComp.h"
#include "FarmerComp.h"
#include "InputKeyComp.h"
#include "ProjectileC.h"
#include "GoalComp.h"
#include "AnimalComp.h"
#include "WeaponComp.h"

#include "animController.h"
#include "FarmerCharactorNode.h"
#include "CowCharactorNode.h"
#include "NoChangeAnimController.h"

using namespace ax;

Vec2 getPhysicsBodySize(ECharName charName);


Actor* Spawn_Farmer(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->NewActor();
    
    actor->mActorName = "Farmer";
    actor->mActorType = ActorType::Farmer;
    actor->setPosition(worldPos);

   
    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNodeWithPhysics(Vec2(16, 16));
    // auto root    = sceneComp->NewNode();
    root->getPhysicsBody()->setContactTestBitmask(0xFFFFFFF0);
    root->getPhysicsBody()->setCollisionBitmask(false);
    root->getPhysicsBody()->setCategoryBitmask(false);
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    //컴포넌트 등록
    auto moveComp = new MovementComp(actor);
    auto inputkey = new InputKeyComp(actor);
    auto Farmer    = new FarmerComp(actor);
    auto goalComp = new GoalComp(actor);
    auto weaponComp = new WeaponComp(actor);
    weaponComp->addGun();
    Farmer->mCharAnimController = FarmerCharactorNode::create(actor);
    /*
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Farmer));
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    
    ax::Sprite* node = SpawnActor_OnScene(root, ECharActName::Idle, ECharDir::Face, Vec2(0, 0));

    auto comp = animController::create(actor);
    node->addComponent(comp);
    */
    
    /*
    /////////
    //auto noded = Sprite::createWithSpriteFrame(Farmer->mCharAnimController->mCurrentAnimInfo->animation->getFrames().front()->getSpriteFrame());
    //auto pol = ax::PolygonInfo::PolygonInfo(Farmer->mCharAnimController->mCurrentAnimInfo->animation->getFrames().front()->getSpriteFrame()->getPolygonInfo());
//    auto pol2 = AutoPolygon::AutoPolygon("");
    */
    auto dr   = DrawNode::create();
    dr->setPosition(actor->getPosition());
    root->addChild(dr);
    /*
    //dr->drawPoly
    //dr->drawPolygon(, pol.getVertCount(),1.f, Color4B::RED);
    //auto body = ax::PhysicsBody::createEdgePolygon(&pos, pol.getVertCount());
    ////////////////
    */
    ax::Sprite* Hnode = SpawnHPbar_OnScene(root, Vec2(0, 16));
    auto hcomp = BarComponent::create(actor);
    Hnode->addComponent(hcomp);
    

    return actor;
}
Actor* Spawn_Cow(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->NewActor();

    actor->mActorName = "Cow";
    actor->mActorType = ActorType::Farmer;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNodeWithPhysics(Vec2(16, 16));
    
    // auto root    = sceneComp->NewNode();
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    // 컴포넌트 등록
    auto moveComp = new MovementComp(actor);
    auto Animal   = new AnimalComp(actor);
    auto goalComp = new GoalComp(actor);
    /*
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Farmer));
    root->setPosition(actor->getPosition());
    parent->addChild(root);

    ax::Sprite* node = SpawnActor_OnScene(root, ECharActName::Idle, ECharDir::Face, Vec2(0, 0));

    auto comp = animController::create(actor);
    node->addComponent(comp);
    */
    Animal->mCharAnimController = CowCharactorNode::create(actor);
    ax::Sprite* Hnode           = SpawnHPbar_OnScene(root, Vec2(0, 16));
    auto hcomp                  = BarComponent::create(actor);
    Hnode->addComponent(hcomp);
    /*
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Farmer));
    root->setPosition(actor->getPosition());
    parent->addChild(root);

    ax::Sprite* node = SpawnActor_OnScene(root, ECharActName::Idle, ECharDir::Face, Vec2(0, 0));

    auto comp = animController::create(actor);
    node->addComponent(comp);
    */
    actor->mMoveComp->setSpeed(30.f);
    return actor;
}
Actor* Spawn_Bullet(ax::Node* parent, Vec2 worldPos, Actor* archor, Vec2 targetPos)
{
    static unsigned int i = 0;

    Actor* actor      = World::get()->NewBullet();
    actor->mActorType = ActorType::Ball;
    actor->mActorName = "Ball";
    actor->mActorName += std::to_string(i);
    i++;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    //getPhysicsBodySize(ECharName::Ball
    sceneComp->mRootNode = sceneComp->NewPhysicsNode("Ball", Vec2(32, 32));
   //
    //sceneComp->addChild(physicsNode);
    //sceneComp->mRootNode = physicsNode;
    //sceneComp->setParent(parent);
    parent->addChild(sceneComp->mRootNode.get());
    //parent->addChild(physicsNode);
    sceneComp->mRootNode->setPosition(worldPos);
    sceneComp->mRootNode->getPhysicsBody()->setDynamic(true);
    sceneComp->mRootNode->getPhysicsBody()->setRotationEnable(false);
    sceneComp->mRootNode->getPhysicsBody()->getShape(0)->setMaterial(PhysicsMaterial(0,0,0));
    //sceneComp->mRootNode->getPhysicsBody()
    // Component 안에서 자동으로 적용됨
    //auto moveComp      = new MovementComp(actor);
    auto projectile    = new ProjectileC(actor, targetPos);
    projectile->archor = archor;

    auto r = sceneComp->CreateNode_withNoChangeAnimController("Body", ECharName::Ball, ECharActName::Idle, ECharDir::Face);
    projectile->mAnimController = r;
    




    return actor;
}
/*
Actor* Spawn_Animal(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor      = World::get()->NewActor();
    actor->mActorName = "Animal";
    actor->mActorType = ActorType::Animal;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    // 컴포넌트 등록
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Animal));
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    return actor;
}

Actor* Spawn_TownHall(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->MakeObject("TownHall");
    actor->setPosition(worldPos);

    ax::Sprite* node = SpawnActor_OnScene(parent, actor, ECharName::TownHall, ECharActName::Idle, ECharDir::Face);
    return actor;
}



Actor* Spawn_Torch(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->MakeObject("Torch");
    actor->setPosition(worldPos);

    ax::Sprite* node = SpawnActor_OnScene(parent, actor, ECharName::Torch, ECharActName::Idle, ECharDir::Face);
    return actor;
}

Actor* Spawn_Ball(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->MakeObject("Ball.png");
    actor->setPosition(worldPos);

    ax::Sprite* node = SpawnActor_OnScene(parent, actor, ECharName::Ball, ECharActName::Move, ECharDir::Face);
    return actor;
}

Actor* Spawn_Mouse(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor      = new Actor;
    actor->mActorType = ActorType::Mouse;
    actor->mActorName = "MOUSE";
    actor->setPosition(worldPos);

    World::get()->mUpdateList_Extra.push_back(actor);

    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNodeWithPhysics(Vec2(16, 16));
    root->setPosition(actor->getPosition());
    parent->addChild(root);

    
    DrawNode* node = DrawNode::create();
    // node->retain();
    // node->setPosition(Vec2(0, 0));
    node->drawRect(Vec2(-7, -7), Vec2(7, 7), Color4F::BLUE);
    root->addChild(node);

    return actor;
}



//test log in Update
if (mTimer > 1.0f)
    {
        mTimer = 0;
        AXLOG("debug Test");
    }
*/




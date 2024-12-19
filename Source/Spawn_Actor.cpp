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
#include "SensorComp.h"

#include "animController.h"
#include "FarmerCharactorNode.h"
#include "CowCharactorNode.h"
#include "CoinCharactorNode.h"
#include "NoChangeAnimController.h"
//#include "box2d/box2d.h"
using namespace ax;

Vec2 getPhysicsBodySize(ECharName charName);


Actor* Spawn_Farmer(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->NewActor();
    
    actor->mActorName = "Farmer";
    actor->mActorType = ActorType::Farmer;
    actor->mTagname   = Actor::Player;
    actor->setPosition(worldPos);

   
    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNodeWithPhysics(Vec2(16, 16));
    // auto root    = sceneComp->NewNode();
    root->getPhysicsBody()->setContactTestBitmask(0xFFFFFFF0);
    root->getPhysicsBody()->setCollisionBitmask(false);
    root->getPhysicsBody()->setCategoryBitmask(false);
    root->getPhysicsBody()->setGravityEnable(false);
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    //sensor node
    
    auto Sensornode = sceneComp->NewNode("Sensor");
    sceneComp->mSensorNode = Sensornode;
    sceneComp->mSensorNode -> setPosition(actor->getPosition());
    auto body = ax::PhysicsBody::createCircle(300);
    body->setContactTestBitmask(0xFFFFFFFF);
    Sensornode->setPhysicsBody(body);
    body->setDynamic(true);
    auto drawNode = ax::DrawNode::create();
    Vec2 pos(0, 0);
    drawNode->setPosition(Vec2(0, 0));
    drawNode->drawCircle(pos, 300, 0, 32, 5, ax::Color4F::BLUE);
    
    Sensornode->addChild(drawNode);
    parent->addChild(Sensornode);
    //컴포넌트 등록
    auto moveComp = new MovementComp(actor);
    auto inputkey = new InputKeyComp(actor);
    auto Farmer    = new FarmerComp(actor);
    auto goalComp = new GoalComp(actor);
    auto weaponComp = new WeaponComp(actor);
    auto sensorComp = new SensorComp(actor);
    weaponComp->addGun();
    weaponComp->addGun2();
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
    actor->mActorType = ActorType::Cow;
    actor->mTagname   = Actor::Enemy;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNodeWithPhysics(Vec2(16, 16));
    root->getPhysicsBody()->setGravityEnable(false);
    //sceneComp->mRootNode->getPhysicsBody()->setDynamic(true);
    //sceneComp->mRootNode->getPhysicsBody()->setRotationEnable(false);
    //sceneComp->mRootNode->getPhysicsBody()->getShape(0)->setMaterial(PhysicsMaterial(0, 0, 1));
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
    actor->mTagname = Actor::pBullet;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    //getPhysicsBodySize(ECharName::Ball
    sceneComp->mRootNode = sceneComp->NewPhysicsNode("Ball", Vec2(16, 16));
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
Actor* Spawn_Bullet2(ax::Node* parent, Vec2 worldPos, Actor* archor, Vec2 targetPos)
{
    static unsigned int i = 0;

    Actor* actor      = World::get()->NewBullet();
    actor->mActorType = ActorType::Ball;
    actor->mActorName = "Ball";
    actor->mActorName += std::to_string(i);
    i++;
    actor->mTagname = Actor::pBullet;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    auto projectile2     = new ProjectileC2(actor, targetPos);
    sceneComp->mRootNode = sceneComp->NewPhysicsNode("Ball", Vec2(32, 32));
    
    parent->addChild(sceneComp->mRootNode.get());
    sceneComp->mRootNode->setPosition(worldPos);
    sceneComp->mRootNode->getPhysicsBody()->setDynamic(true);
    sceneComp->mRootNode->getPhysicsBody()->setRotationEnable(false);
    Vec2 a = targetPos-worldPos;
    a.normalize();
    float x = (a.getAngle() * 180) / M_PI;
    sceneComp->mRootNode->setRotation(-x-(90));
    sceneComp->mRootNode->getPhysicsBody()->getShape(0)->setMaterial(PhysicsMaterial(0, 0, 0));
    sceneComp->mRootNode->setScale(0.5f);
    // Component 안에서 자동으로 적용됨
    projectile2->archor = archor;
    projectile2->mCharAnimController = CoinCharactorNode::create(actor);
    return actor;
}
Actor* SetCamp(Actor* actor)
{
    return nullptr;
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




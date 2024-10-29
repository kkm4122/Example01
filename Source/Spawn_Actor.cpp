#include "pch.h"
#include "preDefines.h"
#include "World.h"
#include "Actor.h"
#include "AniInfo.h"
#include "preDefines.h"
#include "MainScene.h"
#include "SceneComp.h"
#include "animController.h"
#include "BarComponent.h"
#include "MovementComp.h"
using namespace ax;

//Vec2 getPhysicsBodySize(ECharName charName);

Actor* Spawn_Farmer1(MainScene* parent, Vec2 worldPos)
{
    Actor* actor = parent->NewActor();

    actor->mActorName = "Farmer";
    actor->mActorType = ActorType::Farmer;
    actor->setPosition(worldPos);

    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNode();
    //auto root    = sceneComp->NewNode();
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    // 컴포넌트 등록
    /*
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Farmer));
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    */
    ax::Sprite* node = SpawnActor_OnScene(root, ECharActName::Idle, ECharDir::Face, Vec2(0, 0));

    auto comp = animController::create(actor);
    node->addComponent(comp);
    //root->addChild(node);
    ax::Sprite* Hnode = SpawnHPbar_OnScene(root, Vec2(0, 16));

    auto hcomp = BarComponent::create(actor);
    Hnode->addComponent(hcomp);
    //root->addChild(Hnode);
    return actor;
}
Actor* Spawn_Farmer(ax::Node* parent, Vec2 worldPos)
{
    Actor* actor = World::get()->NewActor();
    
    actor->mActorName = "Farmer";
    actor->mActorType = ActorType::Farmer;
    actor->setPosition(worldPos);

   
    auto sceneComp = new SceneComp(actor);
    auto root      = sceneComp->CreateRootNode();
    // auto root    = sceneComp->NewNode();
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    //컴포넌트 등록
    auto moveComp = new MovementComp(actor);
    /*
    auto root = sceneComp->CreateRootNodeWithPhysics(getPhysicsBodySize(ECharName::Farmer));
    root->setPosition(actor->getPosition());
    parent->addChild(root);
    */
    ax::Sprite* node = SpawnActor_OnScene(root, ECharActName::Idle, ECharDir::Face, Vec2(0, 0));

    auto comp = animController::create(actor);
    node->addComponent(comp);

    ax::Sprite* Hnode = SpawnHPbar_OnScene(root, Vec2(0, 16));
    
    auto hcomp = BarComponent::create(actor);
    Hnode->addComponent(hcomp);
    

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




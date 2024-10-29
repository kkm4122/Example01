#include "pch.h"
#include "SceneComp.h"
#include "Actor.h"
#include "MainScene.h"

using namespace ax;

const std::string SceneComp::COMPONENT_NAME = "SceneComp";


SceneComp::SceneComp(Actor* actor) : IActorComponent(actor)
{
    mCompName         = COMPONENT_NAME;
    actor->mSceneComp = this;
    
}

void SceneComp::update(float delta)
{
    if (mRootNode.isNotNull())
        mRootNode->setPosition(mActor->getPosition());
}

void SceneComp::MessageProc(ActorMessage& msg)
{
    //Actor* other = msg.sender;

    // 같은 Projectile 형태이면 충돌처리하지 않는다.
    //     if (msg.sender->mUnitComp->getName() == ProjectileComp::COMPONENT_NAME)
    //   if (msg.msgType == ActorMessage::Contacted)
}


SceneComp::~SceneComp()
{
    mRootNode->release();
}

ax::Node* SceneComp::NewNode(NodeType type)
{
    ax::Node* node     = ax::Node::create();
    Nodedata* nodeData = CreateNodedata(mActor, type);

    node->setUserData(nodeData);
    //mRootNode = node;
    return node;
}

ax::Node* SceneComp::CreateRootNode()
{
    ax::Node* node = NewNode();
    mRootNode      = node;
    return node;
}

Nodedata* SceneComp::CreateNodedata(Actor* actor, NodeType type)
{
    Nodedata* nodedata  = new Nodedata;
    nodedata->mActor    = actor;
    nodedata->mNodeType = type;
    return nodedata;
}


#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "World.h"
#include "MovementComp.h"
#include "Aniinfo.h"
#include "CharAnimController.h"
#include "SceneComp.h"

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


ax::Node* SceneComp::NewNode(std::string_view name)
{
    ax::Node* node = ax::Node::create();
    node->setName(name);
    node->setUserData(CreateNodedata(mActor, name));
    return node;
}
ax::Node* SceneComp::NewAnimNode(std::string_view name,
                                 ECharName charName,
                                 ECharActName actionName,
                                 ECharDir dir,
                                 INodeAnimationController* controller = nullptr)
{
    AnimInfo& info = FindAnimInfo(charName, actionName, dir);
    info.CreateAnimation();

    auto node = Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());
    node->setName(name);
    node->setUserData(CreateNodedata(mActor, name));

    if (controller == nullptr)
        controller = NoChangeAnimController::create(mActor);

    node->addComponent(controller);
    controller->ChangeAnimation(&info, true);

    AddController(controller);

    return node;
}

ax::Node* SceneComp::CreateRootNode()
{
    ax::Node* node = NewNode("RootNode");
    mRootNode      = node;
    return node;
}

Nodedata* SceneComp::CreateNodedata(Actor* actor, std::string_view name)
{
    Nodedata* nodedata  = new Nodedata;
    nodedata->mActor    = actor;
    nodedata->mNodeName = name;
    return nodedata;
}

void SceneComp::AddController(IActorNodeController* anc)
{
    for (auto con : mControllerList)
    {
        if (!con)
        {
            con = anc;
            return;
        }
    }
    mControllerList.push_back(anc);
}

void SceneComp::RemoveController(IActorNodeController* anc)
{
    for (auto con : mControllerList)
    {
        if (con == anc)
        {
            con = nullptr;
            return;
        }
    }
}

IActorNodeController* SceneComp::getController(std::string_view name)
{
    for (auto con : mControllerList)
    {
        if (con->getName() == name)
            return con;
    }
    return nullptr;
}


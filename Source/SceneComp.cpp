#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "World.h"
#include "MovementComp.h"
#include "Aniinfo.h"
#include "CharAnimController.h"
#include "SceneComp.h"
#include "NoChangeAnimController.h"
using namespace ax;

const std::string SceneComp::COMPONENT_NAME = "SceneComp";


SceneComp::SceneComp(Actor* actor) : IActorComponent(actor)
{
    mCompName         = COMPONENT_NAME;
    actor->mSceneComp = this;
    mNodedata.mActor  = actor;

    mRootNode = NewNode("Root");
    mRootNode->setPosition(actor->getPosition());
}

void SceneComp::update(float delta)
{
    if (mRootNode.isNotNull())
    {
        if (mActor->mActorType == ActorType::Ball)
        {
            mActor->setPosition(mRootNode->getPosition());
            return;
        }
        mRootNode->setPosition(mActor->getPosition());
    }
    if (mSensorNode.isNotNull())
    {
        mSensorNode->setPosition(mActor->getPosition());
    }
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
    if (mRootNode.isNotNull())
        mRootNode->removeFromParent();
}


ax::Node* SceneComp::NewNode(std::string_view name)
{
    ax::Node* node = ax::Node::create();
    node->setName(name);
    node->setUserData(CreateNodedata(mActor, name));

    return node;
}
ax::Node* SceneComp::NewPhysicsNode(std::string_view name, Vec2 body_size)
{
    ax::Node* node = NewNode(name);

    //auto ma = ax::PhysicsMaterial()
    //auto body = ax::PhysicsBody::createPolygon();
   
    auto body = ax::PhysicsBody::createCircle(body_size.x/2);
    //auto bodyp = AutoPolygon::generatePolygon("");
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);
    node->setPhysicsBody(body);
    auto bodysize = body_size /2;
    auto drawNode = ax::DrawNode::create();
    Vec2 pos(0, 0);
    drawNode->setPosition(Vec2(0, 0));
    drawNode->drawCircle(pos, body_size.x/2, 0, 16, 5, ax::Color4F::RED);
    //drawNode->drawRect(-bodysize, bodysize, ax::Color4F::RED);
    drawNode->setGlobalZOrder(1.f);
    node->addChild(drawNode);

    return node;
}
ax::Node* SceneComp::NewPhysicsRectNode(std::string_view name, Vec2 body_size)
{
    ax::Node* node = NewNode(name);

    auto body = ax::PhysicsBody::createBox(body_size);
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);
    node->setPhysicsBody(body);
    
    auto drawNode = ax::DrawNode::create();
    Vec2 pos(0, 0);
    drawNode->setPosition(Vec2(0, 0));
    drawNode->drawRect(pos,body_size, ax::Color4F::RED);
    // drawNode->drawRect(-bodysize, bodysize, ax::Color4F::RED);
    drawNode->setGlobalZOrder(1.f);
    node->addChild(drawNode);
    return node;
}
ax::Node* SceneComp::NewPhysicsCircleNode(std::string_view name, float radius)
{
    ax::Node* node = NewNode(name);

    // auto ma = ax::PhysicsMaterial()
    // auto body = ax::PhysicsBody::createPolygon();

    auto body = ax::PhysicsBody::createCircle(radius);
    // auto bodyp = AutoPolygon::generatePolygon("");
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);
    node->setPhysicsBody(body);
    auto bodysize = radius;
    auto drawNode = ax::DrawNode::create();
    Vec2 pos(0, 0);
    drawNode->setPosition(Vec2(0, 0));
    drawNode->drawCircle(pos, radius, 0, 16, 5, ax::Color4F::RED);
    // drawNode->drawRect(-bodysize, bodysize, ax::Color4F::RED);
    drawNode->setGlobalZOrder(1.f);
    node->addChild(drawNode);

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
    //auto pol  = ax::PolygonInfo::PolygonInfo(info.animation->getFrames().front()->getSpriteFrame()->getPolygonInfo());
    
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

ax::Node* SceneComp::CreateRootNodeWithPhysics(Vec2 body_size)
{
    ax::Node* node = NewPhysicsNode("RootNode", body_size);
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





NoChangeAnimController* SceneComp::CreateNode_withNoChangeAnimController(std::string_view name,
                                                                         ECharName charName,
                                                                         ECharActName actionName,
                                                                         ECharDir dir)
{
    auto controller = NoChangeAnimController::create(mActor);
    auto node       = NewAnimNode(name, charName, actionName, dir, controller);
    mRootNode->addChild(node);
    // NoChangeAnimController* comp = (NoChangeAnimController*)
    // node->getComponent(NoChangeAnimController::COMPONENT_NAME);
    return controller;
}



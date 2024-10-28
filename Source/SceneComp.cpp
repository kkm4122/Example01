
#include "SceneComp.h"
#include "Actor.h"
#include "MainScene.h"


SceneComp::SceneComp(Actor* actor) : IActorComponent(actor)
{
    //mCompName         = COMPONENT_NAME;
    actor->mSceneComp = this;
    mRootNode         = ax::Node::create();
    //mRootNode->retain();
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

void SceneComp::update_world(float delta)
{
    //월드에서 액션관리
    Velocity = ax::Vec2(0, 0);
    if (IsTargetForce)
    {
        Do_TargetForce();
    }
    Velocity.normalize();
    Vec2 moveDir = (Velocity * delta * mspeed);
    mPosition += moveDir;
    mRootNode->setPosition(mPosition);
    
    // DirV =이동거리
    //  값이 너무 작을 경우,
    //  앞을 처다보는 현상이 있음.

   
}


void SceneComp::setTarget(ax::Vec2 target)
{
    IsTargetForce   = true;
    mtargetDir         = target - mPosition;
    mWorldTargetPos = target;
}

ax::Vec2 SceneComp::Vec2DNormalized(ax::Vec2 target)
{
    ax::Vec2 vec = target;

    double vector_length = vec.length();

    if (vector_length > 2)
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}

bool SceneComp::IsArrived()
{
    if (1.0 > length(mWorldTargetPos, mPosition))
    {
        // mActor->mBehavior = Idle;
        return true;
    }
    return false;
}

void SceneComp::Do_TargetForce()
{
    if (IsArrived())
    {
        IsTargetForce = false;
    }
    else
        Velocity +=  Vec2DNormalized(mtargetDir);
}

double SceneComp::length(ax::Vec2 v1, ax::Vec2 v2)
{
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;

    return sqrt(dx * dx + dy * dy);
}

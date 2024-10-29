#pragma once
#include "IActorComponent.h"
#include "Actor.h"
#include "preDefines.h"

//노드에서 컴포넌트를 상속받아서 장착할수있음
//컴포넌트 상속받으면
enum class NodeType
{
    None,  // 디버깅용(nullptr느낌)
    Root,  // 노드 관리
    /*
        Node
           -Attack
           -body
    */
    Attack,  // 공격 범위
    Body,    // 피격 범위
};
struct Nodedata
{
    Actor* mActor;
    // StatusInfo* mStatusInfo;
    NodeType mNodeType;
};
class SceneComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;  // 컴포넌트 분류

    SceneComp(Actor* actor);  // 생성할때 actor 와 상호참조

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;

    ~SceneComp();
    // 에니메이션 및 스프라이트
    ax::Node* NewNode(NodeType type = NodeType::Root);
    ax::Node* NewPhysicsNode(Vec2 body_size);
    ax::Node* NewAnimNode(ECharName charName,
                          ECharActName action,
                          ECharDir dir, animController* controller = nullptr);
    
    /*
      RootNode  관련
    */
    ax::Node* CreateRootNode();
    Nodedata* CreateNodedata(Actor* actor, NodeType type);
    void addChild(ax::Node* node) { mRootNode->addChild(node); }
    // 좌표 이동계
    ax::Vec2 mtargetDir = ax::Vec2(200, 200);
    ax::Vec2 Velocity;
    bool IsTargetForce = false;
    double mspeed      = 50.f;
    ax::Vec2 mWorldTargetPos;
    ax::Vec2 mPosition;

public:
    

    int MaxHP = 200;
    int currentHP = 100;
    int getMax() const { return MaxHP; }
    int getCur() const { return currentHP; }
    animController* mExComp = nullptr;
    // BarComponent* mBarComp = nullptr;
    BarComponent* hpComp = nullptr;

    

    //void addChild(ax::Node* node) { mRootNode->addChild(node); }

    Ptr<ax::Node> mRootNode;

};

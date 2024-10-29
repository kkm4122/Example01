#pragma once
#include "IActorComponent.h"
#include "Actor.h"
#include "preDefines.h"
#include "StatusInfo.h"

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
    StatusInfo* mStatusInfo;
    std::string_view mNodeName;
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
    ax::Node* NewNode(std::string_view name);
    ax::Node* NewPhysicsNode(Vec2 body_size);
    ax::Node* NewAnimNode(std::string_view name,
                          ECharName charName,
                          ECharActName actionName,
                          ECharDir dir,
                          INodeAnimationController* controller);
    ;
    
    
      //RootNode  관련
    ax::Node* getRootNode() { return mRootNode.get(); }
    Nodedata* getRootNodedata() { return (Nodedata*)mRootNode->getUserData(); }
    ax::Node* getAttackNode()   { return mAttackNode.get();}
    void addChild(ax::Node* node) { mRootNode->addChild(node); }
    
    ax::Node* CreateRootNode();
    Nodedata* CreateNodedata(Actor* actor, std::string_view name);
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
public:
    void AddController(IActorNodeController* anc);//mControllerList에 컨트롤러 추가 컨트롤러들은 독자적으로 작동하기때문에
    void RemoveController(IActorNodeController* anc);//따로 관리를 하지 않아도됨
    IActorNodeController* getController(std::string_view name);
public:
    Ptr<ax::Node> mRootNode;
    Ptr<ax::Node> mAttackNode;
    std::vector<IActorNodeController*> mControllerList;

};

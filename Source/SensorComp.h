#pragma once

#include "preDefines.h"
#include "IActorComponent.h"

//노드에서 컴포넌트를 상속받아서 장착할수있음
//컴포넌트 상속받으면
class SensorComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

    // bool IsTargetForce = false;

public:
    SensorComp(Actor* actor);
    ~SensorComp();

    void update(float delta);
    virtual void MessageProc(ActorMessage& msg) override;
    void addEnemy(ActorMessage& msg);
    void deleteEnemy(ActorMessage& msg);
    
    

public:
    std::vector<Actor*> mAimList;
};

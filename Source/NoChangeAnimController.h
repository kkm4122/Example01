#pragma once
#include "axmol.h"
#include "preDefines.h"




/*
    예전 Actor 에서
    그래픽과 관련된 행동은 여기서 처리한다.


*/

class animController : public ax::Component
{
public:
    static animController* create(Actor* ac);
    animController();
    ~animController();

    public:
    virtual void update(float delta) override;
        
    void update_animChar(float delta);
    Actor* mActor;
    
        
    AnimInfo* mCurrentAnimInfo = nullptr;
};

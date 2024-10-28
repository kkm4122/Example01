#pragma once
#include "axmol.h"
#include "preDefines.h"



class animController : public ax::Component
{
public:
    static animController* create(Actor* ac);
    animController();
    ~animController();

    public:
    virtual void update(float delta) override;
        void animationUpdate(float delta);
    Actor* mActor;
    
        
    AnimInfo* mCurrentAnimInfo = nullptr;
};

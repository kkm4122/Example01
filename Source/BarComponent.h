#pragma once
#include "axmol.h"
//#include "Aniinfo.h"
#include "preDefines.h"
class SceneComp;


class BarComponent : public ax::Component
{
public:
    static BarComponent* create(Actor* ac);
    BarComponent();
    ~BarComponent();
    
    Actor* mActor;
    virtual void update(float delta) override;
    //void HPupdate();
    void ChangeAnimationByIndex( int idx);


    int hp = 0;
    //AnimInfo* mCurrentAnimInfo = nullptr;
};

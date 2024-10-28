#include "BarComponent.h"
#include "SceneComp.h"

BarComponent* BarComponent::create(Actor* ac)
{
    BarComponent* body = new (std::nothrow) BarComponent();
    body->mActor      = ac;
    
    if (body->init())
    {
        body->autorelease();
        return body;
    }
    
    AX_SAFE_DELETE(body);
    return nullptr;
}

BarComponent::BarComponent() {}

BarComponent::~BarComponent() {}

void BarComponent::update(float delta)
{
    if (hp != mActor->getCur())
    {
        hp             = mActor->getCur();
        int mhp        = mActor->getMax();
        int chp        = hp * 10;
        int idx        = 10 - (chp / mhp);
        AnimInfo& info = HpBar(idx);
        Change_CharAnim(getOwner(), info);
    }

}



void BarComponent::ChangeAnimationByIndex(int idx) {}





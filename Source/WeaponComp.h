#pragma once
#include "preDefines.h"
#include "IActorComponent.h"
#include "IDsystem.h"

class WeaponComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

    bool IsTargetForce = false;

public:
    WeaponComp(Actor* actor);
    ~WeaponComp();

    void update(float delta);
    virtual void MessageProc(ActorMessage& msg) override;

    std::vector<Weapon*> mWeaponList;
};

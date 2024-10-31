#pragma once
#include "preDefines.h"
#include "INodeAnimationController.h"
#include "UnitDefines.h"


class CowCharactorNode : public INodeAnimationController
{
public:
    const static std::string COMPONENT_NAME;

    static CowCharactorNode* create(Actor* ac);

    CowCharactorNode() { _name = COMPONENT_NAME; }
    ~CowCharactorNode() {}
    virtual bool init() override;
    virtual void update(float delta) override;
   
    ECharDir CalcAniDir(Vec2 dir);

public:
    E_UnitPose mUnitPose = E_UnitPose::None;
};

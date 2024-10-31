#pragma once
#include "preDefines.h"
#include "INodeAnimationController.h"
#include "UnitDefines.h"


class FarmerCharactorNode : public INodeAnimationController
{
public:
    const static std::string COMPONENT_NAME;

    static FarmerCharactorNode* create(Actor* ac);
    FarmerCharactorNode() { _name = COMPONENT_NAME; }
    ~FarmerCharactorNode() {}
    virtual bool init() override;
    virtual void update(float delta) override;

public:
    E_UnitPose mUnitPose = E_UnitPose::None;
};

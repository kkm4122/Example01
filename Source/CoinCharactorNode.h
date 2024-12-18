#pragma once
#include "preDefines.h"
#include "INodeAnimationController.h"
#include "UnitDefines.h"

class CoinCharactorNode : public INodeAnimationController
{
public:
    const static std::string COMPONENT_NAME;
    CREATE_FUNC(CoinCharactorNode);
    static CoinCharactorNode* create(Actor* ac);

    CoinCharactorNode() { _name = COMPONENT_NAME; }
    ~CoinCharactorNode() {}
    virtual bool init() override;
    virtual void update(float delta) override;

    ECharDir CalcAniDir(Vec2 dir);

public:
    E_UnitPose mUnitPose = E_UnitPose::None;
};

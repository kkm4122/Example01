#pragma once
#include "INodeAnimationController.h"
#include "NoChangeAnimController.h"
class Actor;


class CharAnimController : public INodeAnimationController
{
public:
    const static std::string COMPONENT_NAME;

    static CharAnimController* create(Actor* ac);
    CharAnimController() { _name = COMPONENT_NAME; }
    ~CharAnimController() {}

    virtual bool init() override { return true; };
    virtual void update(float delta) override;

public:
};

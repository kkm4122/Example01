#pragma once
#include "INodeAnimationController.h"

class Actor;

class NoChangeAnimController : public INodeAnimationController
{
public:
    const static std::string COMPONENT_NAME;

    static NoChangeAnimController* create(Actor* ac);
    NoChangeAnimController() { _name = COMPONENT_NAME; }
    ~NoChangeAnimController() {}

    virtual bool init() override { return true; };
    virtual void update(float delta) override{};

public:
};

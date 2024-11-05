#pragma once
#include "Goal.h"


class A_RandomMoving : public Goal_Composite
{
public:
    Vec2 mOrgPosition;
    bool dir = true;

public:
    static const char* GOAL_NAME;
    const char* getName() override { return GOAL_NAME; }

    A_RandomMoving(Actor* pBot);

    void Start();
    int Do();
    bool Next();
};

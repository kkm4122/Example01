#pragma once
#include "Goal.h"

class A_WaitTime : public Goal
{
public:
    double mWaitTime;

public:
    static const char* GOAL_NAME;
    const char* getName() override { return GOAL_NAME; }

    A_WaitTime(Actor* pBot, float wait_time);

    void Start();
    int Do();
    void End();
};

#pragma once
#include "Goal.h"


class A_GotoTarget : public Goal
{
public:
    Vec2 m_Dest;

    double m예상시간;

    // 문제가 발생했느냐?
    bool isStuck() const;

public:
    static const char* GOAL_NAME;
    const char* getName() override { return GOAL_NAME; }

    A_GotoTarget(Actor* pBot, Vec2 dest);

    void Start();
    int Do();
    void End();
};

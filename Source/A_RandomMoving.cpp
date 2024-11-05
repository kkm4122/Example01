#include "pch.h"
#include "A_RandomMoving.h"
#include "Actor.h"
#include "MovementComp.h"
#include "A_GotoTarget.h"
//#include "A_WaitTime.h"
#include "A_RandomMoving.h"


const char* A_RandomMoving::GOAL_NAME = "A_RandomMoving";

A_RandomMoving::A_RandomMoving(Actor* pBot) : Goal_Composite(pBot)
{
    mOrgPosition = pBot->getPosition();
}

void A_RandomMoving::Start()
{
    m_Status = Goal::active_t;

    Vec2 gg;
    gg.x = std::rand() % 30;
    gg.y = std::rand() % 30;

    dir ^= dir;
    if (dir)
    {
        gg.x *= -1.f;
        gg.y *= -1.f;
    }

   // AddSubgoal(new A_WaitTime(m_pOwner, 2.f));
    AddSubgoal(new A_GotoTarget(m_pOwner, mOrgPosition + gg));
}
int A_RandomMoving::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();
    if (m_Status == Goal::completed_t && Next())
        Start();

    return m_Status;
}


bool A_RandomMoving::Next()
{
    return true;
}

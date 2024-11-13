#include "pch.h"
#include "A_WaitTime.h"
#include "Actor.h"
#include "MovementComp.h"

const char* A_WaitTime::GOAL_NAME = "A_WaitTime";

A_WaitTime::A_WaitTime(Actor* pBot, float wait_time) : Goal(pBot), mWaitTime(wait_time) {}

void A_WaitTime::Start()
{
    m_Status = Goal::active_t;
    m_pOwner->mMoveComp->Start경과시간();
}

int A_WaitTime::Do()
{
    If_Inactive_Start();

    // 문제가 발생했다면
    if (m_pOwner->mMoveComp->m경과시간 > mWaitTime)
    {
        m_Status = Goal::completed_t;
        return m_Status;
    }

    return m_Status;
}

void A_WaitTime::End()
{
    m_pOwner->mMoveComp->Stop경과시간();
    __super::End();
}


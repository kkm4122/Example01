#include "pch.h"
#include "A_GotoTarget.h"
#include "Actor.h"
#include "MovementComp.h"

const char* A_GotoTarget::GOAL_NAME = "A_GotoTarget";

A_GotoTarget::A_GotoTarget(Actor* pBot, Vec2 dest)
    : Goal(pBot), m_Dest(dest), m예상시간(0.0)
{}



bool A_GotoTarget::isStuck() const
{
    if (m예상시간 < m_pOwner->mMoveComp->m경과시간)
    {
        AXLOG("충분한 시간에 도착하지 못했음..!!");
        return true;
    }

    return false;
}


void A_GotoTarget::Start()
{
    m_Status = Goal::active_t;

    m_pOwner->mMoveComp->setTarget(m_Dest);
    m예상시간 = m_pOwner->mMoveComp->getTimeToReachTarget();
    m_pOwner->mMoveComp->Start경과시간();
}

int A_GotoTarget::Do()
{
    If_Inactive_Start();

    // 문제가 발생했다면
    if (isStuck())
    {
        m_Status = Goal::failed_t;
        return m_Status;
    }

    if (m_pOwner->mMoveComp->IsArrived())
    {
        m_Status = Goal::completed_t;
    }

    return m_Status;
}

void A_GotoTarget::End()
{
    m_pOwner->mMoveComp->Stop경과시간();
    __super::End();
}

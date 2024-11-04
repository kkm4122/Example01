#include "pch.h"
#include "Goal.h"
#include "Actor.h"

void Goal::End() {}

void Goal::Render(int step)
{
    char tab[] = {'\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t', '\t'};
    tab[step]  = 0;
    AXLOG("%s %s", tab, getName());
}

bool Goal::HandleMessage(const ActorMessage& msg)
{
    return false;
}



/*---------------------------------------------------------------------------------*/
int Goal_Composite::ProcessSubgoals()
{
    // 이미 수행된 Goal들은 제거한다.
    while (!m_SubGoals.empty() && (m_SubGoals.front()->isComplete() || m_SubGoals.front()->hasFailed()))
    {
        Goal* g = m_SubGoals.front();
        m_SubGoals.pop_front();

        g->End();
        delete g;
    }

    // 더 이상의 SubGoal이 없다면 completed 으로 리턴한다.
    if (m_SubGoals.empty())
    {
        return completed_t;
    }
    // sub goal이 남아 있다면
    int StatusOfSubGoals = m_SubGoals.front()->Do();

    // 성공이 아니므로 결과를 리턴한다.
    if (StatusOfSubGoals != completed_t)
        return StatusOfSubGoals;

    // 처리한 Goal은 완성인데,
    // 남은 할 일이 있으면 Active 상태로
    if (m_SubGoals.size() > 1)
        return active_t;

    return completed_t;
}

bool Goal_Composite::SendToFirstSubGoal(const ActorMessage& msg)
{
    if (!m_SubGoals.empty())
    {
        return m_SubGoals.front()->HandleMessage(msg);
    }

    // 메세지가 처리되지 않았다면 False를 리턴하라....
    return false;
}

int Goal_Composite::Do()
{
    If_Inactive_Start();
    m_Status = ProcessSubgoals();//Do의 처리는 이 함수에서 확인

    return m_Status;
}

void Goal_Composite::Render(int step)
{
    __super::Render(step);
    ++step;

    for (Goal* it : m_SubGoals)
    {
        it->Render(step);
    }
}

bool Goal_Composite::HandleMessage(const ActorMessage& msg)
{
    return SendToFirstSubGoal(msg);
}

void Goal_Composite::RemoveAllSubgoals()
{
    while (!m_SubGoals.empty())
    {
        Goal* g = m_SubGoals.front();
        m_SubGoals.pop_front();
        g->End();
        delete g;
    }

    m_SubGoals.clear();
}
const char* Goal_Think::GOAL_NAME = "Goal_Think";
Goal_Think::Goal_Think(Actor* pE) : Goal_Composite(pE) {}


void Goal_Think::SelectTactic()
{
    double best                   = 0;
    Goal_Evaluator* MostDesirable = 0;

    for (Goal_Evaluator* it : m_Evaluators)
    {
        double desirability = it->CalculateDesirability(m_pOwner);

        if (desirability >= best)
        {
            best          = desirability;
            MostDesirable = it;
        }
    }

    if (best > 0.5)
        MostDesirable->SetGoal(m_pOwner);
}

void Goal_Think::Start()
{
    SelectTactic();
    m_Status = Goal::active_t;
}

int Goal_Think::Do()
{
    If_Inactive_Start();

    m_Status = ProcessSubgoals();
    
    return m_Status;
}

void Goal_Think::End()
{
    RemoveAllSubgoals();
    __super::End();
}

#pragma once
#include "preDefines.h"
#include "ActorMessage.h"


class Goal
{
public:
    enum {active_t, inactive_t, completed_t, failed_t};
protected:
    int m_Status;   //goal 상태
    Actor* m_pOwner;//goal 을 갖는 유닛(액터)
    void If_Inactive_Start()
    {
        if (isInActive())
            Start();
    }
    void If_Failed_Inactive()
    {
        if (hasFailed())
            m_Status = inactive_t;
    }

public:
    Goal(Actor* pE) : m_pOwner(pE), m_Status(inactive_t) {}
    virtual ~Goal() {};
    
    virtual void Start() = 0;  // 이 Goal 시작할때, 먼전 활성화 시키고 시작한다.
    virtual int Do()     = 0;
    virtual void End();  // 이 Goal이 끝났다면,
    virtual const char* getName() = 0;

    virtual void Render(int step);

    virtual bool HandleMessage(const ActorMessage& msg);

    virtual void AddSubgoal(Goal* g) { AXLOG("Cannot add goals to atomic goals"); }

    bool isComplete() const { return m_Status == completed_t; }
    bool isActive() const { return m_Status == active_t; }
    bool isInActive() const { return m_Status == inactive_t; }
    bool hasFailed() const { return m_Status == failed_t; }
};

class Goal_Composite : public Goal
{
    typedef std::list<Goal*> SubgoalList;//복합 목적은 단일목적들의 집합으로 구성 할 수 있다.
public:
    SubgoalList m_SubGoals;

    int ProcessSubgoals();
    bool SendToFirstSubGoal(const ActorMessage& msg);//최상단 메세지 전달

public:
    Goal_Composite(Actor* pE) : Goal(pE) {}
    ~Goal_Composite() { RemoveAllSubgoals(); }

    //	virtual void Start() = 0;
    virtual int Do() override;
    //	virtual void End() = 0;
    virtual void Render(int step) override;

    bool HandleMessage(const ActorMessage& msg) override;

    // 맨앞에 Goal을 추가한다.
    void AddSubgoal(Goal* g) { m_SubGoals.push_front(g); }
    void PushSubgoal(Goal* g) { m_SubGoals.push_back(g); }
    void RemoveAllSubgoals();
};


class Goal_Evaluator
{
public:
    // 욕구 평가하기
    virtual float CalculateDesirability(Actor* a) = 0;

    //
    virtual void SetGoal(Actor* a) = 0;
};



class Goal_Think : public Goal_Composite
{
    std::vector<Goal_Evaluator*> m_Evaluators;

public:
    static const char* GOAL_NAME;
    const char* getName() override { return GOAL_NAME; }

    Goal_Think(Actor* pE);

    void SelectTactic();

    void Start() override;
    int Do() override;
    void End() override;
};

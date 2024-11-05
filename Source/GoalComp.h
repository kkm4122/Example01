#pragma once
#include "IActorComponent.h"
#include "Goal.h"

class GoalComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

    GoalComp(Actor* actor);
    ~GoalComp();

    virtual void update(float delta) override;

public:
    Goal_Think* mThink = nullptr;
};

void AddGoal_GotoTarget(Actor* actor, Vec2 target);
void PushGoal_GotoTarget(Actor* actor, Vec2 target);


template <class T, class T2>
void PushGoal(Actor* actor, T2 target)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubgoal(new T(actor, target));
}

template <class T>
void PushGoal(Actor* actor)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubgoal(new T(actor));
}

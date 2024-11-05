#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "GoalComp.h"
#include "A_GotoTarget.h"


const std::string GoalComp::COMPONENT_NAME = "GoalComp";

GoalComp::GoalComp(Actor* actor) : IActorComponent(actor)
{
    mCompName = COMPONENT_NAME;
    mThink    = new Goal_Think(actor);

    actor->mGoalComp = this;
    
}


GoalComp::~GoalComp()
{
    SAFE_DELETE(mThink);
}

void GoalComp::update(float delta)
{
    mThink->Do();
}

void AddGoal_GotoTarget(Actor* actor, Vec2 target)
{
    if (actor->mGoalComp)
    {
        actor->mGoalComp->mThink->End();
        actor->mGoalComp->mThink->AddSubgoal(new A_GotoTarget(actor, target));
    }
}

void PushGoal_GotoTarget(Actor* actor, Vec2 target)
{
    if (actor->mGoalComp)
        actor->mGoalComp->mThink->PushSubgoal(new A_GotoTarget(actor, target));
}

#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "GoalComp.h"



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

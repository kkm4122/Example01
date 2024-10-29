#include "pch.h"
#include "UnitComp.h"
#include "Actor.h"

UnitComp::UnitComp(Actor* actor) : IActorComponent(actor)
{
    SAFE_DELETE(actor->mUnitComp);
    actor->mUnitComp = this;
}

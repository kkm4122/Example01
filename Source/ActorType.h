#pragma once
#include "preDefines.h"


enum class ActorType : UINT8
{
    None,
    Mouse,
    Farmer,
    Soldier,
    TownHall,
    Torch,
    Ball,
    Skeleton,
    CropsGround,
    Cow,

};

const char* getActorTypeName(ActorType type);

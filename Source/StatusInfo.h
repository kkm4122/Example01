#pragma once

#include "ActorType.h"


struct StatusInfo
{
    int maxHp;
    int hp;
    int at;
};


StatusInfo* CreateStatusInfo(ActorType actortype);

void SetFarmerStatus(StatusInfo* status);

void SetSkeletonStatus(StatusInfo* status);

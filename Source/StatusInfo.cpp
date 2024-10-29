#include "StatusInfo.h"

StatusInfo* CreateStatusInfo(ActorType actortype)
{
    auto status = new StatusInfo();

    switch (actortype)
    {
    case ActorType::Farmer:
        SetFarmerStatus(status);
        break;

    }
    return status;
}

void SetFarmerStatus(StatusInfo* status)//최초 농부 스탯
{
    status->maxHp = 100;
    status->at    = 10;
    status->hp    = 100;
}

void SetSkeletonStatus(StatusInfo* status) {}

#pragma once
#include"Aniinfo.h"
class IActorComponent;

/*
Actor간에 메세지를 전달한다.

결국, Component간에 메세지를 전달하는 거랑 같다.

*/
struct ActorMessage
{
    enum
    {
        MoveToTarget,
        AddToNextTarget,
        Contacted,
        Damaged,
        Attack,
        StopMoving
    } msgType;

    Actor* sender;
    IActorComponent* senderCmp;

    void* data = nullptr;
};

void SendAcotrMessage(Actor* r, ActorMessage msg);

struct AMsgData_Vec2
{
    Vec2 pos;
};

struct AMsgData_Damage
{
    int damageType;
    int damageValue;
};
struct AMsgData_PlayAnimation
{
    ECharName mCharName;
    ECharActName mActionName;
    ECharDir mDirName;
};

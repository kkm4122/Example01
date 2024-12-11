#include "pch.h"
#include "ActorList.h"
#include "Actor.h"
#include "MovementComp.h"
//#include "2dGeometryFunc.h"
//#include "EventSystem.h"

ActorList::~ActorList()
{
    for (Actor* act : mActorList)
    {
        if (act)
            delete act;
    }
}

void ActorList::updateActors(float dt)
{
    for (Actor* act : mActorList)
    {
        if (act)
            act->update(dt);
    }
}

void ActorList::Delete_Actors()
{
    if (mDeleteActorList.size() == 0)
        return;

    for (Actor* act : mDeleteActorList)
    {
        _UnRegister(act);
        delete act;
    }

    mDeleteActorList.clear();
}

void ActorList::Created_Actors()
{
    if (mCreatedActorList.size() == 0)
        return;

    if (mActorList.size() < m_ActorMaxIdx)
        mActorList.resize(m_ActorMaxIdx, nullptr);

    for (Actor* act : mCreatedActorList)
    {
        mActorList[act->mActorID] = act;
    }

    mCreatedActorList.clear();
}

Actor* ActorList::NewActor()
{
    Actor* act = new Actor;
    _Register(act);

    return act;
}

void ActorList::EraseActor(Actor* act)
{
    act->mStatus = Actor::E_Destroyed;
    mDeleteActorList.push_back(act);
}

Actor* ActorList::FindActorByTag(std::string_view tagname)
{
    for (Actor* act : mActorList)
    {
        if (act->mTag == tagname)
            return act;
    }
    return nullptr;
}

Actor* ActorList::FindActorByName(std::string_view name)
{
    for (Actor* act : mActorList)
    {
        if (act->mActorName == name)
            return act;
    }
    return nullptr;
}

Actor* ActorList::FindActorByType(ActorType tt)
{
    for (Actor* act : mActorList)
    {
        if (act->mActorType == tt)
            return act;
    }
    return nullptr;
}

int ActorList::FindActorsByTag(std::vector<Actor*>& actors, std::string_view tagname)
{
    int cnt = 0;
    for (Actor* act : mActorList)
    {
        if (act->mTag == tagname)
        {
            ++cnt;
            actors.push_back(act);
        }
    }

    return cnt;
}

int ActorList::FindActorsByName(std::vector<Actor*>& actors, std::string_view name)
{
    int cnt = 0;
    for (Actor* act : mActorList)
    {
        if (act->mActorName == name)
        {
            ++cnt;
            actors.push_back(act);
        }
    }

    return cnt;
}

int ActorList::FindActorsByType(std::vector<Actor*>& actors, ActorType tt)
{
    int cnt = 0;
    for (Actor* act : mActorList)
    {
        if (act->mActorType == tt)
        {
            ++cnt;
            actors.push_back(act);
        }
    }

    return cnt;
}

unsigned int ActorList::_Register(Actor* aa)
{
    unsigned int idx;

    if (mFreeActorIDList.size() > 0)
    {
        idx = mFreeActorIDList.front();
        mFreeActorIDList.pop_front();
    }
    else
    {
        idx = m_ActorMaxIdx;
        ++m_ActorMaxIdx;
        // idx = mActorList.size();
        // mActorList.push_back(aa);
    }

    aa->mActorID = idx;
    mCreatedActorList.push_back(aa);

    return idx;
}

void ActorList::_UnRegister(Actor* aa)
{
    unsigned int idx = aa->mActorID;

    if (idx == UINT32_MAX)
        return;

    mActorList[idx] = nullptr;
    mFreeActorIDList.push_back(idx);
}

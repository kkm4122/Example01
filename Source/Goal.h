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
public:
    Goal(Actor* pE) : m_pOwner(pE), m_Status(inactive_t) {}
    virtual ~Goal() {};
    bool isComplete() const { return m_Status == completed_t; }
    bool isActive() const { return m_Status == active_t; }
    bool isInactive() const { return m_Status == inactive_t; }
    bool hasFailed() const { return m_Status == failed_t; }
};

class Goal_Composite : public Goal
{

};

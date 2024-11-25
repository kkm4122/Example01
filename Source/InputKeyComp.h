
#pragma once
#include "IActorComponent.h"
#include "Actor.h"

class InputKeyComp : public IActorComponent
{
public:
    const static std::string COMPONENT_NAME;

public:
    InputKeyComp(Actor* actor);
    ~InputKeyComp();

    void update(float delta);
    virtual void MessageProc(ActorMessage& msg) override;
    void SetKey(EventKeyboard::KeyCode a,bool b);

public:
    bool Key_a=false;
    bool Key_s=false;
    bool Key_w=false;
    bool Key_d=false;
};

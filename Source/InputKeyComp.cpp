#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "InputKeyComp.h"
const std::string InputKeyComp::COMPONENT_NAME = "InputKeyComp";
InputKeyComp::InputKeyComp(Actor* actor) : IActorComponent(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mInputComp = this;
}

InputKeyComp::~InputKeyComp() {}

void InputKeyComp::update(float delta)
{
    if (!isEnabled)
        return;

    /*

    wasd 활성화 되면
    pos.x,pos.y ++ -- 등으로 최종좌표 입력

    최종좌표로 센드 메세지

    */
}

void InputKeyComp::MessageProc(ActorMessage& msg)
{
    switch (msg.msgType)
    {
    case ActorMessage::Key:

        AMsgData_InputKey* data = (AMsgData_InputKey*)msg.data;
        EventKeyboard::KeyCode a = data->KEY;
        SetKey(a,data->able);

        break;
    }
}

void InputKeyComp::SetKey(EventKeyboard::KeyCode a, bool b)
{
    //키 활성화
    switch (a)
    {
    case ax::EventKeyboard::KeyCode::KEY_A:
        if (Key_a != b)
            Key_a = b;

        break;
    case ax::EventKeyboard::KeyCode::KEY_D:
        if (Key_d != b)
            Key_d = b;
        break;
    case ax::EventKeyboard::KeyCode::KEY_W:
        if (Key_w != b)
            Key_w = b;
        break;
    case ax::EventKeyboard::KeyCode::KEY_S:
        if (Key_s != b)
            Key_s = b;
        break;
    default:
        break;
    }
}



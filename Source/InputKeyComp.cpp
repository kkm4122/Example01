#include "pch.h"
#include "Actor.h"
#include "ActorMessage.h"
#include "InputKeyComp.h"
#include "MovementComp.h"
const std::string InputKeyComp::COMPONENT_NAME = "InputKeyComp";
InputKeyComp::InputKeyComp(Actor* actor) : IActorComponent(actor)
{
    mCompName        = COMPONENT_NAME;
    actor->mInputComp = this;
}

InputKeyComp::~InputKeyComp() {}

void InputKeyComp::update(float delta)
{
    Vec2 Pos = mActor->getPosition();
    if (!isEnabled)
        return;
    if (!Key_a && !Key_s && !Key_d && !Key_w)
    {
        
        ActorMessage msg      = {ActorMessage::StopMoving, nullptr, nullptr,
                                 };  // voidpointer를 받아 참조자를 받아야한다.
        SendAcotrMessage(mActor, msg);
        return;
    }
    if (Key_a)
        Pos.x--;
    if (Key_d)
        Pos.x++;
    if (Key_s)
        Pos.y--;
    if (Key_w)
        Pos.y++;
    /*

    wasd 활성화 되면
    pos.x,pos.y ++ -- 등으로 최종좌표 입력

    최종좌표로 센드 메세지

    */
        AMsgData_Vec2 msgData = {Pos};  // msgData의 데이터 타입 vec2
    ActorMessage msg = {ActorMessage::MoveToTarget, nullptr, nullptr,
                        &msgData};  // voidpointer를 받아 참조자를 받아야한다.
    SendAcotrMessage(mActor, msg);
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



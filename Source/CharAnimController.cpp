#include "CharAnimController.h"



using namespace ax;

const std::string CharAnimController::COMPONENT_NAME = "CharAnimController";

CharAnimController* CharAnimController::create(Actor* ac)
{
    auto body    = new (std::nothrow) CharAnimController();
    body->mActor = ac;

    if (body->init())
    {
        body->autorelease();
        return body;
    }

    AX_SAFE_DELETE(body);
    return nullptr;
}

void CharAnimController::update(float delta)
{
    if (mActor->mMoveComp)
        Update_CharactorAnimation(delta);
}  // INodeAnimationController 함수 호출

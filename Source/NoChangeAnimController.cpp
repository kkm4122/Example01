#include "pch.h"
#include "NoChangeAnimController.h"
#include "Actor.h"
#include "MovementComp.h"
//#include "MealFarmC.h"

using namespace ax;

const std::string NoChangeAnimController::COMPONENT_NAME = "NoChangeAnimController";


NoChangeAnimController* NoChangeAnimController::create(Actor* ac)
{
    auto body = new (std::nothrow) NoChangeAnimController();
    body->mActor = ac;
    if (body->init())
    {
        body->autorelease();
        return body;
    }
    AX_SAFE_DELETE(body);
    return nullptr;
}

#include "SensorComp.h"
#include "MovementComp.h"
#include "Actor.h"

#include "ActorMessage.h"
#include "UnitComp.h"
const std::string SensorComp::COMPONENT_NAME = "SensorComp";

SensorComp::SensorComp(Actor* actor) : IActorComponent(actor)
{
    mCompName          = COMPONENT_NAME;
    actor->mSensorComp = this;
    /*mNodedata.mActor   = actor;

    mRootNode = NewNode("Root");
    mRootNode->setPosition(actor->getPosition());*/
}

SensorComp::~SensorComp() {}

void SensorComp::update(float delta) {}

void SensorComp::MessageProc(ActorMessage& msg) {}

void SensorComp::addEnemy(ActorMessage& msg) {
    Actor* enemy = msg.sender;
    
        for (int i = 0; i < mAimList.size(); i++)
        {
            if (mAimList[i] == nullptr)
            {
                mAimList[i] = enemy;
                enemy->Lockon = true;
                return;
            }
        }
        if (mAimList.size() > 10)
        {
            AXLOG("");
        }
    //빈공간 메모리
    enemy->Lockon = true;
    mAimList.push_back(enemy);
  
}

void SensorComp::deleteEnemy(ActorMessage& msg)
{
    Actor* enemy = msg.sender;
    for (int i = 0; i < mAimList.size(); i++)
    {
        if (mAimList[i] == enemy)
        {
            mAimList[i]   = nullptr;
            enemy->Lockon = false;
           
            return;
        }
    }
}

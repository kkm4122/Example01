#include "Weapon.h"
#include "World.h"
#include "SensorComp.h"
#include "SceneComp.h"
#include "Actor.h"
bool Weapon::setAim()
{
    if (mMode == AimMode::MOUSE_POS)
    {
        mAiming = World::get()->wMousePos;
        
        mAiming += mActor->mPosition;
       
        return true;
    }
    else if(mMode == AimMode::NEAR_E)
    {
        TL = mLength;
        for (Actor* act : mActor->mSensorComp->mAimList)
        {
            if (act != nullptr)
            {

            Vec2 le = mActor->mPosition - act->mPosition;
                if (le.length() < TL)
                {
                    mAiming = act->mPosition;
                    TL      = le.length();
                }
            }
        }
        if (TL == mLength)
        {
            return false;
        }
        return true;
    }
    else 
    {

    }
}

#pragma once
//ItemComp.h
#include "preDefines.h"
#include "Aniinfo.h"
#include "ActorType.h"

//노드에서 컴포넌트를 상속받아서 장착할수있음
//컴포넌트 상속받으면
#include "IActorComponent.h"
#include "INodeAnimationController.h"

#include "UnitDefines.h"
#include "UnitComp.h"
class Actor;

class ItemComp : public UnitComp
{
public:
    enum
    {
        Exp,
        Item
    }mType;
    const static std::string COMPONENT_NAME;

    ItemComp();
    ~ItemComp();
    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void Attack();

};

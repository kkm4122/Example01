#pragma once
#include "IActorComponent.h"
#include "INodeAnimationController.h"

#include "UnitDefines.h"
#include "UnitComp.h"
class Actor;

class ProjectileC : public UnitComp
{
public:
    const static std::string COMPONENT_NAME;
    enum
    {
        E_Start,
        E_Flying,
        E_Explosion,
        E_End
    } mMode;
    
    ProjectileC(Actor* actor, Vec2 targetPos);
    ~ProjectileC();

    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void Attack();

    void PlayExplosion();
    void Damage처리하라(Actor* other);
    void Start(float delta);
    void ExplosionUpdate(float delta);
    void FlyingUpdate(float delta);
    void End(float delta);

    float timer          = 0;
    bool isExplosionMode = false;

    Actor* archor;
    Vec2 mTargetPos;
    int bounce_count = 1;
    
    INodeAnimationController* mAnimController = nullptr;  // 스프라이트
};



class ProjectileC2 : public UnitComp
{
public:
    const static std::string COMPONENT_NAME;
    enum
    {
        E_Start,
        E_Flying,
        E_End
    } mMode;

    ProjectileC2(Actor* actor, Vec2 targetPos);
    ~ProjectileC2();
    virtual void update(float delta) override;
    virtual void MessageProc(ActorMessage& msg) override;
    virtual void Attack();

    void PlayExplosion();
    void Damage처리하라(Actor* other);
    void Start(float delta);
    void ExplosionUpdate(float delta);
    void FlyingUpdate(float delta);
    void End(float delta);

    float timer          = 0;
    bool Piercing = false;

    Actor* archor;
    Vec2 mTargetPos;
    int Piercing_count = 3;

    INodeAnimationController* mAnimController = nullptr;  // 스프라이트
};

#pragma once
#include "axmol.h"
#include "Actor.h"
using namespace ax;

enum class ECharDir
{
    Left = 1,
    Right,
    Up,
    Down,
    Back,
    Face,
    anim_Count
};

enum class ECharName
{
    None,
    Worker,
    ARES,
    capguy,
    Farmer,
    TownHall,
    Torch,
    Ball,
    CropsGround,
    Explosion,
    Skeleton,
    HPBar,
    Carrot,
    Cow,
    Coin
};

enum class ECharActName
{
    
    Run,
    Attack,
    Idle,
    Move,
    Die,
    Damaged,
    Watering,
    Eat,
    Sit,
    StandUp,
    Sleeping,
    StartSleep,
    Walk
};


struct AnimInfo
{
    ECharName charName = ECharName::None;
    ECharActName actionName;
    ECharDir dir;

    char strPlist[128];
    char format[128];

    int startFrame;
    int frameCount;

    float perFrameTime;
    Vec2 anchor;

    Ptr<ax::Animation> animation;
    
    void CreateAnimation();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~
    static void DestroyAll();
    //ax::Animation* getani() { return animation; }
    //AnimInfo& FindAnimInfo(ECharActName action, ECharDir dir);
};


//


// Print useful error message instead of segfaulting when files are not there.

#define Add_Reference(p) (p)->retain()
void create_frameAnimation(AnimInfo& info);
ax::Sprite* CreateSprite_CharAnim(AnimInfo& info);

void Change_CharAnim(ax::Node* node, AnimInfo& info);
void ChangeAnimation(ECharName charName, ECharActName actName, ECharDir dir);
void ChangeAnimation(AnimInfo* ainfo);

struct S_Create_AnimNode
{
    ax::Sprite* node;
    AnimInfo* animInfo;
    ax::Animate* animate;
};
// on "init" you need to initialize your instance

ax::Sprite* SpawnHPbar_OnScene(ax::Node* scene, Vec2 pos);
/*

*/
AnimInfo& FindAnimInfo(ECharName charName, ECharActName action, ECharDir dir);
//AnimInfo& FindAnimInfo(ECharActName action, ECharDir dir);
AnimInfo& HpBar();
AnimInfo& HpBar(int idx);

AnimInfo& FindAnimInfoByIndex(ECharName charName, int idx);
//ax::Sprite* SpawnActor_OnScene(ax::Node* scene, ECharActName action, ECharDir dir, Vec2 pos);
ECharDir CalcAniDir(Vec2 mVelocity);

Actor* Spawn_Farmer(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_Cow(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_TownHall(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_Torch(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_CropsGround(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_Skeleton(ax::Node* parent, Vec2 worldPos);
Actor* Spawn_Mouse(ax::Node* parent, Vec2 worldPos);


//weapon
Actor* Spawn_Bullet(ax::Node* parent, Vec2 worldPos, Actor* archor, Vec2 targetPos);
Actor* Spawn_Bullet2(ax::Node* parent, Vec2 worldPos, Actor* archor, Vec2 targetPos);
Actor* SetCamp(Actor* actor);

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
    Animal,
    HPBar,
    TownHall,
    Torch,
    Ball
};

enum class ECharActName
{
    Walk,
    Run,
    Attack,
    Idle,
    Move
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

    ax::Animation* animation = nullptr;
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
void ChangeAnimation(AnimInfo* ainfo);
// on "init" you need to initialize your instance
ax::Sprite* SpawnActor_OnScene(ax::Node* scene, ECharActName action, ECharDir dir, Vec2 pos);
ax::Sprite* SpawnHPbar_OnScene(ax::Node* scene, Vec2 pos);
/*

*/
AnimInfo& FindAnimInfo(ECharActName action, ECharDir dir);
AnimInfo& HpBar();
AnimInfo& HpBar(int idx);

AnimInfo& FindAnimInfoByIndex(ECharName charName, int idx);
//ax::Sprite* SpawnActor_OnScene(ax::Node* scene, ECharActName action, ECharDir dir, Vec2 pos);
ECharDir CalcAniDir(Vec2 mVelocity);
Actor* Spawn_Farmer(ax::Node* parent, Vec2 worldPos);


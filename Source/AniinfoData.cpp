#pragma once
#include "Aniinfo.h"

#define anchor_farmer      Vec2(0.5, 1.f - (22.f / 32.f))
#define anchor_TownHall    Vec2(0.5, 1.f - (76.f / 80.f))
#define anchor_Torch       Vec2(0.5, 1.f - (32.f / 48.f))
#define anchor_Ball        Vec2(0.5, 0.5)
#define anchor_CropsGround Vec2(0.5, 0.5)
#define anchor_Explosion   Vec2(0.5, 0.5)
#define anchor_HPBar       Vec2(0.5, 0.5)
#define anchor_Skeleton    Vec2(0.5, 1.f - (22.f / 32.f))


AnimInfo g_AnimInfo_Farmer_Idle[] = {{ECharName::Farmer, ECharActName::Idle, ECharDir::Face, "TestMap.plist",
                                      "Farmer/Idle/Face/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Back, "TestMap.plist",
                                      "Farmer/Idle/Back/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Left, "TestMap.plist",
                                      "Farmer/Idle/Left/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Right, "TestMap.plist",
                                      "Farmer/Idle/Right/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr}};

AnimInfo g_AnimInfo_Farmer_Move[] = {{ECharName::Farmer, ECharActName::Move, ECharDir::Face, "TestMap.plist",
                                      "Farmer/Move/Face/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Back, "TestMap.plist",
                                      "Farmer/Move/Back/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Left, "TestMap.plist",
                                      "Farmer/Move/Left/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Right, "TestMap.plist",
                                      "Farmer/Move/Right/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr}};
AnimInfo g_AnimInfo_HPBar[]       = {
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0001.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0002.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0003.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0004.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0005.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0006.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0007.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0008.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0009.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0010.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
    {ECharName::HPBar, ECharActName::Idle, ECharDir::Face, "HPBar.plist", "HPBar/0011.png", 1, 1, (1.f / 1),
           anchor_HPBar, nullptr},
};
#define SAFE_release(p) \
    if (p)              \
    {                   \
        (p)->release(); \
        (p) = nullptr;  \
    }
void AnimInfo::CreateAnimation() {}
void AnimInfo::DestroyAll()
{

    int count = sizeof(g_AnimInfo_Farmer_Idle) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        SAFE_release(g_AnimInfo_Farmer_Idle[i].animation);
    }

    count = sizeof(g_AnimInfo_Farmer_Move) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        SAFE_release(g_AnimInfo_Farmer_Move[i].animation);
    }
}
AnimInfo& FindAnimInfo(ECharActName action, ECharDir dir)
{
    switch (action)
    {

    case ECharActName::Idle:
        for (int i = 0; i < 4; ++i)
        {
            if (g_AnimInfo_Farmer_Idle[i].dir == dir)
                return g_AnimInfo_Farmer_Idle[i];
        }
        break;
    case ECharActName::Move:
        for (int i = 0; i < 4; ++i)
        {
            if (g_AnimInfo_Farmer_Move[i].dir == dir)
                return g_AnimInfo_Farmer_Move[i];
        }
        break;
    };
}
AnimInfo& HpBar()
{
    return g_AnimInfo_HPBar[0];
}
AnimInfo& HpBar(int idx)
{
    if (idx < 0)
        return g_AnimInfo_HPBar[0];
    else if (idx > 10)
        return g_AnimInfo_HPBar[10];
    else
        return g_AnimInfo_HPBar[idx];
}
AnimInfo& FindAnimInfoByIndex(ECharName charName, int idx)
{
    switch (charName)
    {
    case ECharName::HPBar:
        return g_AnimInfo_HPBar[idx];
    }
    return g_AnimInfo_HPBar[idx];
}

ECharDir CalcAniDir(Vec2 mVelocity)
{
    mVelocity *= 10.f;  // 정확도를 높이고자 값을 키워서 다시 계산함.

    mVelocity.normalize();

    float cos45 = cos(AX_DEGREES_TO_RADIANS(45));

    if (mVelocity.x > cos45)
        return ECharDir::Right;

    if (mVelocity.x < -cos45)
        return ECharDir::Left;

    if (mVelocity.y > 0)
        return ECharDir::Back;

    return ECharDir::Face;
}

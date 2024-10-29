#pragma once
#include "Aniinfo.h"



using namespace ax;

#define anchor_farmer      Vec2(0.5, 1.f - (22.f / 32.f))
#define anchor_TownHall    Vec2(0.5, 1.f - (76.f / 80.f))
#define anchor_Torch       Vec2(0.5, 1.f - (32.f / 48.f))
#define anchor_Ball        Vec2(0.5, 0.5)
#define anchor_CropsGround Vec2(0.5, 0.5)
#define anchor_Explosion   Vec2(0.5, 0.5)
#define anchor_HPBar       Vec2(0.5, 0.5)
#define anchor_Skeleton    Vec2(0.5, 1.f - (22.f / 32.f))

AnimInfo noneAnimInfo = {
    ECharName::Torch, ECharActName::Idle, ECharDir::Face, "Torch.plist", "Torch/Face/%03d.png", 1, 8,
    (1.f / 8),        anchor_Ball,        nullptr};

AnimInfo g_AnimInfo_Farmer_Attack[] = {
    {ECharName::Farmer, ECharActName::Attack, ECharDir::Face, "Farmer.plist", "Farmer/Attack/Face/1_Attack/%04d.png", 1,
     4, (1.f / 4), anchor_farmer, nullptr},
    {ECharName::Farmer, ECharActName::Attack, ECharDir::Back, "Farmer.plist", "Farmer/Attack/Back/1_Attack/%04d.png", 1,
     4, (1.f / 4), anchor_farmer, nullptr},
    {ECharName::Farmer, ECharActName::Attack, ECharDir::Left, "Farmer.plist", "Farmer/Attack/Left/1_Attack/%04d.png", 1,
     4, (1.f / 4), anchor_farmer, nullptr},
    {ECharName::Farmer, ECharActName::Attack, ECharDir::Right, "Farmer.plist", "Farmer/Attack/Right/1_Attack/%04d.png",
     1, 4, (1.f / 4), anchor_farmer, nullptr}};

AnimInfo g_AnimInfo_Farmer_Idle[] = {{ECharName::Farmer, ECharActName::Idle, ECharDir::Face, "Farmer.plist",
                                      "Farmer/Idle/Face/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Back, "Farmer.plist",
                                      "Farmer/Idle/Back/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Left, "Farmer.plist",
                                      "Farmer/Idle/Left/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Idle, ECharDir::Right, "Farmer.plist",
                                      "Farmer/Idle/Right/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr}};

AnimInfo g_AnimInfo_Farmer_Move[] = {{ECharName::Farmer, ECharActName::Move, ECharDir::Face, "Farmer.plist",
                                      "Farmer/Move/Face/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Back, "Farmer.plist",
                                      "Farmer/Move/Back/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Left, "Farmer.plist",
                                      "Farmer/Move/Left/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr},
                                     {ECharName::Farmer, ECharActName::Move, ECharDir::Right, "Farmer.plist",
                                      "Farmer/Move/Right/%04d.png", 1, 6, (1.f / 6), anchor_farmer, nullptr}};

AnimInfo g_AnimInfo_Ball_Move[] = {{ECharName::Ball, ECharActName::Move, ECharDir::Face, "Ball.plist",
                                    "Ball/Move/Face/%04d.png", 1, 3, (1.f / 3), anchor_Ball, nullptr},
                                   {ECharName::Ball, ECharActName::Move, ECharDir::Back, "Ball.plist",
                                    "Ball/Move/Back/%04d.png", 1, 3, (1.f / 3), anchor_Ball, nullptr},
                                   {ECharName::Ball, ECharActName::Move, ECharDir::Left, "Ball.plist",
                                    "Ball/Move/Left/%04d.png", 1, 3, (1.f / 3), anchor_Ball, nullptr},
                                   {ECharName::Ball, ECharActName::Move, ECharDir::Right, "Ball.plist",
                                    "Ball/Move/Right/%04d.png", 1, 3, (1.f / 3), anchor_Ball, nullptr}};

AnimInfo g_AnimInfo_TownHall[]    = {{ECharName::TownHall, ECharActName::Idle, ECharDir::Face, "TownHall.plist",
                                      "TownHall/Face/%03d.png", 1, 3, (1.f / 3), anchor_TownHall, nullptr}};
AnimInfo g_AnimInfo_Torch[]       = {{ECharName::Torch, ECharActName::Idle, ECharDir::Face, "Torch.plist",
                                      "Torch/Face/%03d.png", 1, 8, (1.f / 8), anchor_Torch, nullptr}};
AnimInfo g_AnimInfo_Explosion[]   = {{ECharName::Explosion, ECharActName::Idle, ECharDir::Face, "Explosion.plist",
                                      "Explosion/%04d.png", 1, 10, (1.f / 10), anchor_Explosion, nullptr}};
AnimInfo g_AnimInfo_CropsGround[] = {{ECharName::CropsGround, ECharActName::Idle, ECharDir::Face, "CropsGround.plist",
                                      "CropsGround/%04d.png", 1, 2, (1.f / 2), anchor_CropsGround, nullptr}};

AnimInfo g_AnimInfo_HPBar[] = {
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

AnimInfo g_AnimInfo_Skeleton_Attack[]{{ECharName::Skeleton, ECharActName::Attack, ECharDir::Face, "Skeleton.plist",
                                       "Skeleton/Attack/Face/%04d.png", 1, 4, (1.f / 4), anchor_Skeleton, nullptr},
                                      {ECharName::Skeleton, ECharActName::Attack, ECharDir::Back, "Skeleton.plist",
                                       "Skeleton/Attack/Back/%04d.png", 1, 4, (1.f / 4), anchor_Skeleton, nullptr},
                                      {ECharName::Skeleton, ECharActName::Attack, ECharDir::Left, "Skeleton.plist",
                                       "Skeleton/Attack/Left/%04d.png", 1, 4, (1.f / 4), anchor_Skeleton, nullptr},
                                      {ECharName::Skeleton, ECharActName::Attack, ECharDir::Right, "Skeleton.plist",
                                       "Skeleton/Attack/Right/%04d.png", 1, 4, (1.f / 4), anchor_Skeleton, nullptr}};

AnimInfo g_AnimInfo_Skeleton_Move[] = {{ECharName::Skeleton, ECharActName::Move, ECharDir::Face, "Skeleton.plist",
                                        "Skeleton/Move/Face/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Move, ECharDir::Back, "Skeleton.plist",
                                        "Skeleton/Move/Back/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Move, ECharDir::Left, "Skeleton.plist",
                                        "Skeleton/Move/Left/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Move, ECharDir::Right, "Skeleton.plist",
                                        "Skeleton/Move/Right/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr}};

AnimInfo g_AnimInfo_Skeleton_Idle[] = {{ECharName::Skeleton, ECharActName::Idle, ECharDir::Face, "Skeleton.plist",
                                        "Skeleton/Idle/Face/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Idle, ECharDir::Back, "Skeleton.plist",
                                        "Skeleton/Idle/Back/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Idle, ECharDir::Left, "Skeleton.plist",
                                        "Skeleton/Idle/Left/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr},
                                       {ECharName::Skeleton, ECharActName::Idle, ECharDir::Right, "Skeleton.plist",
                                        "Skeleton/Idle/Right/%04d.png", 1, 6, (1.f / 6), anchor_Skeleton, nullptr}};
AnimInfo g_AnimInfo_Skeleton_Die[]  = {
    {ECharName::Skeleton, ECharActName::Die, ECharDir::Face, "Skeleton.plist", "Skeleton/Die/%04d.png", 1, 4, (1.f / 4),
      anchor_Skeleton, nullptr},
};


void AnimInfo::CreateAnimation()
{
    if (animation.isNotNull())
        return;

    auto spritecache = ax::SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile(strPlist);

    // frame 모으기
    ax::Vector<ax::SpriteFrame*> animFrames;
    char str[128];
    if (frameCount > 1)
    {
        int end = startFrame + frameCount;

        for (int i = startFrame; i < end; i++)
        {
            sprintf(str, format, i);
            ax::SpriteFrame* sp = spritecache->getSpriteFrameByName(str);
            sp->setAnchorPoint(anchor);
            animFrames.pushBack(sp);
        }
    }
    else
    {
        sprintf(str, format, startFrame);
        ax::SpriteFrame* sp = spritecache->getSpriteFrameByName(str);
        sp->setAnchorPoint(anchor);

        animFrames.pushBack(sp);
        animFrames.pushBack(sp);
    }

    animation = Animation::createWithSpriteFrames(animFrames, perFrameTime);
}
void AnimInfo::DestroyAll()
{

    int count = sizeof(g_AnimInfo_Farmer_Idle) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        g_AnimInfo_Farmer_Idle[i].animation.setNull();
    }

    count = sizeof(g_AnimInfo_Farmer_Move) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        g_AnimInfo_Farmer_Move[i].animation.setNull();
    }
    count = sizeof(g_AnimInfo_Farmer_Move) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        g_AnimInfo_Farmer_Move[i].animation.setNull();
    }
    count = sizeof(g_AnimInfo_Ball_Move) / sizeof(AnimInfo);
    for (int i = 0; i < count; ++i)
    {
        g_AnimInfo_Ball_Move[i].animation.setNull();
    }

    g_AnimInfo_TownHall[0].animation.setNull();
    g_AnimInfo_Torch[0].animation.setNull();
}
AnimInfo& FindAnimInfo(ECharName charName, ECharActName action, ECharDir dir)
{
    switch (charName)
    {
    case ECharName::Farmer:
        switch (action)
        {
        case ECharActName::Attack:
            for (int i = 0; i < 4; ++i)
            {
                if (g_AnimInfo_Farmer_Attack[i].dir == dir)
                    return g_AnimInfo_Farmer_Attack[i];
            }
            break;
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
        return g_AnimInfo_Farmer_Attack[0];
    }  // TODO: 여기에 return 문을 삽입합니다.
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

#pragma once
#include "Aniinfo.h"
#include "animController.h"


using namespace ax;
Vec2 getPhysicsBodySize(ECharName charName)
{
    switch (charName)
    {
    case ECharName::ARES:
    case ECharName::capguy:
    case ECharName::Farmer:
        return Vec2(16, 16);

    case ECharName::TownHall:
        return Vec2(48, 80);
    case ECharName::Torch:
        return Vec2(16, 20);
    case ECharName::CropsGround:
        return Vec2(48, 48);
    }

    return Vec2(16, 16);
}

void Change_CharAnim(ax::Node* node, AnimInfo& info)
{
    create_frameAnimation(info);

    node->stopActionByTag(20202);

    ax::Action* action = RepeatForever::create(Animate::create(info.animation.get()));
    action->setTag(20202);
    node->runAction(action);
}

void ChangeAnimation(ECharName charName, ECharActName actName, ECharDir dir)
{
    AnimInfo& info = FindAnimInfo(charName, actName, dir);
    ChangeAnimation(&info);
}

void ChangeAnimation(AnimInfo* ainfo) {}

void create_frameAnimation(AnimInfo& info) 
{
    if (info.animation.isNull())
    {
        auto spritecache = ax::SpriteFrameCache::getInstance();
        char str[128]    = "Plist/";
        strcat(str, info.strPlist);    
        //sprintf(str, info.strPlist);
        spritecache->addSpriteFramesWithFile(str);

        // frame 모으기
        ax::Vector<ax::SpriteFrame*> animFrames;

        
        for (int i = 1; i <= info.frameCount; i++)
        {
            sprintf(str, info.format, i);
            animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        }
        info.animation = Animation::createWithSpriteFrames(animFrames, info.perFrameTime);
        Add_Reference(info.animation);
    }
}

ax::Sprite* CreateSprite_CharAnim(AnimInfo& info)
{
    create_frameAnimation(info);

    auto sprite = Sprite::createWithSpriteFrame(info.animation->getFrames().front()->getSpriteFrame());

    ax::Action* action = RepeatForever::create(Animate::create(info.animation.get()));
    action->setTag(20202);
    sprite->runAction(action);

    return sprite;
}

/*
ax::Sprite* SpawnActor_OnScene(ax::Node* scene, Actor* actor, ECharName charName, ECharActName action, ECharDir dir)
{
    AnimInfo& info = FindAnimInfo(charName, action, dir);

    ax::Sprite* node = CreateSprite_CharAnim(info);
    node->setPosition(actor->mPosition);
    scene->addChild(node);

    auto comp              = NodeComponent_Actor::create(actor);
    comp->mCurrentAnimInfo = &info;
    node->addComponent(comp);

    auto body = PhysicsBody::createBox(node->getContentSize());
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setDynamic(false);
    node->setPhysicsBody(body);

    //~ Actor 정보 채우기 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Actor::SceneObj sobj;
    sobj.scene = scene;
    sobj.cmp   = comp;
    actor->SceneObj_pushback(sobj);

    return node;
}
*/
ax::Sprite* SpawnHPbar_OnScene(ax::Node* scene, Vec2 pos)
{
    AnimInfo& info = HpBar();
    ax::Sprite* node = CreateSprite_CharAnim(info);
    node->setPosition(pos);
    scene->addChild(node);
    return node;
}

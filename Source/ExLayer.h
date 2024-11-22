#pragma once
//#include "pch.h"
#include "preDefines.h"
#include <vector>
#include <iostream>
class ExLayer : public ax::Layer
{
public:

    CREATE_FUNC(ExLayer);

    ax::TMXTiledMap* mMap           = nullptr;//불러올 타일맵
    ax::PhysicsWorld* mPhysicsWorld = nullptr;//물리법칙 적용을 위한 physicworld

    cPoint visible, origin;//출발지
    cPoint currentCenter;
    Vec2 halfContentsSize;

    Vec2 mWorldBase;
    ax::TMXTiledMap* mMaplist[9];
    //std::vector<ax::TMXTiledMap*> mMaplist;

    virtual bool init() override;
    virtual void update(float delta) override;
    void CreateMap(Vec2 pos);
    void InfinityUpdate(TMXTiledMap* map);
    cPoint CorrectCenterPoint(cPoint currentCenter, float layerScale);

    void MoveCenterTo(cPoint center, float layerScale);
    void MoveBy(cPoint movBy, float layerScale);
    
private:
};

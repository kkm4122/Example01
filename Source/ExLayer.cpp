#include "pch.h"
#include "AniInfo.h"
#include "ExLayer.h"
#include "Actor.h"
#include "World.h"

bool ExLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    visible = Director::getInstance()->getVisibleSize();
    origin  = Director::getInstance()->getVisibleOrigin();

    // We need to set GameLayer position according to left-bottom point
    // this->setPosition(visible / 2);

    //mMap = TMXTiledMap::create("TileMaps/InfinityEx.tmx");
    //// mMap = Sprite::create("MapResource.png");


    //mMap->setAnchorPoint(Vec2(0.5, 0.5));
    //mMap->setPosition(Vec2(0, 0));

    //this->setPosition((visible / 2));
    //this->addChild(mMap);
    Vec2 playerpos(480, 480);
        //World::get()->GetSeletedActor()->getPosition();
    CreateMap(playerpos);
    halfContentsSize.x = mMaplist[4]->getContentSize().width / 2*3;
    halfContentsSize.y = mMaplist[4]->getContentSize().height / 2*3;
    
    mWorldBase.x = halfContentsSize.x - (visible.x / 2);
    mWorldBase.y = halfContentsSize.y - (visible.y / 2);

    currentCenter.x = halfContentsSize.x - (visible.x / (2 * this->getScale()));
    currentCenter.y = halfContentsSize.y - (visible.y / (2 * this->getScale()));

    return true;
}

void ExLayer::update(float delta)
{
    for (int i = 0; i < 9; i++)
    {
        InfinityUpdate(mMaplist[i]);
    }
}

void ExLayer::CreateMap(Vec2 pos)
{
    
    for (int i = 0; i < 9; i++)
    {
        mMaplist[i] = TMXTiledMap::create("TileMaps/InfinityEx.tmx");
        mMaplist[i]->setAnchorPoint(Vec2(0.5, 0.5));
        this->addChild(mMaplist[i]);
    }
    mMaplist[0]->setPosition(Vec2(pos.x - 320, pos.y- 320));
    mMaplist[1]->setPosition(Vec2(pos.x, pos.y - 320));
    mMaplist[2]->setPosition(Vec2(pos.x + 320, pos.y - 320));
    mMaplist[3]->setPosition(Vec2(pos.x - 320, pos.y));
    mMaplist[4]->setPosition(Vec2(pos.x, pos.y));
    mMaplist[5]->setPosition(Vec2(pos.x + 320, pos.y));
    mMaplist[6]->setPosition(Vec2(pos.x - 320, pos.y+320));
    mMaplist[7]->setPosition(Vec2(pos.x, pos.y + 320));
    mMaplist[8]->setPosition(Vec2(pos.x + 320, pos.y + 320));
   
}

void ExLayer::InfinityUpdate(TMXTiledMap* map)
{
    if (!World::get()->GetSeletedActor())
    {
        return;
    }
    Vec2 PlayerPos = World::get()->GetSeletedActor()->getPosition();
    float lengthx = (map->getContentSize().x * 1.5f)-1;
    float lengthy = (map->getContentSize().y * 1.5f)-1;
    float lengthMandPx = map->getPositionX() - PlayerPos.x;
    float lengthMandPy = map->getPositionY() - PlayerPos.y;
    if (lengthMandPx < (-lengthx))
    {
        float x = PlayerPos.x + lengthx;
        map->setPositionX(x);
        AXLOG("map좌표 %f, %f \n", map->getPositionX(), map->getPositionY());
    }
    if (lengthMandPy < (-lengthy))
    {
        float y = PlayerPos.y + lengthy;
        map->setPositionY(y);
        AXLOG("map좌표 %f, %f \n", map->getPositionX(), map->getPositionY());
    }
    if (lengthMandPx > (lengthx))
    {
        float x = PlayerPos.x - lengthx;
        map->setPositionX(x);
        AXLOG("map좌표 %f, %f \n", map->getPositionX(), map->getPositionY());
    }
    if (lengthMandPy > (lengthy))
    {
        float y = PlayerPos.y - lengthy;
        map->setPositionY(y);
    AXLOG("map좌표 %f, %f \n", map->getPositionX(), map->getPositionY());
    }
}

cPoint ExLayer::CorrectCenterPoint(cPoint center, float layerScale)
{
    cPoint scaledCenter = center * layerScale;

    // mapSize = in-game size of map. ( Don't forget to multiply this to map->getScale() if you had scaled map)
    cSize mapSize = mMap->getContentSize() * mMap->getScale();
    float scale   = this->getScale();

    scaledCenter.x = std::max(scaledCenter.x, visible.x / 2);
    scaledCenter.x = std::min(scaledCenter.x, mapSize.width * scale - visible.x / 2);
    scaledCenter.y = std::max(scaledCenter.y, visible.y / 2);
    scaledCenter.y = std::min(scaledCenter.y, mapSize.height * scale - visible.y / 2);

    return (scaledCenter / layerScale);
}


// presume : `center` is based on nonScaled-layer-size:  [0,0] => [map.width, map.height]
void ExLayer::MoveCenterTo(cPoint center, float layerScale)
{
    // Convert nonScaled-layer-size to scaled-layer-size
    // [0,0] => [0,0] ||| [map.width, map.height] => [map.width * S , map.height * S]
    cPoint scaledCenter = center * layerScale;

    scaledCenter.x = -scaledCenter.x + visible.x / 2 + origin.x;
    scaledCenter.y = -scaledCenter.y + visible.y / 2 + origin.y;
    this->setPosition(scaledCenter);
}

void ExLayer::MoveBy(cPoint movBy, float layerScale)
{
    currentCenter += movBy;
    cPoint scaledCenter = currentCenter * layerScale;

    scaledCenter.x = -scaledCenter.x + visible.x / 2 + origin.x;
    scaledCenter.y = -scaledCenter.y + visible.y / 2 + origin.y;
    this->setPosition(scaledCenter);
}

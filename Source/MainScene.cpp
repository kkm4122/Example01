/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "Actor.h"
#include "World.h"
#include "ExLayer.h"


#include "SceneComp.h"
#include "animController.h"
#include "BarComponent.h"
#include "MovementComp.h"
#include "GoalComp.h"
#include "A_RandomMoving.h"
#include "ActorMessage.h"
#include "ImGui/ImGuiPresenter.h"

using namespace ax::extension;
using namespace ax;
class AnimInfo;
    // Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}
#define Add_Reference(p) (p)->retain()



// on "init" you need to initialize your instance

//









namespace
{
static MainScene* g = nullptr;
}


MainScene* MainScene::get()
{
    if (!g)
        g = new MainScene;
    return g;
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    visibleSize     = _director->getVisibleSize();
    origin          = _director->getVisibleOrigin();
    halfVisibleSize = visibleSize / 2;
    auto safeArea   = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;


    //입력 리스너들
    auto mouseListener           = EventListenerMouse::create();
    mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto contactListener               = EventListenerPhysicsContact::create();
    contactListener->onContactPreSolve = AX_CALLBACK_1(MainScene::onContactBegin, this);
    contactListener->onContactBegin    = AX_CALLBACK_1(MainScene::onContactBegin, this);
    contactListener->onContactSeparate = AX_CALLBACK_1(MainScene::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed  = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);

    mExLayer                = ExLayer::create();
    mExLayer->mPhysicsWorld = getPhysicsWorld();
    mExLayer->mPhysicsWorld->setGravity(Vec2(0, 0));
    this->addChild(mExLayer);

    setGameScale(mExLayer->getScale());



    SpawnActor();
    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}
void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}
void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}
void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    Vec2 Pos(e->getCursorX(), e->getCursorY());
    Vec2 mouseWorldPos = Pos - mExLayer->getPosition();
    mouseWorldPos      = mouseWorldPos / mGameScale;
    AXLOG("onMouseDown detected, Key: %d %f,%f\n%f,%f", static_cast<int>(e->getMouseButton()), e->getCursorX(),
          e->getCursorY(),mouseWorldPos.x,mouseWorldPos.y);
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        if (mSelectedActor!=nullptr)
        {

       // SendAcotrMessage(mSelectedActor, ActorMessage::MoveToTarget);
            AMsgData_Vec2 msgData = {mouseWorldPos};  // msgData의 데이터 타입 vec2
       ActorMessage msg      = {ActorMessage::MoveToTarget, nullptr, nullptr,
                                &msgData};  // voidpointer를 받아 참조자를 받아야한다.
            SendAcotrMessage(mSelectedActor, msg);
        }
    }
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        SpawnCow(mouseWorldPos);
    }
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
    if (e->getScrollY() < 0)
        setGameScale(mGameScale + 0.1f);
    else if (e->getScrollY() > 0)
        setGameScale(mGameScale - 0.1f);
}

bool MainScene::onContactBegin(ax::PhysicsContact& contact)
{

    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    auto nodeDataA = (Nodedata*)bodyA->getOwner()->getUserData();
    auto nodeDataB = (Nodedata*)bodyB->getOwner()->getUserData();

    auto nodeActorA = nodeDataA->mActor;
    auto nodeActorB = nodeDataB->mActor;

    ActorMessage amsgA = {ActorMessage::Contacted, nodeActorB, nullptr, nodeDataB};
    SendAcotrMessage(nodeActorA, amsgA);

    ActorMessage amsgB = {ActorMessage::Contacted, nodeActorA, nullptr, nodeDataA};
    SendAcotrMessage(nodeActorB, amsgB);

    return true;
}

bool MainScene::onContactSeparate(ax::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    auto nodeDataA = (Nodedata*)bodyA->getOwner()->getUserData();
    auto nodeDataB = (Nodedata*)bodyB->getOwner()->getUserData();

    auto nodeActorA = nodeDataA->mActor;
    auto nodeActorB = nodeDataB->mActor;

    if (nodeActorA == nullptr || nodeActorB == nullptr)
        return true;

    return true;
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    AMsgData_InputKey Inpu{code, true};
    ActorMessage msg = {ActorMessage::Key, nullptr, nullptr, &Inpu};
    switch (code)
    {
    case ax::EventKeyboard::KeyCode::KEY_Z:
        mSelectedActor->currentHP -= 10;
       
        break;
    case ax::EventKeyboard::KeyCode::KEY_X:
        mSelectedActor->currentHP += 10;
        
        break;
    case ax::EventKeyboard::KeyCode::KEY_W:
        
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_S:
        
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_A:
        
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_D:
        
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_SPACE:
        ActorMessage msg1 = {ActorMessage::Shot, nullptr, nullptr,
                            nullptr};  // voidpointer를 받아 참조자를 받아야한다.
        SendAcotrMessage(mSelectedActor, msg1);
        break;
    }
    //AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AMsgData_InputKey Inpu{code, false};
    ActorMessage msg = {ActorMessage::Key, nullptr, nullptr, &Inpu};
    switch (code)
    {
   
    case ax::EventKeyboard::KeyCode::KEY_W:
        
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_S:
        
       
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_A:
        
       
        SendAcotrMessage(mSelectedActor, msg);
        break;
    case ax::EventKeyboard::KeyCode::KEY_D:
       
        
        SendAcotrMessage(mSelectedActor, msg);
        break;
    
    }
    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta)
{
    //_director->convertToGL();
    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;

        break;
    }

    case GameState::update:
    {
       
        
        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }
        
    } //switch
    if (mSelectedActor)
    {
        Vec2 pos = halfVisibleSize - (mSelectedActor->getPosition() * mGameScale);
        mExLayer->setPosition(pos);
    }
    mExLayer->update(delta);
}

void MainScene::createCharactorAni(ax::Vec2 pos)
{
    Node* ani       = Sprite::create("0001.png");
    this->addChild(ani);
    ani->setScale(2, 2);
    ani->setPosition(pos);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.3);
    for (int index = 1; index <= 6; ++index)

    {

        char fileName[256];

        sprintf(fileName, "00%02d.png", index);

        animation->addSpriteFrameWithFile(fileName);
    }
    
    auto animate = Animate::create(animation);
    auto act     = RepeatForever::create(animate);
    ani->runAction(act);

}

void MainScene::createCharactorPlist(ax::Vec2 pos)
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();

    cache->addSpriteFramesWithFile("Farmer.plist");

   
    ax::Vector<ax::SpriteFrame*> animFrames;

    for (int i = 1; i < 6; ++i)

    {

        char fileName[128];

        sprintf(fileName, "Farmer/Move/Face/%04d.png", i);
        animFrames.pushBack(cache->getSpriteFrameByName(fileName));   
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    
    auto sprite = Sprite::createWithSpriteFrame(animation->getFrames().front()->getSpriteFrame());
    sprite->setPosition(pos);
    sprite->setScale(2, 2);
    this->addChild(sprite);
    ax::Action* action = RepeatForever::create(Animate::create(animation));
    //action->setTag(20202);
    sprite->runAction(action);
    

    

    
}



void MainScene::SpawnActor()
{
    Vec2 pos = halfVisibleSize - mExLayer->getPosition();
    SpawnActor(Vec2(pos));
}

void MainScene::SpawnActor(Vec2 pos)
{
    //auto actor      = Spawn_Farmer(this, pos);
    auto actor     = Spawn_Farmer(mExLayer, pos);
    //auto a = actor->mSceneComp->mRootNode->getParent();
    mSelectedActor = actor;
    World::get()->SetSelectActor(actor);
    if (mGameScale == 1.f)
        setGameScale(2.f);


    //auto excomp          = new ExComponent(act);
    
}

void MainScene::SpawnFamer(ax::Vec2 pos) {}

void MainScene::SpawnCow(ax::Vec2 pos)
{
    auto actor2 = Spawn_Cow(mExLayer, pos);
    PushGoal<A_RandomMoving>(actor2);
}

void MainScene::setGameScale(float s)
{
    mGameScale = s;
    if (mGameScale < 1.f)
        mGameScale = 1.0f;
    if (mGameScale > 2.f)
        mGameScale = 2.0f;
    mExLayer->setScale(mGameScale);
}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MainScene::onEnter()
{
    __super::onEnter();

    ax::extension::ImGuiPresenter::getInstance()->setViewResolution(visibleSize.x, visibleSize.y);
    ax::extension::ImGuiPresenter::getInstance()->addFont("fonts/arial.ttf");
    ax::extension::ImGuiPresenter::getInstance()->enableDPIScale();
    ax::extension::ImGuiPresenter::getInstance()->addRenderLoop("#test", AX_CALLBACK_0(MainScene::onDrawImGui, this),
                                                                this);

    //CreatMouseActor();
}

void MainScene::onDrawImGui() {}

void MainScene::onExit()
{
    ImGuiPresenter::getInstance()->removeRenderLoop("#test");
    ImGuiPresenter::getInstance()->clearFonts();

    ImGuiPresenter::destroyInstance();

    __super::onExit();
}

void MainScene::actorPushBack(Actor* a)
{
    a->mActorID = mActorList.size();
    mActorList.push_back(a);
}
Actor* MainScene::NewActor()
{
    Actor* act = new Actor;  // 생성
    actorPushBack(act);      // 푸시
    mActorList.push_back(act);
    return act;              //
}

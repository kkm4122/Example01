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

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__
#include "preDefines.h"
#include "axmol.h"
using namespace ax;
class SceneComp;
class MainScene : public ax::Scene
{
    enum class GameState
    {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };
    
public:


    static MainScene* get();

    cSize visibleSize;
    cSize halfVisibleSize;
    cPoint origin;

    bool init() override;
    void update(float delta) override;
    void createCharactorAni(ax::Vec2 pos);
    void createCharactorPlist(ax::Vec2 pos);
    Actor* mSelectedActor=nullptr;

    Actor* mContactedActor = nullptr;

    Actor* mPlayerActor = nullptr;
    Actor* mMouseActor  = nullptr;
    Vec2 mMouseDownWorldPos;
    Vec2 mMouseWorldPos;

    std::vector<Actor*> mActorList;
    Actor* NewActor();
    void SpawnActor();
    void SpawnActor(ax::Vec2 pos);
    void SpawnFamer(ax::Vec2 pos);
    void SpawnCow(ax::Vec2 pos);



    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);

    // mouse
    void onMouseDown(ax::Event* event);
    void onMouseUp(ax::Event* event);
    void onMouseMove(ax::Event* event);
    void onMouseScroll(ax::Event* event);
    // Physics
    bool onContactBegin(ax::PhysicsContact& contact);
    bool onContactSeparate(ax::PhysicsContact& contact);
    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event* event);
    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event* event);

    // a selector callback
    void menuCloseCallback(ax::Object* sender);


    // ImGUI ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void onEnter() override;
    void onDrawImGui();
    void onExit() override;
    bool show_test_window          = false;
    bool show_another_window       = true;
    bool show_create_window        = false;
    bool show_select_player_window = false;
    bool show_select_window        = false;


    void actorPushBack(Actor* a);

private:
    GameState _gameState = GameState::init;
};

#endif  // __MAIN_SCENE_H__

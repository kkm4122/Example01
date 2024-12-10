#pragma once
#include "IDsystem.h"
#include "ActorList.h"
class Actor;

class World
{
public:
    World();
    ~World();
    static World* get();
    static void destroy();

    void GetWindowPosW(HWND hWnd, float* x, float* y);

    long long getWorldTime() const { return mWorldTime; }
    void update(float dt);
    void updateActors(float dt);
    void EraseActor(Actor* act);
    void EraseBullet(Actor* act);
    void Delete_Actors();
    void Delete_Bulletes();
    Actor* NewActor();
    Actor* NewBullet();
    void SetSelectActor(Actor* act) { WSeletedActer = act; }
    Actor* GetSeletedActor() { return WSeletedActer; }
    Vec2 wMousePos;
    void SetScale(float scale) { mWorldScale = scale; }

public:
    bool mIsRunning = true;

    float mWorldTime        = 0;
    long long mWorldUpdateCount = 0;
    float mWorldScale;

   unsigned int RegisterBullet(Actor* aa);
    void UnRegisterBullet(Actor* aa);
    
    unsigned int RegisterActor(Actor* aa);
    void UnRegisterActor(Actor* aa);
    //std::vector<Wall2D*> m_Walls;
    Actor* WSeletedActer=nullptr;
    std::vector<Actor*> mActorList;
    std::vector<Actor*> mDeleteActorList;
    std::deque<unsigned int> mFreeActorIDList;

    std::vector<Actor*> mBulletList;
    std::vector<Actor*> mDeleteBulletList;
    std::deque<unsigned int> mFreeBulletIDList;

    std::vector<Actor*> mUpdateList_Extra;
    int x = 0;

private:
    ActorList m_ActorList;
    ActorList m_ProjectileList;
    ActorList m_ItemList;

    unsigned int m_ActorMaxIdx = 0;
};

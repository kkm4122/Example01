#pragma once
#include "IDsystem.h"
class Actor;

class World
{
public:
    World();
    ~World();
    static World* get();
    static void destroy();

    long long getWorldTime() const { return mWorldTime; }
    void update(float dt);
    void updateActors(float dt);
    void eraseActor(Actor* act);

    void Delete_Actors();

    Actor* NewActor();
    void EraseActor(Actor* act);
    void SetSelectActor(Actor* act) { WSeletedActer = act; }
    Actor* GetSeletedActor() { return WSeletedActer; }


public:
    bool mIsRunning = true;

    float mWorldTime        = 0;
    long long mWorldUpdateCount = 0;


    IDsystem<Actor> mIdList;

    //std::vector<Wall2D*> m_Walls;
    Actor* WSeletedActer=nullptr;
    std::vector<Actor*> mDeleteActorList;
    std::vector<Actor*> mUpdateList_Extra;
};

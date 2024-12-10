#pragma once

#pragma once
#include "preDefines.h"
//#include "Wall2D.h"
#include "IDsystem.h"
#include "ActorType.h"
/************************************************************************
월드에 있는 actorlist가 업데이트를 돌릴때 엑터가 다른 엑터를 생성할때
업데이트 함수에서 오류 발생
이를 방지하기위해 2개의 액터리스트를 만들어 액터가 다른 액터를 생성할때
다른 액터리스트에 액터를 넣어주고
업데이트가 넣어진 액터리스트에 있는 액터들을 원래 액터리스트에 넣는다.
*************************************************************************/
class ActorList
{
public:
    ~ActorList();

    void updateActors(float dt);
    void Delete_Actors();
    void Created_Actors();


    Actor* NewActor();
    void EraseActor(Actor* act);
    Actor* FindActorByTag(std::string_view tagname);
    Actor* FindActorByName(std::string_view name);
    Actor* FindActorByType(ActorType tt);
    int FindActorsByTag(std::vector<Actor*>& actors, std::string_view tagname);
    int FindActorsByName(std::vector<Actor*>& actors, std::string_view name);
    int FindActorsByType(std::vector<Actor*>& actors, ActorType tt);

    std::vector<Actor*>& GetActorList() { return mActorList; }

private:
    unsigned int _Register(Actor* aa);
    void _UnRegister(Actor* aa);

    std::deque<unsigned int> mFreeActorIDList;
    std::vector<Actor*> mActorList;
    std::vector<Actor*> mCreatedActorList;
    std::vector<Actor*> mDeleteActorList;
    unsigned int m_ActorMaxIdx = 0;
};

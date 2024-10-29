#pragma once
#include "axmol.h"
#include "SmartPtr.h"
#define SAFE_DELETE(p) \
    if (p)             \
    {                  \
        delete (p);    \
        (p) = nullptr; \
    }

#define Add_Reference(p) (p)->retain()

typedef ax::Point cPoint;
typedef ax::Size cSize;
typedef ax::Node cNode;
typedef ax::Vec2 cVec2;
typedef ax::Vec2 Vec2;

class Actor;
class IActorNodeController;
class INodeAnimationController;
class CharAnimController;
class NoChangeAnimController;
class AnimInfo;

// Component
class SceneComp;
class animController;
class BarComponent;



// 씬에다 그리기 기능,axmol node를 참조하고 mactor와 상호참조









class UnitComp;
class FarmerComp;
class MovementComp;


class ObjectSheet;
class MapLayer;
class UIlayer;
class InvWindow;

struct ActorMessage;

#pragma once

enum class Team
{
    Player,
    Enemy,
};
enum class Unit
{
    Item,
    Bullet,
    Actor
};
enum class E_UnitPose
{
    None,
    Idle,
    Move,
    Attack,
    Damaged,
    Watering,
    Die,
    Pos_Count
};

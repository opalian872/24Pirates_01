// NormalEnemy.h

#pragma once
#include "Enemy.h"

enum class NormalType
{
    Skeleton,
    Goblin,
    Snail,
    Orc,
    Hog,
    Zombie,
    Golem,
    Slime,
    Chimera
};

class NormalEnemy : public Enemy
{
public:
    // roomCount에 따른 레벨 스케일링
    NormalEnemy(NormalType type, int roomCount);

    virtual EnemySkill DetermineNextSkill() override;
};

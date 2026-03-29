// BossEnemy

#pragma once
#include "Enemy.h"

enum class BossType
{
    SkeletonKing,
    OrcKing
};

class BossEnemy : public Enemy
{
public:
    BossEnemy(BossType type, int roomCount);
    virtual EnemySkill DetermineNextSkill() override;

private:
    BossType bossType;
    // 페이즈 변환 있을 시 활성화
    // int phase =1;
};

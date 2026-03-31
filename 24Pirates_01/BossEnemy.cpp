//BossEnemy.cpp

#include "BossEnemy.h"
#include <ctime>
#include <cstdlib>

BossEnemy::BossEnemy(BossType type, int roomCount)
    : Enemy("", 0, 0, 0, 0, 0, roomCount), bossType(type)
{
    switch (type)
    {
    case BossType::SkeletonKing:
        engName = "Kernel Panic : The Skeleton King";
        maxHp = 750; atk = 50; def = 50; getExp = 50; getGold = 50;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "SHUT DOWN!!!", SkillType::Unique, atk * 2 });
        break;

    case BossType::OrcKing:
        engName = "Logical Error : The Orc King";
        maxHp = 750; atk = 50; def = 50; getExp = 50; getGold = 50;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5) });
        skills.push_back({ "Attack Boost", SkillType::Normal, 5 });
        skills.push_back({ "Illogicla Logic", SkillType::Unique, 10 });
        break;

    }

    ApplyScaling(roomCount);
    currentHp = maxHp;
}

EnemySkill BossEnemy::DetermineNextSkill()
{
    int roll = std::rand() % 100;

    if (roll < 40)
        return skills[0];
    else if (roll < 60)
        return skills[1];
    else if (roll < 80)
        return skills[2];
    else
        return skills[3];
}

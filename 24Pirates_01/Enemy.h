// Enemy.h

#pragma once
#include <string>
#include <vector>
#include <iostream>

// 스킬 타입 구분 (일반 / 고유)
enum class SkillType
{
    Normal,
    Unique
};

// 몬스터 스킬 구조체
struct EnemySkill
{
    std::string skillName;
    SkillType type;
    int skillValue;
};

class Enemy
{
protected:
    std::string engName;
    int maxHp;
    int currentHp;
    int atk;
    int def;
    int getExp;
    int getGold;

    // 스킬 목록
    std::vector<EnemySkill> skills;

    int turnCount = 0;

public:
    Enemy(std::string name, int baseHp, int baseAtk, int baseDef, int baseExp, int baseGold, int roomCount);
    virtual ~Enemy() = default;

    virtual void ApplyScaling(int roomCount);
    virtual void TakeDamage(int damage);
    bool IsDead() const;

    virtual EnemySkill DetermineNextSkill() = 0;
    void EndTurn() { turnCount++; }
};

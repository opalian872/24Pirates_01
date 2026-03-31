// NormalEnemy.cpp

#include "NormalEnemy.h"
#include <ctime>
#include <cstdlib>

NormalEnemy::NormalEnemy(NormalType type, int roomCount)
// 부모 생성자에는 기본값을 넘기고, 내부에서 상세 스탯을 세팅합니다.
    : Enemy("", 0, 0, 0, 0, 0, roomCount)
{
    switch (type)
    {
    case NormalType::Skeleton:
        engName = "The Memory Leaked Skeleton";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;
        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Memory Trace", SkillType::Unique, 0 });
        break;

    case NormalType::Goblin:
        engName = "Semicolon Thief Goblin";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "Thief Semicolon", SkillType::Unique, 0 });
        break;

    case NormalType::Snail:
        engName = "The Infinite Loop Snail";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack Boost", SkillType::Normal, 3 });
        skills.push_back({ "Defense Boost", SkillType::Normal, 3 });
        skills.push_back({ "Command Overlap", SkillType::Unique, 5 });
        break;

    case NormalType::Orc:
        engName = "The Null Pointer Orc";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Blind Reference", SkillType::Unique, -65535 });
        break;

    case NormalType::Hog:
        engName = "Permission Denied Hog";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "Unauthorized Access", SkillType::Unique, atk });
        break;

    case NormalType::Zombie:
        engName = "Missing Virtual Zombie";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Life Drain", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "So, Who are you?", SkillType::Unique, 0 });
        break;

    case NormalType::Golem:
        engName = "Inline Failed Golem";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Critical Hit", SkillType::Normal, atk });
        skills.push_back({ "Tooooo Heavy", SkillType::Unique, atk });
        break;

    case NormalType::Slime:
        engName = "One-Liner Slime";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heal", SkillType::Normal, static_cast<int>(maxHp * 0.1f) });
        skills.push_back({ "I Can See it All", SkillType::Unique, 2 });
        break;

    case NormalType::Chimera:
        engName = "Zero-Indent Chimera";
        maxHp = 20; atk = 5; def = 5; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5) });
        skills.push_back({ "OneWay", SkillType::Unique, 5 });
        break;
    }

    ApplyScaling(roomCount);
    currentHp = maxHp;
}

EnemySkill NormalEnemy::DetermineNextSkill()
{
    if (engName == "Missing Virtual Zombie" ||
        engName == "Permission Denied Hog" ||
        engName == "Inline Failed Golem" ||
        engName == "One-Liner Slime" ||
        engName == "Zero-Indent Chimera")
    {
        int roll = std::rand() % 100;

        if (roll < 50)
            return skills[0];
        else if (roll < 75)
            return skills[1];
        else
            return skills[2];
    }

    if (engName == "The Null Pointer Orc")
    {
        if (currentHp < (maxHp * 0.2f))
        {
            return skills[2]; // Blind Reference 사용
        }

        int roll = std::rand() % 100;
        if (roll < 75)
            return skills[0];
        else
            return skills[1];
    }

    if (!skills.empty())
    {
        int randomIndex = std::rand() % 3;
        return skills[randomIndex];
    }

    return { "None", SkillType::Normal, 0 }; // 예외 방지용
}

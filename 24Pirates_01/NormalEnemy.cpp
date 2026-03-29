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
        maxHp = 10; atk = 5; def = 3; getExp = 10; getGold = 10;
        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Memory Trace", SkillType::Unique, 0 });
        break;

    case NormalType::Goblin:
        engName = "Semicolon Thief Goblin";
        maxHp = 20; atk = 10; def = 6; getExp = 20; getGold = 20;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        // Skill 2: 연속 공격 (공격력의 50%를 밸류로 저장)
        // 실제 '2번 공격' 로직은 나중에 BattleRoom에서 이 스킬 이름이나 ID를 체크하여 처리합니다.
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        // Skill 3: [고유] 세미콜론 훔치기 (피해 무효화 기믹)
        // 데미지 자체가 목적이 아니므로 밸류는 0으로 둡니다.
        skills.push_back({ "Thief Semicolon", SkillType::Unique, 0 });
        break;

    case NormalType::Snail:
        engName = "The Infinite Loop Snail";
        maxHp = 30; atk = 15; def = 9; getExp = 30; getGold = 30;

        skills.push_back({ "Attack Boost", SkillType::Normal, 3 });
        skills.push_back({ "Defense Boost", SkillType::Normal, 3 });
        skills.push_back({ "Command Overlap", SkillType::Unique, 5 });
        break;

    case NormalType::Orc:
        engName = "The Null Pointer Orc";
        maxHp = 40; atk = 20; def = 12; getExp = 40; getGold = 40;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heavy Strike", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Blind Reference", SkillType::Unique, -65535 });
        break;

    case NormalType::Hog:
        engName = "Permission Denied Hog";
        maxHp = 50; atk = 25; def = 15; getExp = 50; getGold = 50;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Multiple Attacks", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "Unauthorized Access", SkillType::Unique, atk });
        break;

    case NormalType::Zombie:
        engName = "Missing Virtual Zombnie";
        maxHp = 60; atk = 30; def = 18; getExp = 60; getGold = 60;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Life Drain", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "So, Who are you?", SkillType::Unique, 0 });
        break;

    case NormalType::Golem:
        engName = "Inline Failed Golem";
        maxHp = 70; atk = 35; def = 21; getExp = 70; getGold = 70;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Critical Hit", SkillType::Normal, atk });
        skills.push_back({ "Tooooo Heavy", SkillType::Unique, atk });
        break;

    case NormalType::Slime:
        engName = "One-Liner Slime";
        maxHp = 80; atk = 40; def = 24; getExp = 80; getGold = 80;

        skills.push_back({ "Attack", SkillType::Normal, atk });
        skills.push_back({ "Heal", SkillType::Normal, static_cast<int>(maxHp * 0.1f) });
        skills.push_back({ "I Can See it All", SkillType::Unique, 2 });
        break;

    case NormalType::Chimera:
        engName = "Zero-Indent Chimera";
        maxHp = 90; atk = 45; def = 27; getExp = 90; getGold = 90;

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

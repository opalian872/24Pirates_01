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
        maxHp = 40; atk =16; def = 4; getExp = 30; getGold = 10;
        skills.push_back({ "Bone Attack", SkillType::Normal, atk });
        skills.push_back({ "Scull Crush!!", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Bone Head", SkillType::Unique, 0 });
        break;

    case NormalType::Goblin:
        engName = "Semicolon Thief Goblin";
        maxHp = 40; atk = 16; def = 6; getExp = 30; getGold = 15;

        skills.push_back({ "Goblin Stab Attack", SkillType::Normal, atk });
        skills.push_back({ "ATTACKKKK!!!!!", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "SUPER GOBLIN BRAIN STORMING(Do Nothing)", SkillType::Unique, 0 });
        break;

    case NormalType::Snail:
        engName = "The Infinite Loop Snail";
        maxHp = 30; atk = 4; def = 16; getExp = 30; getGold = 15;

        skills.push_back({ "Special Snail Cream Attack", SkillType::Normal, atk});
        skills.push_back({ "SUPER FAST MOVING", SkillType::Normal, 0 });
        skills.push_back({ "Doing Something Fast", SkillType::Unique, 1 });
        break;

    case NormalType::Orc:
        engName = "The Null Pointer Orc";
        maxHp = 50; atk = 16; def = 10; getExp = 40; getGold = 20;

        skills.push_back({ "Orc Thumping Attack", SkillType::Normal, atk });
        skills.push_back({ "Orc Smash", SkillType::Normal, static_cast<int>(atk * 1.5f) });
        skills.push_back({ "Blind Reference", SkillType::Unique, -65535 });
        break;

    case NormalType::Hog:
        engName = "Permission Denied Hog";
        maxHp = 100; atk = 20; def = 20; getExp = 40; getGold = 15;

        skills.push_back({ "Rush", SkillType::Normal, atk });
        skills.push_back({ "RU-----------------SH", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "SUPER FAST RUSH", SkillType::Unique, atk });
        break;

    case NormalType::Zombie:
        engName = "Missing Virtual Zombie";
        maxHp = 100; atk = 30; def = 10; getExp = 40; getGold = 15;

        skills.push_back({ "Zombie Claw Attack", SkillType::Normal, atk });
        skills.push_back({ "Fatching Somthing", SkillType::Normal, static_cast<int>(atk * 0.5f) });
        skills.push_back({ "Empty Head Attack", SkillType::Unique, 0 });
        break;

    case NormalType::Golem:
        engName = "Inline Failed Golem";
        maxHp = 150; atk = 20; def = 30; getExp = 50; getGold = 20;

        skills.push_back({ "Golem Attack", SkillType::Normal, atk });
        skills.push_back({ "Golem Hyper Attack", SkillType::Normal, atk });
        skills.push_back({ "Rocking Ducking Attack", SkillType::Unique, atk });
        break;

    case NormalType::Slime:
        engName = "One-Liner Slime";
        maxHp = 120; atk = 20; def = 25; getExp = 50; getGold = 25;

        skills.push_back({ "Slime Smile Attack", SkillType::Normal, atk });
        skills.push_back({ "Self Healing", SkillType::Normal, static_cast<int>(maxHp * 0.1f) });
        skills.push_back({ "Slime Jump", SkillType::Unique, 2 });
        break;

    case NormalType::Chimera:
        engName = "Zero-Indent Chimera";
        maxHp = 250; atk = 25; def =35; getExp = 50; getGold =40;

        skills.push_back({ "Somthing Terrible Attack", SkillType::Normal, atk });
        skills.push_back({ "Maybe Awesome Attack", SkillType::Normal, static_cast<int>(atk * 0.5) });
        skills.push_back({ "Claw Addvenced", SkillType::Unique, 5 });
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

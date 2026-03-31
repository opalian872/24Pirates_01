//UIData.h
#pragma once
#include "CardDatabase.h"
#include <string>


class Deck;
struct DummyEnemy;


//어떤 UI를 표시할 것인지 표시해주기
enum class BattleUIState
{
    Default,
    ChooseCard,
    ChooseCardTarget,
    CheckDeck,
    EnemyTurn,
    Clear
};

struct CardData
{
    CardID id;
    std::string name;
    std::string rarity;
    std::string effectText;
    bool isPlayableInHand;
    TargetType targetType;
    bool isEmpty;
    CardData()
        : id(CardID::Strike), name(""), rarity(""), effectText(""), isPlayableInHand(false), targetType(TargetType::None), isEmpty(true)
    {
    }

    CardData(CardID id, const std::string& name, const std::string& rarity, const std::string& effectText, bool isPlayableInHand, TargetType targetType)
        : id(id), name(name), rarity(rarity), effectText(effectText), isPlayableInHand(isPlayableInHand), targetType(targetType), isEmpty(false)
    {
    }
};
struct EnemyData
{
    std::string name;
    int maxHp;
    int currentHp;
    int atk;
    int def;
    int getExp;
    int getGold;
};

struct UIData
{
    std::string playerName;
    int playerLevel;
    int playerExp;
    int playerGold;
    int playerCurrentHealth;
    int playerMaxHealth;
    int playerAttack;
    int playerDefense;
    std::vector<CardData> playerDeck;
    std::vector<CardData> playerHand;
    std::vector<EnemyData> enemies;
    //const std::vector<DummyEnemy>* enemies = nullptr;
    std::vector<std::string> currentLog;
};

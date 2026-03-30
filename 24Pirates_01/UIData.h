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
};

struct CardData
{
    CardID id;
    std::string name;
    std::string rarity;
    std::string effectText;
    bool isEmpty;
    CardData()
        : id(CardID::Strike), name(""), rarity(""), effectText(""), isEmpty(true)
    {
    }

    CardData(CardID id, const std::string& name, const std::string& rarity, const std::string& effectText)
        : id(id), name(name), rarity(rarity), effectText(effectText), isEmpty(false)
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

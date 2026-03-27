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

struct UIData
{
    std::string playerName;
    int playerCurrentHealth;
    int playerMaxHealth;
    int playerAttack;
    int playerDefense;
    Deck* playerDeck = nullptr;
    const std::vector<DummyEnemy>* enemies = nullptr;
};

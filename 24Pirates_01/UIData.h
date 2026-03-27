//UIData.h
#pragma once
#include "CardDatabase.h"
#include <string>


class Deck;
struct DummyEnemy;


enum class UIState
{
    Default,
    ChooseCard,
    ChooseCardTarget,
    EnemyTurn
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

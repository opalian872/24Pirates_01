#pragma once

#include <string>
#include "Deck.h"
#include "CardDatabase.h"

struct Player
{
private:
    std::string playerName;
    int level;
    int maxHp;
    int hp;
    int attack;
    int defense;
    int exp;
    int gold;
    bool playerCondition; // 플레이어의 생존상태 유무. 기본값 true


public:
    void PlayerMaking(std::string inname, int inlevel, int inmaxHp, int inhp, int inattack, int indefense, int inexp, int ingold, bool inplayerCondition);
    void CreateStarterDeck(const CardDatabase& database);
    void GainExp(int expAmount, std::string gainEMsg); // gainexp == 받는 경험치 임시 변수
    void LevelUp(std::string levelMsg);
    void GainGold(int goldAmount, std::string gainGMsg); // gaingold == 받는 골드 임시 변수
    void TakeDamage(int damage, std::string takeDMsg1, std::string takeDMsg2, std::string takeDMsg3, std::string takeDMsg4); // damage == 받는 대미지 임시 변수
    void Heal(int healAmount, std::string healMsg1, std::string healMsg2); // heal == 받는 회복 임시 변수
    void UseCard();

    void AddCardToDeck(Card* card);
    void AddCardToDeckByID(const CardDatabase& database, CardID id);
    void ShowMyDeck();
    int GetDeckSize();
    Card* GetDeckCard(int index);
    void RemoveDeckCard(int index);

    // Player 클래스 Getter 함수입니다.
    std::string GetName();
    int GetHp();
    int GetMaxHp();
    int GetAttack();
    int GetDefense();
    int GetExp();
    int GetGold();
    bool GetPlayerCondition();

    Deck playerDeck;
};

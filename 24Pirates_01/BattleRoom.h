//BattleRoom.h
#pragma once
#include <vector>
#include <string>
#include "UIData.h"
#include "BattleUI.h"
#include "Player.h"
#include "NormalEnemy.h"
#include "BossEnemy.h"
#include "Deck.h" //Deck 헤더 


//더미용 enemy struct
struct DummyEnemy
{
    std::string name;
    int currentHealth;
    int maxHealth;
    int attack;
    int defense;
    int killGold;
    int killExp;
};
//더미용 player struct
struct DummyPlayer
{
    std::string name;
    int currentHealth;
    int maxHealth;
    int attack;
    int defense;
};



class BattleRoom
{
private:
	Player& player;
	//CardDatabase& cardDatabase;
	//std::vector<std::unique_ptr<Enemy>> enemies; -> Enemy 자식 클래스들 소환하기 위한 방법
	BattleUI battleUI;
	bool playerTurn = true;
	bool isRunning = true;
    const int roomCount;
    //Deck* playerDeck; //포인터 추가
    UIData data; //UI에 넘겨줄 데이터 묶음
    BattleUIState battleUIState; // 어떤 화면을 렌더링할지 정해주기
    std::vector<std::string> currentLog;
	//여기서부턴 테스트용 더미데이터입니다.
	std::vector<DummyEnemy> enemies;
public:
	BattleRoom(int roomCount, Player& player); // 원래는 BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies); Deck 생성자 추가
	int Run();
	void Reward();
	void PlayerTurnRun();
    void WaitForEnter();
    std::string RarityToString(CardRarity rarity) const;
    std::vector<CardData> PackageCards();
    //추후 플레이어 hand 도 package 하는 override 함수 구현 예정
    void RenewUI();

};


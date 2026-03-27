//BattleRoom.h
#pragma once
#include <vector>
#include <string>
#include "UIData.h"
#include "BattleUI.h"
//#include "Player.h"
//#include "Enemy.h"
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
	//Player& player;
	//CardDatabase& cardDatabase;
	//std::vector<std::unique_ptr<Enemy>> enemies; -> Enemy 자식 클래스들 소환하기 위한 방법
	BattleUI battleUI;
	bool playerTurn = true;
	bool isRunning = true;
    const int roomCount;
    Deck* playerDeck; //포인터 추가
    UIData data; //UI에 넘겨줄 데이터 묶음
	//여기서부턴 테스트용 더미데이터입니다.
	DummyPlayer player = { "ParkKyeongHo", 100, 200, 30, 30 };
	std::vector<DummyEnemy> enemies;
public:
	BattleRoom(int roomCount, Deck* playerDeck); // 원래는 BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies); Deck 생성자 추가
	int Run();
	void Reward();
	void PlayerTurnRun();
    void WaitForEnter();
    void PackageUIData();

};


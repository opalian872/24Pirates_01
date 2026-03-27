//BattleRoom.h
#pragma once
#include <vector>
#include <string>
#include "BattleUI.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "CardDatabase.h"



//더미용 enemy struct
struct Enemy
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
struct Player
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
	//여기서부턴 테스트용 더미데이터입니다.
	Player player = { "ParkKyeongHo", 100, 200, 30, 30 };
	std::vector<Enemy> enemies;
public:
	BattleRoom(int roomCount); // 원래는 BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies);
	int Run();
	void Reward();
	void PlayerTurnRun();
    void WaitForEnter();

};


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


class BattleRoom
{
private:
	Player& player;
	BattleUI battleUI;
	bool playerTurn = true;
	bool isRunning = true;
    const int roomCount;
    UIData data; //UI에 넘겨줄 데이터 묶음
    BattleUIState battleUIState; // 어떤 화면을 렌더링할지 정해주기
    std::vector<std::string> currentLog;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<EnemyData> enemiesData;
public:
	BattleRoom(int roomCount, Player& player, std::vector<std::unique_ptr<Enemy>> enemies);
	int Run();
	void Reward();
	void PlayerTurnRun();
    void WaitForEnter();
    std::string RarityToString(CardRarity rarity) const;
    std::vector<CardData> PackageDeck();
    std::vector<CardData> PackageHand();
    void RenewUI();

};


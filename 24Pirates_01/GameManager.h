//GameManager.h
#pragma once
//#include "Player.h"
#include "Deck.h" // deck추가
#include "CardDatabase.h" // carddatabase 추가
#include "StartMenuUI.h"
#include "BattleUI.h"
#include "BattleRoom.h"
#include <iostream>

enum class GameState
{
	Start,
	InBattle,
	InShop,
	GameOver,
	Clear
};

class GameManager
{
private:
	GameState currentState;
	StartMenuUI startMenuUI;
	int roomCount;
	bool isRunning;
    CardDatabase cardDatabase; // 카드데이터 베이스 추가
    Deck playerDeck; // 플레이어 deck 추가
	//Player myPlayer; << GameManager가 플레이어를 들고 있는 형태로 이렇게 구현하려고 합니다.
	//CardDatabase cardDatabase << 전체 카드 도감을 넣어 주시면 다른 메뉴들에서 불러오기 쉬울 거 같습니다.

public:
	GameManager();
	void Run();
	void GenerateRoom();
	void RunStartMenu();
	int RunBattleRoom();
	void RunShopRoom();
	void RunGameOver();
	void RunClear();
	void WaitForEnter();
};


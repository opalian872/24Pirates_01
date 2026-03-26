//GameManager.cpp

#include <iostream>
#include <limits>
#include "GameManager.h"

GameManager::GameManager() :currentState(GameState::Start), roomCount(0), isRunning(true)
{

}

void GameManager::Run()
{
	while (isRunning)
	{
		switch (currentState)
		{
		case GameState::Start:
			RunStartMenu();
			break;
		case GameState::InBattle:
			RunBattleRoom();
			if (currentState != GameState::GameOver)
			{
				GenerateRoom();
			}
			break;
		case GameState::InShop:
			RunShopRoom();
			GenerateRoom();
			break;
		case GameState::GameOver:
			RunGameOver();
			break;
		case GameState::Clear:
			RunClear();
			break;
		}
	}
}

void GameManager::GenerateRoom()
{
	if (roomCount != 10)
	{
		if (roomCount % 3 != 0)
		{
			currentState = GameState::InBattle;
		}
		else
		{
			currentState = GameState::InShop;
		}
	}
	else
	{
		currentState = GameState::InBattle;
	}
}

void GameManager::RunStartMenu() // 여기서 StartingUI 를 불러옵니다.
{
	std::string inputName;
	startMenuUI.Render();
	std::cin >> inputName;
	startMenuUI.ClearScreen();
	startMenuUI.Render(inputName);
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); //전에 입력 받았으므로
	WaitForEnter();
	currentState = GameState::InBattle;
	roomCount++;
}
void GameManager::RunBattleRoom() // 여기서 BattleRoom을 불러옵니다. player와 vector<Enemy>, cardDatabase를 가지고 들어갈 거 같습니다.
{
	std::cout << "Current Room: " << roomCount << " Battle has begun!" << std::endl;
    BattleUI battleUI = BattleUI(roomCount);
    if (roomCount != 10)
	{
        battleUI.Render();
		roomCount++;
		WaitForEnter();
	}
	else
	{
		std::cout << "Current Room: " << roomCount <<" Battle has ended. You Lost" << std::endl;
		currentState = GameState::GameOver;
	}
}
void GameManager::RunShopRoom() //여기서 ShopRoom을 불러옵니다
{
	std::cout << "Current Room: " << roomCount << " In Shop!" << std::endl;
	std::cout << "Shopping ended." << std::endl;
	WaitForEnter();
	roomCount++;
}
void GameManager::RunGameOver()//여기서 Game Over 스크린을 불러옵니다
{
	std::cout << "Game Over! Number of rooms passed: " << (roomCount - 1) << std::endl;
	isRunning = false;
}
void GameManager::RunClear() //여기서 Clear 스크린을 불러옵니다
{
	std::cout << "Clear!" << std::endl;
	isRunning = false;
}

void GameManager::WaitForEnter()
{
	std::cout << "Press Enter to Proceed";
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 전에 입력 받았을 때만
	std::cin.get();
}

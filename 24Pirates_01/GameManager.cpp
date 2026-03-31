//GameManager.cpp

#include <iostream>
#include <limits>
#include <random>
#include <algorithm>
#include "GameManager.h"
#include "ShopRoom.h"
#include "ShopManager.h"
#include "Player.h"

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
        {
            int battleResult = RunBattleRoom();
            if (battleResult == 1)
            {
                currentState = GameState::GameOver;
            }
            else if (battleResult == 2)
            {
                currentState = GameState::Clear;
            }
            else
            {
                roomCount++;
                GenerateRoom();
            }
            break;
        }
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
            enemies.clear();
            switch (roomCount)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
            case 1:
            case 2:
                std::uniform_int_distribution<int> uniformDist(0, 3);
                for (int i = 0; i < 3; i++)
                {
                    NormalType type = static_cast<NormalType>(uniformDist(gen));
                    enemies.push_back(std::make_unique<NormalEnemy>(type, roomCount));
                }
                break;
            case 4:
            case 5:
                std::uniform_int_distribution<int> uniformDist(2, 5);
                for (int i = 0; i < 3; i++)
                {
                    NormalType type = static_cast<NormalType>(uniformDist(gen));
                    enemies.push_back(std::make_unique<NormalEnemy>(type, roomCount));
                }
                break;
            case 7:
            case 8:
                std::uniform_int_distribution<int> uniformDist(5, 8);
                for (int i = 0; i < 3; i++)
                {
                    NormalType type = static_cast<NormalType>(uniformDist(gen));
                    enemies.push_back(std::make_unique<NormalEnemy>(type, roomCount));
                }
                break;        
            }
       
        }
		else
		{
			currentState = GameState::InShop;
		}
	}
	else
	{
        currentState = GameState::InBattle;
        enemies.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> bossDist(0, 1);
        int roll = bossDist(gen);

        if (roll == 0)
        {
            enemies.push_back(std::make_unique<BossEnemy>(BossType::SkeletonKing, roomCount));
        }
        else
        {
            enemies.push_back(std::make_unique<BossEnemy>(BossType::OrcKing, roomCount));
        }
	}
}

void GameManager::RunStartMenu() // 여기서 StartingUI 를 불러옵니다.
{
	std::string inputName;
	startMenuUI.Render();
	std::cin >> inputName;
	startMenuUI.ClearScreen();
	startMenuUI.Render(inputName);
    myPlayer.PlayerMaking(inputName, 1, 200, 200, 30, 0, 0, 100, true);
    myPlayer.CreateStarterDeck(cardDatabase);
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); //전에 입력 받았으므로
	WaitForEnter();
	currentState = GameState::InBattle;
	roomCount++;
    GenerateRoom();
}
int GameManager::RunBattleRoom() // 여기서 BattleRoom을 불러옵니다. player와 vector<Enemy>, cardDatabase를 가지고 들어갈 거 같습니다.
{
    int clearState;
    BattleRoom battleRoom(roomCount, myPlayer, std::move(enemies));
    clearState = battleRoom.Run();
    return clearState; // clearState 가 0이면 일반방 클리어, 1이면 GameOver, 2이면 Clear
}
void GameManager::RunShopRoom() //여기서 ShopRoom을 불러옵니다
{
    ShopManager shopManager(cardDatabase, myPlayer.playerDeck, myPlayer);
    ShopRoom shopRoom(roomCount, shopManager);
    shopRoom.ShowMenu();

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

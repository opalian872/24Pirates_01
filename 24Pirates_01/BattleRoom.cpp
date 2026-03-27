//BattleRoom.cpp
#include <iostream>
#include "BattleRoom.h"
#include <random> //현재는 10번 방 클리어 or 실패 나타내기 위해 쓴 랜덤함수.


BattleRoom::BattleRoom(int roomCount): roomCount(roomCount), playerTurn(true), isRunning(true), battleUI(roomCount)  //원래는 BattleRoom::BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies)
{
    //더미용 enemy
	enemies.push_back({ "Goblin", 100, 100, 10, 10, 50, 50 });
	enemies.push_back({ "Dragon", 500, 500, 50, 20, 500, 500 });
}

int BattleRoom::Run() //지금 당장은 더미입니다.
//0, 1, 2 int 리턴값으로 방 클리어, 게임 오버, 게임 전체 클리어 표시할 예정입니다
{
    if (roomCount != 10)
    {
        battleUI.Render();
        WaitForEnter();
        return 0;
    }
    else
    {
        std::random_device rd;//1 or 2 랜덤하게
        int randomClear = (rd() % 2);
        if (randomClear == 0)
        {
            battleUI.Render();
            std::cout << "Current Room: " << roomCount << " Battle has ended. You Lost!" << std::endl;
            WaitForEnter();
            return 1;
        }
        else
        {
            battleUI.Render();
            std::cout << "Current Room: " << roomCount << " Battle has ended. You Cleared!" << std::endl;
            WaitForEnter();
            return 2;
        }
    }




    //while (isRunning)
	//{
		//if (playerTurn)
		//{
			//플레이어가 선택하는 행동들이 여기서 동작합니다. 행동마다 전투가 종료되었는지 체크합니다.
		//}
		//else
		//{
			//적이 선택하는 동작들이 여기서 동작합니다.
		//}
	//}
	//return;
}

void BattleRoom::Reward()
{
	int totalExp = 0;
	int totalGold = 0;
	//for(const auto& enemy: enemies)
	//{
	//   totalExp +=enemy->killExp;
	//   totalGold +=enemy->killGold;
	//}
	for (const Enemy& enemy : enemies)
	{
		totalExp += enemy.killExp;
		totalGold += enemy.killGold;
	}
	//player->giveExp(); 이런 걸로 레벨업 체크 해줬으면 좋겠네요. 어떻게 UI화면에 병합할지는 나중에 생각해 보는걸로
	//player->addGold();
	return;
}

void BattleRoom::PlayerTurnRun() 
{
	bool playerTurnIsRunning = true;
	int choice = -1;
	//ui.render() 이 메서드로 화면 UI를 만들 겁니다.
	//std::cin >>choice;
	while (playerTurnIsRunning)
	{
		switch (choice)
		{
		case 1: 
		case 2:
		case 3:
		default:
			break;
		}
	}

}

void BattleRoom::WaitForEnter()
{
    std::cout << "Press Enter to Proceed";
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 전에 입력 받았을 때만
    std::cin.get();
}

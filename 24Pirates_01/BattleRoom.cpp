//BattleRoom.cpp
#include <iostream>
#include "BattleRoom.h"
#include "Card.h"
#include <random> //현재는 10번 방 클리어 or 실패 나타내기 위해 쓴 랜덤함수.
#include <string>


BattleRoom::BattleRoom(int roomCount, Player& player, std::vector<std::unique_ptr<Enemy>> enemies): roomCount(roomCount), player(player), enemies(std::move(enemies)),
playerTurn(true), isRunning(true), battleUI(roomCount), battleUIState(BattleUIState::Default)
//원래는 BattleRoom::BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies) Deck 포인터 추가
{
    
}

int BattleRoom::Run() //지금 당장은 더미입니다.
//0, 1, 2 int 리턴값으로 방 클리어, 게임 오버, 게임 전체 클리어 표시할 예정입니다
{
    player.playerHand.DrawCards(player.playerDeck, 5, player);
    RenewUI();
    WaitForEnter();
    /*int choice = 0;
    while (isRunning)
    {
        battleUIState = BattleUIState::Default;
        while (playerTurn)
        {
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                continue;
            }
            switch (choice)
            {
            case 1:
                battleUIState = BattleUIState::ChooseCard;

            }
                
        }
    }*/

    /*while (player.currentHealth > 0 && enemies.size() > 0)
    {
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        case 2:
        default:
            break;
        }
        break;
    }*/


    return 0;

    //if (roomCount != 10)
    //{
    //    battleUI.Render();

    //    if (playerDeck != nullptr)
    //    {
    //        std::cout << "\n=== My Cards ===\n";

    //        if (playerDeck->getCardCount() == 0)
    //        {
    //            std::cout << "Deck is empty.\n";
    //        }
    //        else
    //        {
    //            for (int i = 0; i < playerDeck->getCardCount(); i++)
    //            {
    //                Card* card = playerDeck->getCard(i);

    //                if (card != nullptr)
    //                {
    //                    std::cout << "[" << i + 1 << "] "
    //                        << card->getName()
    //                        << " | "
    //                        << card->getEffectText()
    //                        << "\n";
    //                }
    //            }
    //        }
    //    }
    //    else
    //    {
    //        std::cout << "\nDeck is not connected.\n";
    //    }

    //    WaitForEnter();
    //    return 0;
    //}
    //else
    //{
    //    std::random_device rd;//1 or 2 랜덤하게
    //    int randomClear = (rd() % 2);
    //    if (randomClear == 0)
    //    {
    //        battleUI.Render();
    //        std::cout << "Current Room: " << roomCount << " Battle has ended. You Lost!" << std::endl;
    //        WaitForEnter();
    //        return 1;
    //    }
    //    else
    //    {
    //        battleUI.Render();
    //        std::cout << "Current Room: " << roomCount << " Battle has ended. You Cleared!" << std::endl;
    //        WaitForEnter();
    //        return 2;
    //    }
    //}




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
	for (const auto& enemy : enemies)
	{
		//totalExp += enemy; <<<enemy에 get, set 함수 필요
		//totalGold += enemy.killGold;
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

std::string BattleRoom::RarityToString(CardRarity rarity) const
{
    switch (rarity)
    {
    case CardRarity::Normal:
        return "Normal";
    case CardRarity::Rare:
        return "Rare";
    case CardRarity::Epic:
        return "Epic";
    default:
        return "Unknown";
    }
}
std::vector<CardData> BattleRoom::PackageDeck()
{
    std::vector<CardData> cardsData;
    for (int i = 0; i < player.playerDeck.getCardCount(); i++)
        {
        CardData cardData(player.playerDeck.getCard(i)->getID(), player.playerDeck.getCard(i)->getName(), RarityToString(player.playerDeck.getCard(i)->getRarity()), player.playerDeck.getCard(i)->getEffectText());
            cardsData.push_back(cardData);
        }
    return cardsData;
}

std::vector<CardData> BattleRoom::PackageHand()
{
    std::vector<CardData> cardsData;
    for (int i = 0; i < player.playerHand.getCardCount(); i++)
    {
        CardData cardData(player.playerHand.getCard(i)->getID(), player.playerHand.getCard(i)->getName(), RarityToString(player.playerHand.getCard(i)->getRarity()), player.playerHand.getCard(i)->getEffectText());
        cardsData.push_back(cardData);
    }
    return cardsData;
}
void BattleRoom::RenewUI()
{
    enemiesData.clear();
    for (const auto& enemy : enemies)
    {
        enemiesData.push_back({ enemy->GetName(), enemy->GetMaxHp(), enemy->GetCurrentHp(), enemy->GetAtk(), enemy->GetDef(), enemy->GetExp(), enemy->GetGold()});
    }
    data.playerName = player.GetName();
    data.playerCurrentHealth = player.GetHp();
    data.playerMaxHealth = player.GetMaxHp();;
    data.playerAttack = player.GetAttack();
    data.playerDefense = player.GetDefense();
    data.playerDeck = PackageDeck();
    data.playerHand = PackageHand();
    data.enemies = enemiesData;
    data.currentLog = currentLog;
    battleUI.Render(data, battleUIState);
    return;
}

bool BattleRoom::CheckForClear()
{
    if (player.GetPlayerCondition());

    return true;
}

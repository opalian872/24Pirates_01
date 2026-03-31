//BattleRoom.cpp
#include <iostream>
#include "BattleRoom.h"
#include "Card.h"
#include <random> //현재는 10번 방 클리어 or 실패 나타내기 위해 쓴 랜덤함수.
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace
{
    int ReadIntChoice()
    {
        while (true)
        {
            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            int value;
            char extra;

            if ((ss >> value) && !(ss >> extra))
            {
                return value;
            }

            std::cout << " Invalid input. Choose again: ";
        }
    }

    std::vector<int> BuildPlayableHandIndices(const Hand& hand)
    {
        std::vector<int> result;

        for (int i = 0; i < hand.getCardCount(); i++)
        {
            Card* card = hand.getCard(i);

            if (card != nullptr && card->IsPlayableInHand())
            {
                result.push_back(i);
            }
        }

        return result;
    }

    void RemoveDeadEnemies(std::vector<std::unique_ptr<Enemy>>& enemies)
    {
        enemies.erase(
            std::remove_if(
                enemies.begin(),
                enemies.end(),
                [](const std::unique_ptr<Enemy>& enemy)
                {
                    return enemy == nullptr || enemy->IsDead();
                }),
            enemies.end());
    }

    void RunEnemyTurnDummy(Enemy& enemy, Player& player, std::vector<std::string>& currentLog)
    {
        EnemySkill skill = enemy.DetermineNextSkill();
        currentLog.push_back(enemy.GetName() + " used " + skill.skillName + ".");

        if (skill.skillName == "Attack Boost")
        {
            enemy.SetAtk(enemy.GetAtk() + skill.skillValue);
            return;
        }

        if (skill.skillName == "Defense Boost")
        {
            enemy.SetDef(enemy.GetDef() + skill.skillValue);
            return;
        }

        if (skill.skillName == "Heal")
        {
            enemy.SetCurrentHp(enemy.GetCurrentHp() + skill.skillValue);
            return;
        }

        if (skill.skillName == "Multiple Attacks")
        {
            player.TakeDamage(
                skill.skillValue,
                enemy.GetName() + "'s attack could not break your defense.",
                enemy.GetName() + " dealt damage: ",
                "You were defeated.",
                "Game Over."
            );

            if (player.GetPlayerCondition())
            {
                player.TakeDamage(
                    skill.skillValue,
                    enemy.GetName() + "'s second attack could not break your defense.",
                    enemy.GetName() + " dealt damage: ",
                    "You were defeated.",
                    "Game Over."
                );
            }

            enemy.EndTurn();
            return;
        }

        int damage = skill.skillValue;

        if (damage <= 0)
        {
            damage = enemy.GetAtk();
        }

        player.TakeDamage(damage, enemy.GetName() + "'s attack could not break your defense.",
            enemy.GetName() + " dealt damage: ",
            "You were defeated.",
            "Game Over."
        );

        enemy.EndTurn();
    }
}


BattleRoom::BattleRoom(int roomCount, Player& player, std::vector<std::unique_ptr<Enemy>> enemies): roomCount(roomCount), player(player), enemies(std::move(enemies)),
playerTurn(true), isRunning(true), battleUI(roomCount), battleUIState(BattleUIState::Default)
//원래는 BattleRoom::BattleRoom(Player& player, std::vector<std::unique_ptr<Enemy>> enemies) Deck 포인터 추가
{
    
}

int BattleRoom::Run() //지금 당장은 더미입니다.
//0, 1, 2 int 리턴값으로 방 클리어, 게임 오버, 게임 전체 클리어 표시할 예정입니다
{
    isRunning = true;
    playerTurn = true;
    //방 끝났을 때 플레이어 리셋/보상 지급용 변수들
    originalAttack = player.GetAttack();
    originalDefense = player.GetDefense();
    for (const auto& enemy : enemies)
    {
        totalExp += enemy->GetExp();
        totalGold += enemy->GetGold();
    }

    battleUIState = BattleUIState::Default;
    currentLog.clear();
    currentLog.push_back("Battle Start!");

    player.playerHand.DrawCards(player.playerDeck, 5, player);

    while (isRunning)
    {
        if (!player.GetPlayerCondition())
        {
            return 1;
        }

        if (enemies.empty())
        {
            isRunning = false;
            continue;
        }

        if (playerTurn)
        {
            battleUIState = BattleUIState::Default;
            RenewUI();

            int choice = ReadIntChoice();

            switch (choice)
            {
            case 1:
            {
                std::vector<int> playableIndices = BuildPlayableHandIndices(player.playerHand);

                if (playableIndices.empty())
                {
                    currentLog.push_back("There are no playable cards in hand.");
                    break;
                }

                battleUIState = BattleUIState::ChooseCard;
                RenewUI();

                int cardChoice = ReadIntChoice();

                if (cardChoice == 0)
                {
                    battleUIState = BattleUIState::Default;
                    break;
                }

                if (cardChoice < 1 || cardChoice > static_cast<int>(playableIndices.size()))
                {
                    currentLog.push_back("Invalid card choice.");
                    battleUIState = BattleUIState::Default;
                    break;
                }

                int realHandIndex = playableIndices[cardChoice - 1];
                Card* selectedCard = player.playerHand.getCard(realHandIndex);

                if (selectedCard == nullptr)
                {
                    currentLog.push_back("Selected card is invalid.");
                    battleUIState = BattleUIState::Default;
                    break;
                }

                int targetIndex = -1;

                if (selectedCard->getTargetType() == TargetType::SingleEnemy)
                {
                    if (enemies.empty())
                    {
                        currentLog.push_back("There is no target.");
                        battleUIState = BattleUIState::Default;
                        break;
                    }

                    battleUIState = BattleUIState::ChooseCardTarget;
                    RenewUI();

                    int targetChoice = ReadIntChoice();

                    if (targetChoice == 0)
                    {
                        battleUIState = BattleUIState::Default;
                        break;
                    }

                    targetIndex = targetChoice - 1;

                    if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size()))
                    {
                        currentLog.push_back("Invalid target.");
                        battleUIState = BattleUIState::Default;
                        break;
                    }

                    if (enemies[targetIndex] == nullptr || enemies[targetIndex]->IsDead())
                    {
                        currentLog.push_back("That target is already defeated.");
                        battleUIState = BattleUIState::Default;
                        break;
                    }
                }

                selectedCard->use(player, enemies, targetIndex);
                currentLog.push_back("You used {" + selectedCard->getName() + "}.");

                RemoveDeadEnemies(enemies);

                player.playerHand.RemoveCard(realHandIndex, player);

                battleUIState = BattleUIState::Default;
                break;
            }

            case 2:
            {
                battleUIState = BattleUIState::CheckDeck;
                while (true)
                {
                    RenewUI();
                    int previousChoice = ReadIntChoice();

                    if (previousChoice == 0)
                    {
                        battleUIState = BattleUIState::Default;
                        break;
                    }
                }
                break;
            }

            case 3:
            {
                std::cout << "Work In Progress" << std::endl;
                break;
            }

            case 0:
                currentLog.push_back("You ended your turn.");
                playerTurn = false;
                break;

            default:
                currentLog.push_back("Invalid command.");
                break;
            }
        }
        else
        {
            battleUIState = BattleUIState::EnemyTurn;
            RenewUI();

            for (auto& enemy : enemies)
            {
                if (enemy == nullptr || enemy->IsDead())
                {
                    continue;
                }

                RunEnemyTurnDummy(*enemy, player, currentLog);

                RenewUI();
                WaitForEnter();

                if (!player.GetPlayerCondition())
                {
                    return 1;
                }
            }
            player.playerHand.Clear(player);
            player.playerHand.DrawCards(player.playerDeck, 5, player);
            playerTurn = true;
            currentLog.clear();
            battleUIState = BattleUIState::Default;
        }
    }
    battleUIState = BattleUIState::Clear;
    RewardReset();
    RenewUI();
    std::cin.ignore(10000, '\n');
    WaitForEnter();
    return (roomCount==10)?2:0;
}


void BattleRoom::RewardReset()
{
    player.addAttack(originalAttack - player.GetAttack());
    player.addDefense(originalDefense - player.GetDefense());
    player.GainExp(totalExp, "The player' experienced increased by: ");
    player.GainGold(totalGold, "The player got richer! Gained: ");
    currentLog.clear();
    currentLog.push_back(player.GetName() + " gained " + std::to_string(totalExp) + " experience!");
    currentLog.push_back(player.GetName() + " gained " + std::to_string(totalGold) + " gold!");
    return;
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
        CardData cardData(player.playerDeck.getCard(i)->getID(), player.playerDeck.getCard(i)->getName(), RarityToString(player.playerDeck.getCard(i)->getRarity()), player.playerDeck.getCard(i)->getEffectText(), player.playerDeck.getCard(i)->IsPlayableInHand(), player.playerDeck.getCard(i)->getTargetType());
            cardsData.push_back(cardData);
        }
    return cardsData;
}

std::vector<CardData> BattleRoom::PackageHand()
{
    std::vector<CardData> cardsData;
    for (int i = 0; i < player.playerHand.getCardCount(); i++)
    {
        CardData cardData(player.playerHand.getCard(i)->getID(), player.playerHand.getCard(i)->getName(), RarityToString(player.playerHand.getCard(i)->getRarity()), player.playerHand.getCard(i)->getEffectText(), player.playerHand.getCard(i)->IsPlayableInHand(), player.playerHand.getCard(i)->getTargetType());
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
    data.playerLevel=player.GetLevel();
    data.playerExp = player.GetExp();
    data.playerGold = player.GetGold();
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


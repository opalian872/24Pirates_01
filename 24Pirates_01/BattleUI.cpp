//BattleUI.cpp

#include "BattleUI.h"
#include "BattleRoom.h" // Enemy struct 보기 위해서. 가능하면 안 쓰고 싶음
#include "Deck.h" //덱 사이즈나 이런 걸 알기 위해 사용. 가능하면 안쓰고 싶음.
#include "Card.h"
#include <iostream>
#include <sstream>
#include <algorithm>

BattleUI::BattleUI(int roomCount): roomCount(roomCount)
{
    consoleWidth = GetConsoleWidth();
    consoleHeight = GetConsoleHeight();

}
void BattleUI::ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void BattleUI::Render(const UIData& data, BattleUIState battleUIState)
{
    ClearScreen();
    std::cout << " [Room " << roomCount << "] [Battle] Ruined Dungeon\n\n";
    //left = "["+data.playerName+"] Health 180/200 Attack: 10 Defense: 20";
    //right = "Buffs: [Attack+2(1turn)][Defense+3(2turn)]";
    RenderHeader(data);
    std::cout << '\n';
    RenderEnemies(data);
    std::cout << " Your Hand:" << '\n';
    std::cout << " [1] {Strike} Attack a single target for N damage." << '\n';
    std::cout << " [2] {Shake & roll} Choose two cards to discard. Draw two cards from your deck" << '\n';
    std::cout << " [3] {P: Increase attack} Increase attack by 2." << '\n';
    std::cout << " [4] {P: School Days} Increase your defense be 2 for each enemy on the field" << '\n';
    std::cout << " [5] {P: Mundo Goes Where He Pleases} Regenerate 2 Health after enemy's turn ends." << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << " //손패 최대 10장까지 가능하게" << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << std::string(consoleWidth - 1, '-') << '\n';
    std::cout << '\n';
    std::cout << " Commands:" << '\n';
    std::cout << " [1]: Choose card to play" << '\n';
    std::cout << " [2]: Check my deck" << '\n';
    std::cout << " [3]: Battle Log" << '\n';
    std::cout << " [4]: End Turn" << '\n';
    std::cout << '\n';

    std::cout << " Choose:: ";
    return;
}

int BattleUI::GetConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int BattleUI::GetConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void BattleUI::RenderHeader(const UIData& data)
{
    std::string left;
    std::string right;
    int deckSize = data.playerDeck->getCardCount();
    left = " [" + data.playerName + "]"+ " Health: " + std::to_string(data.playerCurrentHealth)+" / " + std::to_string(data.playerCurrentHealth)+ " Attack: "+std::to_string(data.playerAttack)+" Defense: "+ std::to_string(data.playerDefense);
    right = "Buffs: [Attack+2(1turn)][Defense+3(2turn)]";
    int spaces = consoleWidth - static_cast<int>(left.size()) - static_cast<int>(right.size());
    std::cout << left << std::string(spaces, ' ') << right << std::endl;
    std::cout << " My Deck: "<<deckSize<<" / "<<deckSize << '\n';
    return;
}
void BattleUI::RenderEnemies(const UIData& data)
{
    if (data.enemies != nullptr)
    {
        std::cout << " Enemies:" << '\n';
        std::cout << '\n';
        for (int i = 0; i < data.enemies->size(); i++)
        {
            const DummyEnemy& enemy = (*data.enemies)[i];

            std::cout << i + 1 << ". "
                << enemy.name
                << " HP: " << enemy.currentHealth << "/" << enemy.maxHealth
                << " Attack: " << enemy.attack
                << " Defense: " << enemy.defense
                << '\n' << '\n';
        }
        for (int i = 3; i > data.enemies->size(); i--)
        {
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "Enemy pointer data.enemies is nullptr" << std::endl;
    }

    return;
}

void BattleUI::RenderCards(const UIData& data)
{
    if (data.playerDeck == nullptr)
    {
        std::cout << "Deck is not connected." << std::endl;
        std::cout << '\n';
        return;
    }



    return;
}

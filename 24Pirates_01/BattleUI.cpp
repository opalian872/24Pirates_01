//BattleUI.cpp
#include <iostream>
#include "BattleUI.h"

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

void BattleUI::Render()
{
    ClearScreen();
    std::cout << "[Room " << roomCount << "] [Battle] Ruined Dungeon\n\n";
    left = "[Player] Health 180/200 Attack: 10 Defense: 20";
    right = "Buffs: [Attack+2(1turn)][Defense+3(2turn)]";
    RenderHeader(left, right);
    std::cout << "My Deck: 15/20" << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Enemies:" << '\n';
    std::cout << '\n';
    std::cout << "1. Goblin HP: 20/30 Attack: 10 Defense: 10" << '\n';
    std::cout << '\n';
    std::cout << "2. KyeongHo Park HP: 500/700 Attack: 300 Defense: 20" << '\n';
    std::cout << '\n';
    std::cout << "Your Hand:" << '\n';
    std::cout << "[1] {Strike} Attack a single target for N damage." << '\n';
    std::cout << "[2] {Shake & roll} Choose two cards to discard. Draw two cards from your deck" << '\n';
    std::cout << "[3] {P: Increase attack} Increase attack by 2." << '\n';
    std::cout << "[4] {P: School Days} Increase your defense be 2 for each enemy on the field" << '\n';
    std::cout << "[5] {P: Mundo Goes Where He Pleases} Regenerate 2 Health after enemy's turn ends." << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "//손패 최대 10장까지 가능하게" << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << std::string(consoleWidth - 1, '-') << '\n';
    std::cout << '\n';
    std::cout << "Commands:" << '\n';
    std::cout << "[1]: Choose card to play" << '\n';
    std::cout << "[2]: Check my deck" << '\n';
    std::cout << "[3]: Battle Log" << '\n';
    std::cout << "[4]: End Turn" << '\n';
    std::cout << '\n';

    std::cout << "Choose:: ";
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

void BattleUI::RenderHeader(const std::string& left, const std::string& right)
{
    int spaces = consoleWidth - static_cast<int>(left.size()) - static_cast<int>(right.size());
    std::cout << left << std::string(spaces, ' ') << right << std::endl;
    return;
}

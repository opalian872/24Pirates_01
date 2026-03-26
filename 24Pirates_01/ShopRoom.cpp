// ShopRoom.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

#include "ShopRoom.h"
//#include "Card.h"




ShopRoom::ShopRoom(int roomCount) : roomCount(roomCount)
{
    consoleWidth = GetConsoleWidth();
    consoleHeight = GetConsoleHeight();
}

int ShopRoom::GetConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int ShopRoom::GetConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void ShopRoom::ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}





void ShopRoom::ShowMenu()
{
    int num = 0;
    bool ShopMenu = true;

    while (ShopMenu)
    {


        ClearScreen();

        std::cout << "[Room " << roomCount << "] [Shop] [General]\n";
        std::cout << "My Deck: 15/20\n\n";

        std::cout << std::string(consoleWidth - 1, '=') << '\n';        //카드 진열 목록 수정해야 함
        std::cout << "+----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+\n";
        std::cout << "| [1]                        |  | [2]                        |  | [3]                        |  | [4]                        |  | [5]                        |\n";
        std::cout << "| Strike                     |  | Heal                       |  | Defense Boost              |  | Attack Boost               |  | Double Hit                 |\n";
        std::cout << "+----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+\n";
        std::cout << "| Type: Active               |  | Type: Active               |  | Type: Passive              |  | Type: Passive              |  | Type: Passive              |\n";
        std::cout << "| Target: SingleEnemy        |  | Target: Self               |  | Target: Self               |  | Target: Self               |  | Target: SingleEnemy        |\n";
        std::cout << "|                            |  |                            |  |                            |  |                            |  |                            |\n";
        std::cout << "| Description                |  | Description                |  | Description                |  | Description                |  | Description                |\n";
        std::cout << "+----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+\n";
        std::cout << "| Deal 12 damage to one e... |  | Recover 10 HP              |  | Gain +3 defense for 3 t... |  | Gain +2 attack for 1 turn  |  | Hit one enemy 2 times w... |\n";
        std::cout << "| y                          |  |                            |  | s                          |  |                            |  | 70 percent attack          |\n";
        std::cout << "|                            |  |                            |  |                            |  |                            |  |                            |\n";
        std::cout << "|                            |  |                            |  |                            |  |                            |  |                            |\n";
        std::cout << "|                            |  |                            |  |                            |  |                            |  |                            |\n";
        std::cout << "+----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+  +----------------------------+\n";
        std::cout << std::string(consoleWidth - 1, '=') << '\n';        //카드 진열 목록 수정해야 함
        std::cout << "Commands:\n";
        std::cout << "[1]: BuyCard\n";
        std::cout << "[2]: RemoveCard\n";
        std::cout << "[3]: RandomRemove\n";
        std::cout << "[4]: ShopReset\n";
        std::cout << "[5]: ExitShop\n";
        std::cout << "\n\nChoose:: ";

        std::cin >> num;
        switch (num)
        {
        case 1:
            BuyCard();
            break;
        case 2:
            RemoveCard();
            break;
        case 3:
            RemoveRandomCard();
            break;
        case 4:
            ResetShop();
            break;
        case 5:
            ExitShop();
            ShopMenu = false;
            break;
        default:
            std::cout << "Wrong Number.\n";
            break;
        }

        if (ShopMenu)
        {
            std::cout << "\nPress Enter to Proceed";
            std::cin.ignore(10000, '\n');
            std::cin.get();
        }

    }
}

void ShopRoom::BuyCard()
{
    std::cout << "Please choose the card you want to buy.\n";
}

void ShopRoom::RemoveCard()
{
    std::cout << "Please choose the card you want to remove.\n";
}

void ShopRoom::RemoveRandomCard()
{
    std::cout << "Remove the card at random.\n";
}

void ShopRoom::ResetShop()
{
    std::cout << "Reset the store.\n";
}

void ShopRoom::ExitShop()
{
    std::cout << "leaving the store.\n";
}

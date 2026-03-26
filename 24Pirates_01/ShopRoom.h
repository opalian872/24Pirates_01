// ShopRoom.h

#pragma once
#include <windows.h>
#include <vector>
#include <string>

class Card;

class ShopRoom
{
private:
    int roomCount;
    int consoleWidth;
    int consoleHeight;

public:
    ShopRoom(int roomCount);

    int GetConsoleWidth();
    int GetConsoleHeight();
    void ClearScreen();

    void ShowMenu();

    void BuyCard();
    void RemoveCard();
    void RemoveRandomCard();
    void ResetShop();
    void ExitShop();


    /*void PrintCardGroupHorizontal(const std::vector<Card*>& cards, int startIndex, int endIndex);
    void PrintShopCards(const std::vector<Card*>& cards);*/
};

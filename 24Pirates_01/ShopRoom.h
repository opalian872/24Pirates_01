<<<<<<< HEAD
﻿// ShopRoom.h

#pragma once
#include <windows.h>
#include <vector>
#include <string>

class Card;

=======
﻿#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "ShopManager.h"

// 상점 화면 출력과 입력 처리를 담당하는 클래스
>>>>>>> Shop
class ShopRoom
{
private:
    int roomCount;
    int consoleWidth;
    int consoleHeight;

<<<<<<< HEAD
public:
    ShopRoom(int roomCount);

    int GetConsoleWidth();
    int GetConsoleHeight();
=======
    ShopManager& shopManager;

public:
    ShopRoom(int roomCount, ShopManager& shopManager);

    // 현재 콘솔 창의 너비와 높이를 반환
    int GetConsoleWidth();
    int GetConsoleHeight();

>>>>>>> Shop
    void ClearScreen();

    void ShowMenu();

    void BuyCard();
    void RemoveCard();
    void RemoveRandomCard();
    void ResetShop();
    void ExitShop();

<<<<<<< HEAD

    /*void PrintCardGroupHorizontal(const std::vector<Card*>& cards, int startIndex, int endIndex);
    void PrintShopCards(const std::vector<Card*>& cards);*/
=======
    // 카드가 있는 슬롯의 박스 출력 문자열을 생성
    std::vector<std::string> MakeCardBoxLines(int cardNumber, const ShopCardData& card);

    // 비어 있는 슬롯의 박스 출력 문자열을 생성
    std::vector<std::string> MakeEmptyCardBoxLines(int cardNumber);

    // 카드 여러 장을 가로 방향으로 나란히 출력
    void PrintCardGroupHorizontal(const std::vector<ShopCardData>& cards, int startIndex, int endIndex);

    // 상점 10칸 카드를 2줄로 나눠 출력
    void PrintShopCards(const std::vector<ShopCardData>& cards);

    // 현재 플레이어 덱 목록을 출력
    void PrintDeckCards();
>>>>>>> Shop
};

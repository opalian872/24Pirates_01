#include "ShopRoom.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>

// 문자열이 너무 길면 자르고, 짧으면 공백을 채워서 고정 길이로 맞춤
static std::string FitToWidth(const std::string& text, int width)
{
    if ((int)text.length() > width)
    {
        return text.substr(0, width);
    }

    return text + std::string(width - text.length(), ' ');
}

// 긴 문자열을 여러 줄로 나눠 카드 박스 안에 들어가게 정리
static std::vector<std::string> WrapText(const std::string& text, int width, int maxLines)
{
    std::vector<std::string> lines;

    if (text.empty())
    {
        for (int i = 0; i < maxLines; i++)
        {
            lines.push_back(std::string(width, ' '));
        }
        return lines;
    }

    std::string remaining = text;

    while (!remaining.empty() && (int)lines.size() < maxLines)
    {
        if ((int)remaining.length() <= width)
        {
            lines.push_back(FitToWidth(remaining, width));
            remaining.clear();
        }
        else
        {
            int splitPos = width;

            for (int i = width; i >= 0; i--)
            {
                if (remaining[i] == ' ')
                {
                    splitPos = i;
                    break;
                }
            }

            if (splitPos == width)
            {
                lines.push_back(FitToWidth(remaining.substr(0, width), width));
                remaining = remaining.substr(width);
            }
            else
            {
                lines.push_back(FitToWidth(remaining.substr(0, splitPos), width));
                remaining = remaining.substr(splitPos + 1);
            }
        }
    }

    while ((int)lines.size() < maxLines)
    {
        lines.push_back(std::string(width, ' '));
    }

    return lines;
}

// 상점 화면 객체를 만들고 콘솔 크기를 저장
ShopRoom::ShopRoom(int roomCount, ShopManager& shopManager)
    : roomCount(roomCount), shopManager(shopManager)
{
    consoleWidth = GetConsoleWidth();
    consoleHeight = GetConsoleHeight();
}

// 현재 콘솔 창의 너비를 반환
int ShopRoom::GetConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// 현재 콘솔 창의 높이를 반환
int ShopRoom::GetConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// 콘솔 화면을 지움
void ShopRoom::ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 카드가 있는 슬롯의 박스 문자열을 생성
std::vector<std::string> ShopRoom::MakeCardBoxLines(int cardNumber, const ShopCardData& card)
{
    const int innerWidth = 28;
    std::vector<std::string> lines;

    std::vector<std::string> descLines = WrapText(card.description, innerWidth - 1, 4);

    std::string priceText;
    if (card.rarity == "Normal")
    {
        priceText = "Price: 20";
    }
    else if (card.rarity == "Rare")
    {
        priceText = "Price: 30";
    }
    else if (card.rarity == "Epic")
    {
        priceText = "Price: 50";
    }
    else
    {
        priceText = "Price: 0";
    }

    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("[" + std::to_string(cardNumber) + "]", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth(card.name, innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("Rarity: " + card.rarity, innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth(priceText, innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("Description", innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    for (int i = 0; i < (int)descLines.size(); i++)
    {
        lines.push_back("| " + FitToWidth(descLines[i], innerWidth - 1) + "|");
    }

    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    return lines;
}

// 비어 있는 슬롯의 박스 문자열을 생성
std::vector<std::string> ShopRoom::MakeEmptyCardBoxLines(int cardNumber)
{
    const int innerWidth = 28;
    std::vector<std::string> lines;

    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("[" + std::to_string(cardNumber) + "]", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("Rarity: ", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("Price: ", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("Description", innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    for (int i = 0; i < 4; i++)
    {
        lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
    }

    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    return lines;
}

// 여러 장의 카드를 가로로 나란히 출력
void ShopRoom::PrintCardGroupHorizontal(const std::vector<ShopCardData>& cards, int startIndex, int endIndex)
{
    std::vector<std::vector<std::string>> allCardLines;

    for (int i = startIndex; i <= endIndex; i++)
    {
        if (i < (int)cards.size())
        {
            if (cards[i].isEmpty)
            {
                allCardLines.push_back(MakeEmptyCardBoxLines(i + 1));
            }
            else
            {
                allCardLines.push_back(MakeCardBoxLines(i + 1, cards[i]));
            }
        }
        else
        {
            allCardLines.push_back(MakeEmptyCardBoxLines(i + 1));
        }
    }

    int lineCount = (int)allCardLines[0].size();

    for (int line = 0; line < lineCount; line++)
    {
        for (int cardIndex = 0; cardIndex < (int)allCardLines.size(); cardIndex++)
        {
            std::cout << allCardLines[cardIndex][line] << "  ";
        }
        std::cout << '\n';
    }
}

// 상점 카드 10칸을 2줄로 나눠 출력
void ShopRoom::PrintShopCards(const std::vector<ShopCardData>& cards)
{
    PrintCardGroupHorizontal(cards, 0, 4);
    std::cout << '\n';
    PrintCardGroupHorizontal(cards, 5, 9);
    std::cout << '\n';
}

// 현재 플레이어 덱 목록을 번호와 함께 출력
void ShopRoom::PrintDeckCards()
{
    std::cout << "My Deck Cards:\n";

    int count = shopManager.GetDeckCardCount();

    if (count == 0)
    {
        std::cout << "(Empty)\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        Card* card = shopManager.GetDeckCard(i);

        if (card != nullptr)
        {
            std::cout << i + 1 << ". " << card->getName() << '\n';
        }
    }
}

// 상점 화면과 메뉴를 반복 출력하고 입력을 처리
void ShopRoom::ShowMenu()
{
    int choice = 0;
    bool isShopping = true;

    while (isShopping)
    {
        ClearScreen();

        std::cout << "[Room " << roomCount << "] [Shop] [General]\n";
        std::cout << "Current Gold: " << shopManager.getGold() << "\n";
        std::cout << "My Deck: " << shopManager.GetDeckCardCount() << "/20\n";
        std::cout << "Remove Count: " << shopManager.GetRemoveCardCount() << "/3\n\n";

        PrintShopCards(shopManager.GetShopCards());
        PrintDeckCards();

        std::cout << "\n============================================================\n";
        std::cout << "Commands:\n";
        std::cout << "[1]: Buy Card\n";
        std::cout << "[2]: Remove Card From Deck\n";
        std::cout << "[3]: Random Remove From Deck\n";
        std::cout << "[4]: Shop Reset (1 time only)\n";
        std::cout << "[5]: Exit Shop\n";
        std::cout << "\nChoose:: ";

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
            isShopping = false;
            break;
        default:
            break;
        }
    }
}

// 사용자가 선택한 상점 카드를 구매
void ShopRoom::BuyCard()
{
    int cardChoice;

    std::cout << "\nPlease choose the card you want to buy: ";
    std::cin >> cardChoice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }

    int index = cardChoice - 1;

    if (shopManager.BuyCard(index))
    {
        std::cout << "Purchase complete.\n";
    }
    else
    {
        std::cout << "Invalid choice, empty slot, or not enough gold.\n";
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cout << "Press Enter to return to shop.";
    std::cin.get();
}

// 사용자가 선택한 덱 카드를 제거
void ShopRoom::RemoveCard()
{
    if (!shopManager.CanRemoveCard())
    {
        std::cout << "\nYou can only remove cards 3 times.\n";
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Press Enter to return to shop.";
        std::cin.get();
        return;
    }

    int cardChoice;

    std::cout << "\nPlease choose the deck card you want to remove: ";
    std::cin >> cardChoice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return;
    }

    int index = cardChoice - 1;

    if (shopManager.RemoveCard(index))
    {
        std::cout << "Card removed from deck.\n";
    }
    else
    {
        std::cout << "Invalid deck choice.\n";
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cout << "Press Enter to return to shop.";
    std::cin.get();
}

// 플레이어 덱에서 랜덤으로 카드 1장을 제거
void ShopRoom::RemoveRandomCard()
{
    if (shopManager.RemoveRandomCard())
    {
        std::cout << "\nA random card has been removed from your deck.\n";
    }
    else
    {
        std::cout << "\nThere are no cards in your deck.\n";
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cout << "Press Enter to return to shop.";
    std::cin.get();
}

void ShopRoom::ResetShop()
{
    if (shopManager.CanResetShop())
    {
        shopManager.ResetShop();
        std::cout << "\nShop has been reset.\n";
    }
    else
    {
        std::cout << "\nShop reset can only be used once.\n";
    }

    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cout << "Press Enter to return to shop.";
    std::cin.get();
}

// 상점 종료 메시지를 출력
void ShopRoom::ExitShop()
{
    std::cout << "\nExiting shop.\n";
}

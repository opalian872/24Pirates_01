//BattleUI.cpp

#include "BattleUI.h"
#include "BattleRoom.h" // Enemy struct 보기 위해서. 가능하면 안 쓰고 싶음
#include "Deck.h" //덱 사이즈나 이런 걸 알기 위해 사용. 가능하면 안쓰고 싶음.
#include "Card.h"
#include <iostream>
#include <sstream>
#include <algorithm>

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
    switch (battleUIState)
    {
    case BattleUIState::Default:
        ClearScreen();
        std::cout << " [Room " << roomCount << "] [Battle] Ruined Dungeon\n\n";
        //left = "["+data.playerName+"] Health 180/200 Attack: 10 Defense: 20";
        //right = "Buffs: [Attack+2(1turn)][Defense+3(2turn)]";
        RenderHeader(data);
        std::cout << '\n';
        RenderEnemies(data);
        RenderHand(data);
        /*std::cout << " [1] {Strike} Attack a single target for N damage." << '\n';
        std::cout << " [2] {Shake & roll} Choose two cards to discard. Draw two cards from your deck" << '\n';
        std::cout << " [3] {P: Increase attack} Increase attack by 2." << '\n';
        std::cout << " [4] {P: School Days} Increase your defense be 2 for each enemy on the field" << '\n';
        std::cout << " [5] {P: Mundo Goes Where He Pleases} Regenerate 2 Health after enemy's turn ends." << '\n';
        std::cout << '\n';
        std::cout << '\n';
        std::cout << " //손패 최대 10장까지 가능하게" << '\n';
        std::cout << '\n';
        std::cout << '\n';*/
        std::cout << std::string(consoleWidth - 1, '-') << '\n';
        std::cout << '\n';
        std::cout << " Commands:" << '\n';
        std::cout << " [1]: Choose card to play" << '\n';
        std::cout << " [2]: Check my deck" << '\n';
        std::cout << " [3]: Battle Log" << '\n';
        std::cout << " [4]: End Turn" << '\n';
        std::cout << '\n';

        std::cout << " Choose:: ";
        break;


    }
    
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
std::vector<std::string> BattleUI::MakeCardBoxLines(int cardNumber, const CardData& card)
{
    const int innerWidth = 28;
    std::vector<std::string> lines;

    std::vector<std::string> descLines = WrapText(card.effectText, innerWidth - 1, 5);

    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("[" + std::to_string(cardNumber) + "]", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth(card.name, innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("Rarity: " + card.rarity, innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
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
std::vector<std::string> BattleUI::MakeEmptyCardBoxLines(int cardNumber)
{
    const int innerWidth = 28;
    std::vector<std::string> lines;

    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("[" + std::to_string(cardNumber) + "]", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");
    lines.push_back("| " + FitToWidth("Rarity: ", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
    lines.push_back("| " + FitToWidth("Description", innerWidth - 1) + "|");
    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    for (int i = 0; i < 5; i++)
    {
        lines.push_back("| " + FitToWidth("", innerWidth - 1) + "|");
    }

    lines.push_back("+" + std::string(innerWidth, '-') + "+");

    return lines;
}

void BattleUI::RenderHeader(const UIData& data)
{
    std::string left;
    std::string right;
    int deckSize = data.playerDeck.size();
    left = " [" + data.playerName + "]"+ " Health: " + std::to_string(data.playerCurrentHealth)+" / " + std::to_string(data.playerMaxHealth)+ " Attack: "+std::to_string(data.playerAttack)+" Defense: "+ std::to_string(data.playerDefense);
    right = "Buffs: [Attack+2(1turn)][Defense+3(2turn)]";
    int spaces = consoleWidth - static_cast<int>(left.size()) - static_cast<int>(right.size());
    std::cout << left << std::string(spaces, ' ') << right << std::endl;
    std::cout << " My Deck: "<<deckSize<<" / "<<deckSize << '\n';
    return;
}
void BattleUI::RenderEnemies(const UIData& data)
{
    if (!data.enemies.empty())
    {
        std::cout << " Enemies:" << '\n';
        std::cout << '\n';
        for (int i = 0; i < data.enemies.size(); i++)
        {
            const EnemyData& enemy = data.enemies[i];

            std::cout << i + 1 << ". "
                << enemy.name
                << " HP: " << enemy.currentHp << "/" << enemy.maxHp
                << " Attack: " << enemy.atk
                << " Defense: " << enemy.def
                << '\n' << '\n';
        }
        for (int i = 3; i > data.enemies.size(); i--)
        {
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "Enemy data is Empty!" << std::endl;
    }

    return;
}

void BattleUI::RenderHand(const UIData& data)
{
    std::cout << " Your Hand:" << '\n';
    if (data.playerHand.empty())
    {
        std::cout << "Deck is not connected." << std::endl;
        std::cout << '\n';
        return;
    }
    else
    {
        PrintCardGroupHorizontal(data.playerHand, 0, 4);
    }
    if (data.playerHand.size() > 5)
    {
        PrintCardGroupHorizontal(data.playerHand, 5, 9);
    }


    return;
}

void BattleUI::RenderDeck(const UIData& data)
{
    std::cout << " Your Deck:" << '\n';
    if (data.playerDeck.empty())
    {
        std::cout << "Deck is not connected." << std::endl;
        std::cout << '\n';
        return;
    }
    else
    {
        PrintCardGroupHorizontal(data.playerHand, 0, 4);
    }
    if (data.playerHand.size() > 5)
    {
        PrintCardGroupHorizontal(data.playerHand, 5, 9);
    }
    if (data.playerHand.size() > 10)
    {
        PrintCardGroupHorizontal(data.playerHand, 10, 14);
    }
    if (data.playerHand.size() > 15)
    {
        PrintCardGroupHorizontal(data.playerHand, 15, 19);
    }
    return;
}

void BattleUI::RenderCommands(const UIData& data, BattleUIState battleUIState)
{
    switch (battleUIState)
    {
    case BattleUIState::Default:

        break;
    }
    return;
}

void BattleUI::PrintCardGroupHorizontal(const std::vector<CardData>& cards, int startIndex, int endIndex)
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
    return;
}

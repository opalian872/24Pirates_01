//BattleUI.h
#pragma once
#include "UIData.h"
#include <windows.h>
#include <string>
class BattleUI
{
private:
    int consoleWidth;
    int consoleHeight;
    const int roomCount;
public:
	BattleUI(int roomCount);
    void ClearScreen();
	void Render(const UIData& data, BattleUIState battleUIState);
    int GetConsoleWidth();
    int GetConsoleHeight();
    std::vector<std::string> MakeCardBoxLines(int cardNumber, const CardData& card);
    std::vector<std::string> MakeEmptyCardBoxLines(int cardNumber);
    void RenderHeader(const UIData& data);
    void RenderEnemies(const UIData& data);
    void RenderHand(const UIData& data);
    void RenderDeck(const UIData& data);
    void RenderCommands(const UIData& data, BattleUIState battleUIState);
    void RenderLogs(const UIData& data);
    void RenderClear();
    void PrintCardGroupHorizontal(const std::vector<CardData>& cards, int startIndex, int endIndex);
};


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
    void RenderHeader(const UIData& data);
    void RenderEnemies(const UIData& data);
    void RenderCards(const UIData& data);
};


//BattleUI.h
#pragma once
#include <windows.h>
#include <string>
class BattleUI
{
private:
    int consoleWidth;
    int consoleHeight;
    const int roomCount;
    std::string left;
    std::string right;
public:
	BattleUI(int roomCount);
    void ClearScreen();
	void Render();
    int GetConsoleWidth();
    int GetConsoleHeight();
    void RenderHeader(const std::string& left, const std::string& right);
};


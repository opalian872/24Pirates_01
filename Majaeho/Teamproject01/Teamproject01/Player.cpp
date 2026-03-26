#include <iostream>
#include "Player.h"
#include <string>



void Player::ShowStatus()
{
	std::cout << playerName << " HP: " << hp << "/" << maxHp << " | ATK: " << attack << " | DEF: " << defense << std::endl;

}
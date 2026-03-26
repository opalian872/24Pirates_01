#include <iostream>
#include "Player.h"

// expAmount : 몬스터 처치 시 얻는 경험치의 임시 변수입니다.
void Player::GainExp(int expAmount)
{
	exp += expAmount;
	std::cout << playerName << " gained " << expAmount << " EXP." << std::endl;
	if(exp >= 100)
	{
		LevelUp();
	}
}


void Player::LevelUp()
{
	level++;
	maxHp += level * 20;
	hp = maxHp;
	attack += level * 5;
	exp = 0;

	std::cout << playerName << " Leveled Up!" << std::endl;
	std::cout << "Current Level : " << level << std::endl;
}
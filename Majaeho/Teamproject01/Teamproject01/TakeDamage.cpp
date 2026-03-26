#include <iostream>
#include "Player.h"

// damage : 몬스터에게 받는 대미지량의 임시 변수 입니다.
void Player::TakeDamage(int damage) 
{
	hp -= damage;
	if (hp < 0)
	{
		playerCondition = false;
	}
}
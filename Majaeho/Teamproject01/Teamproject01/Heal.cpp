#include <iostream>
#include "Player.h"

// healAmount : 카드 사용시 얻는 회복량의 임시 변수 입니다.
void Player::Heal(int healAmount)
{
	hp += healAmount
	if (hp > maxHp)
	{
		hp = maxHp;
	}

}
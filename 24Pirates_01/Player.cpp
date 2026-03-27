#include <iostream>
#include "Player.h"
#include <string>



void Player::ShowStatus()
{
    std::cout << playerName << " HP: " << hp << "/" << maxHp << " | ATK: " << attack << " | DEF: " << defense << std::endl;

}

Player::Usecard(std::string cardname)
{




}

// damage : 몬스터에게 받는 대미지량의 임시 변수 입니다.
void Player::TakeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        hp = 0;
        playerCondition = false;
    }
}

// healAmount : 카드 사용시 얻는 회복량의 임시 변수 입니다.
void Player::Heal(int healAmount)
{
    hp += healAmount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }

}

// expAmount : 몬스터 처치 시 얻는 경험치의 임시 변수입니다.
void Player::GainExp(int expAmount)
{
    exp += expAmount;
    std::cout << playerName << " gained " << expAmount << " EXP." << std::endl;
    if (exp >= 100)
    {
        exp -= 100;
        LevelUp();
    }
}


void Player::LevelUp()
{
    level++;
    maxHp += level * 20;
    hp = maxHp;
    attack += level * 5;

    std::cout << playerName << " Leveled Up!" << std::endl;
    std::cout << "Current Level : " << level << std::endl;
}

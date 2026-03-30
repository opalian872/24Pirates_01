#include <iostream>
#include "Player.h"
#include <string>


void Player::PlayerMaking(std::string inname, int inlevel, int inmaxHp, int inhp, int inattack, int indefense, int inexp, int ingold, bool inplayerCondition)
{
    playerName = inname;
    level = inlevel;
    maxHp = inmaxHp;
    hp = inhp;
    attack = inattack;
    defense = indefense;
    exp = inexp;
    //gold = ingold;
    gold = 100; // 상점 테스트를 위해 임시로 시작골드 100
    playerCondition = inplayerCondition;

    CreateStarterDeck();

    std::cout << "Player's name : " << playerName << std::endl;
    std::cout << "Player's level : " << level <<std::endl;
    std::cout << "Player's Hp : " << hp << "/" << maxHp << std::endl;
    std::cout << "Player's attack : " << attack <<std::endl;
    std::cout << "Player's defense : " << defense <<std::endl;
    std::cout << "Player's currentExp : " << exp <<std::endl;
    std::cout << "Player's currentGold : " << gold <<std::endl;

}

void Player::CreateStarterDeck()
{
    CardDatabase database;

    playerDeck.addCardByID(database, CardID::Strike);
    playerDeck.addCardByID(database, CardID::Strike);
    playerDeck.addCardByID(database, CardID::Heal);
    playerDeck.addCardByID(database, CardID::DefenseBoost);
}

void Player::GainExp(int expAmount)
{
    std::cout << "The player gains " << expAmount << " experience points!" << std::endl;
    exp += expAmount;
    if (exp >= 100)
    {
        std::cout << "The player levels up!" << std::endl;
        ++level;
        maxHp += level * 20;
        hp = maxHp;
        attack += level * 5;
        exp = 0;
    }

}
void Player::GainGold(int goldAmount)
{
    std::cout << "The player gains " << goldAmount << " gold!" << std::endl;
    gold += goldAmount;

}

// 골드 차감
bool Player::SubGold(int goldAmount)
{
    if (gold < goldAmount)
    {
        std::cout << "Not enough gold!" << std::endl;
        return false;
    }

    gold -= goldAmount;
    std::cout << goldAmount << " gold has been spent." << std::endl;
    return true;
}

void Player::TakeDamage(int damage)
{

    int finalDamage = damage - defense;

    if (finalDamage <= 0)
    {
        std::cout << "The monster's attack bounced off!" << std::endl;
    }
    else
    {
        std::cout << "The player took " << finalDamage << " damage!" << std::endl;

        if(hp <= 0)
        {
            std::cout << "The player's HP has run out." << std::endl;
            std::cout << "The player's vision went dark." << std::endl;
            playerCondition = false;
        }
    }
    

}

void Player::Heal(int healAmount)
{
    std::cout << "The player's HP is restored!" << std::endl;
    hp += healAmount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
    std::cout << "Player's HP has been restored!" << std::endl;

}

void Player::AddCardToDeck(Card* card)
{
    playerDeck.addCard(card);
}

void Player::AddCardToDeckByID(const CardDatabase& database, CardID id)
{
    playerDeck.addCardByID(database, id);
}

int Player::GetDeckSize()
{
    return playerDeck.getCardCount();
}

Card* Player::GetDeckCard(int index)
{
    return playerDeck.getCard(index);
}

void Player::RemoveDeckCard(int index)
{
    playerDeck.removeCard(index);
}

// Player 클래스 내에 있는 멤버변수 호출할 수 있는 Getter 함수입니다.
// GetName, GetHp, GetMaxHp, GetAttack, GetDefense, GetExp, GetGold, GetPlayerCondition

std::string Player::GetName()
{
    return playerName;
}

int Player::GetHp()
{
    return hp;
}

int Player::GetMaxHp()
{
    return maxHp;
}

int Player::GetAttack()
{
    return attack;
}

int Player::GetDefense()
{
    return defense;
}

int Player::GetExp()
{
    return exp;
}

int Player::GetGold()
{
    return gold;
}

bool Player::GetPlayerCondition()
{
    return playerCondition;
}

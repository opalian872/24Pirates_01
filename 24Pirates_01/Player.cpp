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
    gold = ingold;
    playerCondition = inplayerCondition;

    std::cout << "Player's name : " << playerName << std::endl;
    std::cout << "Player's level : " << level <<std::endl;
    std::cout << "Player's Hp : " << hp << "/" << maxHp << std::endl;
    std::cout << "Player's attack : " << attack <<std::endl;
    std::cout << "Player's defense : " << defense <<std::endl;
    std::cout << "Player's currentExp : " << exp <<std::endl;
    std::cout << "Player's currentGold : " << gold <<std::endl;

}

void Player::CreateStarterDeck(const CardDatabase& database)
{
    playerDeck.addCardByID(database, CardID::KeyboardSmash);
    playerDeck.addCardByID(database, CardID::DoubleClickBug);
    playerDeck.addCardByID(database, CardID::SuddenBathroom);
    playerDeck.addCardByID(database, CardID::MonitorOff);
    playerDeck.addCardByID(database, CardID::ChairPush);
    playerDeck.addCardByID(database, CardID::CtrlZLife);
    playerDeck.addCardByID(database, CardID::ShakeWifi);
}

void Player::GainExp(int expAmount, std::string gainEMsg)
{
    std::cout << gainEMsg << expAmount << std::endl;
    exp += expAmount;
    if (exp >= 100)
    {
        LevelUp("The Player levels up!");
    }

}

void Player::LevelUp(std::string levelMsg)
{
    std::cout << levelMsg << std::endl;
    ++level;
    maxHp += level * 20;
    hp = maxHp;
    attack += level * 5;
    exp = 0;

}

void Player::GainGold(int goldAmount, std::string gainGMsg)
{
    std::cout << gainGMsg << goldAmount << std::endl;
    gold += goldAmount;

}

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


void Player::TakeDamage(int damage, std::string takeDMsg1, std::string takeDMsg2, std::string takeDMsg3, std::string takeDMsg4)
{

    int finalDamage = damage - defense;
    if (finalDamage <= 0)
    {
        std::cout << takeDMsg1 << std::endl;
        return;
    }
    else
    {
        hp -= finalDamage;
        std::cout << takeDMsg2 << finalDamage << std::endl;

        if (hp <= 0)
        {
            std::cout << takeDMsg3 << std::endl;
            std::cout << takeDMsg4 << std::endl;
            playerCondition = false;
        }
    }


}

void Player::Heal(int healAmount, std::string healMsg1, std::string healMsg2)
{
    std::cout << healMsg1 << std::endl;
    hp += healAmount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }
    std::cout << healMsg2 << std::endl;

}

void Player::UseCard()
{

}

void Player::addAttack(int amount)
{
    attack = (std::max)(0, attack + amount);
}

void Player::addDefense(int amount)
{
    defense = (std::max)(0, defense + amount);
}

void Player::heal(int amount)
{
    hp += amount;
    if (hp > maxHp)
    {
        hp = maxHp;
    }

    if (hp > 0)
    {
        playerCondition = true;
    }
}
void Player::AddCardToDeck(Card* card)
{
    playerDeck.addCard(card);
}

void Player::AddCardToDeckByID(const CardDatabase& database, CardID id)
{
    playerDeck.addCardByID(database, id);
}

void Player::ShowMyDeck()
{
    
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

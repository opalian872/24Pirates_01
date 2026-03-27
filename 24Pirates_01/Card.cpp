// Card.cpp

#include "Card.h"
#include "PlayerDummy.h"
#include "EnemyDummy.h"

Card::Card(CardID id,
    CardRarity rarity,
    const std::string& name,
    const std::string& description,
    const std::string& effectText,
    CardType cardType,
    TargetType targetType)
    : id(id),
    rarity(rarity),
    name(name),
    description(description),
    effectText(effectText),
    cardType(cardType),
    targetType(targetType)
{
}

CardID Card::getID() const
{
    return id;
}

CardRarity Card::getRarity() const
{
    return rarity;
}

std::string Card::getName() const
{
    return name;
}

std::string Card::getDescription() const
{
    return description;
}

std::string Card::getEffectText() const
{
    return effectText;
}

CardType Card::getCardType() const
{
    return cardType;
}

TargetType Card::getTargetType() const
{
    return targetType;
}

Card* Card::clone() const
{
    return new Card(*this);
}

void Card::use(Player& player, std::vector<Enemy>& enemies, int targetIndex) const
{
    switch (id)
    {
    case CardID::Strike:
        if (targetIndex >= 0 && targetIndex < static_cast<int>(enemies.size()))
        {
            if (!enemies[targetIndex].isDead())
            {
                enemies[targetIndex].takeDamage(5);
            }
        }
        break;

    case CardID::Heal:
        player.heal(10);
        break;

    case CardID::DefenseBoost:
        player.addDefense(5);
        break;

    case CardID::AttackBoost:
        player.addAttack(5);
        break;

    case CardID::DoubleHit:
        if (targetIndex >= 0 && targetIndex < static_cast<int>(enemies.size()))
        {
            if (!enemies[targetIndex].isDead())
            {
                enemies[targetIndex].takeDamage(3);
                if (!enemies[targetIndex].isDead())
                {
                    enemies[targetIndex].takeDamage(3);
                }
            }
        }
        break;

    case CardID::MemoryShield:
        player.addDefense(static_cast<int>(enemies.size()));
        break;

    case CardID::Regeneration:
        player.heal(3);
        break;

    case CardID::Whirlwind:
        for (Enemy& enemy : enemies)
        {
            if (!enemy.isDead())
            {
                enemy.takeDamage(4);
            }
        }
        break;

    default:
        break;
    }
}

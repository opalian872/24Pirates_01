#include "CardDatabase.h"

CardDatabase::CardDatabase()
{
    initialize();
}

CardDatabase::~CardDatabase()
{
    for (Card* card : cardList)
    {
        delete card;
    }

    cardList.clear();
}

void CardDatabase::initialize()
{
    addCard(new Card(
        CardID::Strike,
        CardRarity::Normal,
        "Strike",
        "Hits the enemy with a keyboard.",
        "Deal 5 damage.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::Heal,
        CardRarity::Normal,
        "Heal",
        "Take a breath and recover.",
        "Recover 10 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::DefenseBoost,
        CardRarity::Rare,
        "Defense Boost",
        "Raise your guard with strong focus.",
        "Gain 5 defense.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::AttackBoost,
        CardRarity::Rare,
        "Attack Boost",
        "Tighten your grip and prepare to strike.",
        "Gain 5 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::DoubleHit,
        CardRarity::Rare,
        "Double Hit",
        "Attack twice before the enemy reacts.",
        "Deal 3 damage two times.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::MemoryShield,
        CardRarity::Epic,
        "Memory Shield",
        "Turn memory into protection.",
        "Gain defense based on enemy count.",
        CardType::Passive,
        TargetType::None
    ));

    addCard(new Card(
        CardID::Regeneration,
        CardRarity::Epic,
        "Regeneration",
        "Recover through steady breathing.",
        "Recover 3 HP.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::Whirlwind,
        CardRarity::Epic,
        "Whirlwind",
        "Spin with unstoppable force.",
        "Deal 4 damage to all enemies.",
        CardType::Active,
        TargetType::AllEnemies
    ));
}

void CardDatabase::addCard(Card* card)
{
    cardList.push_back(card);
}

Card* CardDatabase::getCardByID(CardID id) const
{
    for (Card* card : cardList)
    {
        if (card->getID() == id)
        {
            return card;
        }
    }

    return nullptr;
}

Card* CardDatabase::getCardByIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(cardList.size()))
    {
        return nullptr;
    }

    return cardList[index];
}

int CardDatabase::getCardCount() const
{
    return static_cast<int>(cardList.size());
}

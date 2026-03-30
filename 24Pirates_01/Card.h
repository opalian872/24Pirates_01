#pragma once

#include <string>
#include <vector>
#include "CardTypes.h"

struct Player;
struct Enemy;

class Card
{
private:
    CardID id;
    CardRarity rarity;
    std::string name;
    std::string description;
    std::string effectText;
    CardType cardType;
    TargetType targetType;

public:
    Card(CardID id,
        CardRarity rarity,
        const std::string& name,
        const std::string& description,
        const std::string& effectText,
        CardType cardType,
        TargetType targetType);

    CardID getID() const;
    CardRarity getRarity() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getEffectText() const;
    CardType getCardType() const;
    TargetType getTargetType() const;

    bool IsPassive() const;
    bool IsPlayableInHand() const;

    void use(Player& player, std::vector<Enemy>& enemies, int targetIndex) const;
    void ApplyPassive(Player& player) const;
    void RemovePassive(Player& player) const;

    Card* clone() const;
};

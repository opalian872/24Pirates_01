#pragma once

#include <vector>
#include "Card.h"
#include "CardDatabase.h"

class Deck
{
private:
    std::vector<Card*> cards;

public:
    Deck();
    ~Deck();

    void addCard(Card* card);
    void addCardByID(const CardDatabase& database, CardID id);

    Card* getCard(int index) const;
    void removeCard(int index);

    int getCardCount() const;
};

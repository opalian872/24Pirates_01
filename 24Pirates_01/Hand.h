// Hand.h

#pragma once

#include <vector>
#include "Card.h"
#include "Deck.h"

class Hand
{
private:
    std::vector<Card*> cards;

public:
    Hand();
    ~Hand();

    void DrawCards(const Deck& deck, int count);

    void addCard(Card* card);

    Card* getCard(int index) const;

    int getCardCount() const;

    const std::vector<Card*>& getCards() const;

    void Clear();
};

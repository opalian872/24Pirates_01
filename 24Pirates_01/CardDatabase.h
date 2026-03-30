#pragma once

#include <vector>
#include "Card.h"

class CardDatabase
{
private:
    std::vector<Card*> cardList;

public:
    CardDatabase();
    ~CardDatabase();

    void initialize();

    void addCard(Card* card);
    Card* getCardByID(CardID id) const;
    Card* getCardByIndex(int index) const;
    int getCardCount() const;
};

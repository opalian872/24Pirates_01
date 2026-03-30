#pragma once

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

class Hand
{
private:
    std::vector<Card*> cards;

public:
    Hand();
    ~Hand();

    // Draw cards at the start of a turn
    void DrawCards(const Deck& deck, int count, Player& player);

    // Add one card during the turn (for draw effects)
    void addCard(Card* card, Player& player);

    // Get one card
    Card* getCard(int index) const;

    // Number of cards in hand
    int getCardCount() const;

    // Return all cards for UI
    const std::vector<Card*>& getCards() const;

    // Clear hand at end of turn
    void Clear(Player& player);
};

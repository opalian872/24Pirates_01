// Hand.cpp

#include "Hand.h"
#include <cstdlib>

Hand::Hand()
{
}

Hand::~Hand()
{
    Clear();
}

void Hand::DrawCards(const Deck& deck, int count)
{
    Clear();

    int deckSize = deck.getCardCount();

    if (deckSize == 0)
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int randomIndex = rand() % deckSize;
        Card* card = deck.getCard(randomIndex);

        if (card != nullptr)
        {
            cards.push_back(card->clone());
        }
    }
}

void Hand::addCard(Card* card)
{
    if (card != nullptr)
    {
        cards.push_back(card);
    }
}

Card* Hand::getCard(int index) const
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        return nullptr;
    }

    return cards[index];
}

int Hand::getCardCount() const
{
    return static_cast<int>(cards.size());
}

const std::vector<Card*>& Hand::getCards() const
{
    return cards;
}

void Hand::Clear()
{
    for (Card* card : cards)
    {
        delete card;
    }

    cards.clear();
}

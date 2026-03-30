#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
    for (Card* card : cards)
    {
        delete card;
    }

    cards.clear();
}

void Deck::addCard(Card* card)
{
    cards.push_back(card);
}

void Deck::addCardByID(const CardDatabase& database, CardID id)
{
    Card* original = database.getCardByID(id);

    if (original != nullptr)
    {
        cards.push_back(original->clone());
    }
}

Card* Deck::getCard(int index) const
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        return nullptr;
    }

    return cards[index];
}

void Deck::removeCard(int index)
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        return;
    }

    delete cards[index];
    cards.erase(cards.begin() + index);
}

int Deck::getCardCount() const
{
    return static_cast<int>(cards.size());
}

#include "Hand.h"
#include <cstdlib>

Hand::Hand()
{
}

Hand::~Hand()
{
    for (Card* card : cards)
    {
        delete card;
    }

    cards.clear();
}

void Hand::DrawCards(const Deck& deck, int count, Player& player)
{
    Clear(player);

    int deckSize = deck.getCardCount();

    if (deckSize == 0)
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int randomIndex = rand() % deckSize;
        Card* original = deck.getCard(randomIndex);

        if (original != nullptr)
        {
            Card* newCard = original->clone();

            if (newCard->IsPassive())
            {
                newCard->ApplyPassive(player);
            }

            cards.push_back(newCard);
        }
    }
}

void Hand::addCard(Card* card, Player& player)
{
    if (card != nullptr)
    {
        if (card->IsPassive())
        {
            card->ApplyPassive(player);
        }

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

void Hand::Clear(Player& player)
{
    for (Card* card : cards)
    {
        if (card != nullptr && card->IsPassive())
        {
            card->RemovePassive(player);
        }

        delete card;
    }

    cards.clear();
}

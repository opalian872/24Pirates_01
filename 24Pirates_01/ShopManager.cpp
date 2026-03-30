#include "ShopManager.h"
#include "CardDatabase.h"
#include "Deck.h"
#include "Player.h"
#include <algorithm>
#include <random>
#include <iostream>

ShopManager::ShopManager(const CardDatabase& cardDatabase, Deck& playerDeck, Player& player)
    : cardDatabase(cardDatabase), playerDeck(playerDeck), player(player), hasReset(false), removeCardCount(0)
{
    InitializeShop();
}

void ShopManager::InitializeShop()
{
    shopCards.clear();

    for (int i = 0; i < 10; i++)
    {
        shopCards.push_back(ShopCardData());
    }

    ResetShop();

    hasReset = false;
}



bool ShopManager::BuyCard(int index)
{
    if (index < 0 || index >= 10)
    {
        return false;
    }

    if (shopCards[index].isEmpty)
    {
        return false;
    }

    int price = GetCardPrice(shopCards[index].rarity);

    if (!player.SubGold(price))
    {
        return false;
    }


    playerDeck.addCardByID(cardDatabase, shopCards[index].id);
    AddBlockedCard(shopCards[index].id);

    // 슬롯은 비우되 칸은 유지
    shopCards[index] = ShopCardData();

    return true;
}

bool ShopManager::RemoveCard(int deckIndex)
{
    if (removeCardCount >= 3)
    {
        return false;
    }

    Card* card = playerDeck.getCard(deckIndex);

    if (card == nullptr)
    {
        return false;
    }

    AddBlockedCard(card->getID());
    playerDeck.removeCard(deckIndex);
    removeCardCount++;

    return true;
}

bool ShopManager::CanRemoveCard() const
{
    return removeCardCount < 3;
}

int ShopManager::GetRemoveCardCount() const
{
    return removeCardCount;
}

bool ShopManager::RemoveRandomCard()
{
    int deckCount = playerDeck.getCardCount();

    if (deckCount <= 0)
    {
        return false;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> dist(0, deckCount - 1);

    int randomIndex = dist(g);

    Card* card = playerDeck.getCard(randomIndex);
    if (card == nullptr)
    {
        return false;
    }

    AddBlockedCard(card->getID());
    playerDeck.removeCard(randomIndex);

    return true;
}

const std::vector<ShopCardData>& ShopManager::GetShopCards() const
{
    return shopCards;
}

int ShopManager::GetDeckCardCount() const
{
    return playerDeck.getCardCount();
}

void ShopManager::ResetShop()
{
    if (hasReset)
    {
        return;
    }
    else
    {
        hasReset = true;

        for (int i = 0; i < 10; i++)
        {
            shopCards[i] = ShopCardData();
        }

        std::vector<ShopCardData> candidates;

        for (int i = 0; i < cardDatabase.getCardCount(); i++)
        {
            Card* card = cardDatabase.getCardByIndex(i);

            if (card == nullptr)
            {
                continue;
            }

            if (IsBlocked(card->getID()))
            {
                continue;
            }

            candidates.push_back(ConvertCardToShopData(card));
        }

        if (candidates.empty())
        {
            return;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(candidates.begin(), candidates.end(), g);

        int count = static_cast<int>(candidates.size());
        if (count > 10)
        {
            count = 10;
        }

        for (int i = 0; i < count; i++)
        {
            shopCards[i] = candidates[i];
        }
    }
    
}

bool ShopManager::CanResetShop() const
{
    return !hasReset;
}

int ShopManager::GetGold() const
{
    return player.GetGold();
}

Card* ShopManager::GetDeckCard(int index) const
{
    return playerDeck.getCard(index);
}

bool ShopManager::IsBlocked(CardID id) const
{
    for (CardID blockedID : blockedCardIDs)
    {
        if (blockedID == id)
        {
            return true;
        }
    }

    return false;
}

void ShopManager::AddBlockedCard(CardID id)
{
    if (IsBlocked(id))
    {
        return;
    }

    blockedCardIDs.push_back(id);
}

std::string ShopManager::RarityToString(CardRarity rarity) const
{
    switch (rarity)
    {
    case CardRarity::Normal:
        return "Normal";
    case CardRarity::Rare:
        return "Rare";
    case CardRarity::Epic:
        return "Epic";
    default:
        return "Unknown";
    }
}

ShopCardData ShopManager::ConvertCardToShopData(Card* card) const
{
    return ShopCardData(
        card->getID(),
        card->getName(),
        RarityToString(card->getRarity()),
        card->getDescription()
    );
}

int ShopManager::GetCardPrice(const std::string& rarity) const
{
    if (rarity == "Normal")
    {
        return 20;
    }
    else if (rarity == "Rare")
    {
        return 30;
    }
    else if (rarity == "Epic")
    {
        return 50;
    }

    return 0;
}

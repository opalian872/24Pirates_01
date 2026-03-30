#include "ShopManager.h"
#include "CardDatabase.h"
#include "Deck.h"
#include "Player.h"
#include <algorithm>
#include <random>

// 카드 DB와 덱, 플레이어를 받아 상점 데이터를 초기화
ShopManager::ShopManager(const CardDatabase& cardDatabase, Deck& playerDeck, Player& player)
    : cardDatabase(cardDatabase), playerDeck(playerDeck), player(player), hasUsedReset(false), removeCardCount(0), lastRandomRemoveGold(0)
{
    InitializeShop();
}

// 상점 슬롯 10칸을 만들고 첫 진열을 준비
void ShopManager::InitializeShop()
{
    shopCards.clear();

    for (int i = 0; i < 10; i++)
    {
        shopCards.push_back(ShopCardData());
    }

    ResetShop();

    // 처음 상점 생성은 리셋 사용으로 치지 않도록 다시 false 처리
    hasUsedReset = false;
}

// 차단되지 않은 카드만 다시 뽑아 상점을 새로고침
void ShopManager::ResetShop()
{
    if (hasUsedReset)
    {
        return;
    }

    hasUsedReset = true;

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

// 선택한 상점 카드를 구매해서 덱에 넣고 골드를 차감하며, 다시 상점에 못 나오게 처리
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

    // 슬롯은 비우되 칸 자체는 유지
    shopCards[index] = ShopCardData();

    return true;
}

// 플레이어 덱에서 선택한 카드를 제거하고, 해당 카드를 다시 상점에 못 나오게 처리
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

// 플레이어 덱에서 랜덤으로 1장을 제거하고, 해당 카드를 다시 상점에 못 나오게 처리
bool ShopManager::RemoveRandomCard()
{
    int deckCount = playerDeck.getCardCount();

    if (deckCount <= 0)
    {
        lastRandomRemoveGold = 0;
        return false;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    // 랜덤으로 제거할 카드
    std::uniform_int_distribution<int> dist(0, deckCount - 1);
    int randomIndex = dist(g);

    Card* card = playerDeck.getCard(randomIndex);
    if (card == nullptr)
    {
        lastRandomRemoveGold = 0;
        return false;
    }

    AddBlockedCard(card->getID());
    playerDeck.removeCard(randomIndex);

    // 0~60 골드 지급
    std::uniform_int_distribution<int> goldDist(0, 6);
    lastRandomRemoveGold = goldDist(g) * 10;

    player.GainGold(lastRandomRemoveGold, "Random remove reward ");

    return true;
}

int ShopManager::GetLastRandomRemoveGold() const
{
    return lastRandomRemoveGold;
}

// 현재 상점 슬롯 목록을 반환
const std::vector<ShopCardData>& ShopManager::GetShopCards() const
{
    return shopCards;
}

// 현재 플레이어 덱 카드 개수를 반환
int ShopManager::GetDeckCardCount() const
{
    return playerDeck.getCardCount();
}

// 플레이어 덱의 특정 위치 카드를 반환
Card* ShopManager::GetDeckCard(int index) const
{
    return playerDeck.getCard(index);
}

// 현재 플레이어 골드를 반환
int ShopManager::getGold() const
{
    return player.GetGold();
}

// 상점 리셋 가능 여부를 반환
bool ShopManager::CanResetShop() const
{
    return !hasUsedReset;
}

// 카드 제거 가능 여부를 반환
bool ShopManager::CanRemoveCard() const
{
    return removeCardCount < 3;
}

// 현재 카드 제거 사용 횟수를 반환
int ShopManager::GetRemoveCardCount() const
{
    return removeCardCount;
}

// 카드가 차단 목록에 있는지 확인
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

// 카드 ID를 차단 목록에 추가해서 이후 상점 후보에서 제외
void ShopManager::AddBlockedCard(CardID id)
{
    if (IsBlocked(id))
    {
        return;
    }

    blockedCardIDs.push_back(id);
}

// 희귀도 enum 값을 문자열로 바꿔서 출력용으로 사용
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

// Card 객체를 상점 출력용 구조체로 변환
ShopCardData ShopManager::ConvertCardToShopData(Card* card) const
{
    return ShopCardData(
        card->getID(),
        card->getName(),
        RarityToString(card->getRarity()),
        card->getDescription()
    );
}

// 희귀도에 따라 카드 가격을 반환
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

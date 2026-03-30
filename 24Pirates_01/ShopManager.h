#pragma once
#include <vector>
#include <string>
#include "Card.h"

class CardDatabase;
class Deck;
class Player;

// 상점에 표시할 카드 정보를 담는 구조체
struct ShopCardData
{
    CardID id;
    std::string name;
    std::string rarity;
    std::string description;
    bool isEmpty;

    ShopCardData()
        : id(CardID::Strike), name(""), rarity(""), description(""), isEmpty(true) {
    }

    ShopCardData(CardID id, const std::string& name, const std::string& rarity, const std::string& description)
        : id(id), name(name), rarity(rarity), description(description), isEmpty(false) {
    }
};

// 상점 카드 진열, 구매, 제거, 리셋 제한을 관리하는 클래스
class ShopManager
{
private:
    const CardDatabase& cardDatabase;
    Deck& playerDeck;
    Player& player;

    // 현재 상점에 진열 중인 10칸 슬롯
    std::vector<ShopCardData> shopCards;

    // 다시 상점에 나오면 안 되는 카드 ID 목록
    std::vector<CardID> blockedCardIDs;

    // 상점 리셋 사용 여부
    bool hasUsedReset;

    // 덱 카드 제거 사용 횟수
    int removeCardCount;

    // 해당 카드 ID가 이미 상점 차단 목록에 있는지 확인
    bool IsBlocked(CardID id) const;

    // 카드 ID를 차단 목록에 추가해서 다시 상점에 나오지 못하게 함
    void AddBlockedCard(CardID id);

    // 카드 희귀도 enum 값을 문자열로 변환
    std::string RarityToString(CardRarity rarity) const;

    // Card 객체를 상점 출력용 데이터로 변환
    ShopCardData ConvertCardToShopData(Card* card) const;

    // 희귀도에 따라 카드 가격을 반환
    int GetCardPrice(const std::string& rarity) const;

public:
    // 카드 DB, 플레이어 덱, 플레이어 정보를 연결해서 상점 관리 객체를 생성
    ShopManager(const CardDatabase& cardDatabase, Deck& playerDeck, Player& player);

    // 상점 슬롯 10칸을 만들고 초기 카드 진열을 준비
    void InitializeShop();

    // 차단되지 않은 카드들만 다시 뽑아서 상점을 새로고침
    void ResetShop();

    // 상점 슬롯의 카드를 구매해서 덱에 추가하고 골드를 차감
    bool BuyCard(int index);

    // 플레이어 덱에서 선택한 카드를 제거하고 상점 재등장을 막음
    bool RemoveCard(int deckIndex);

    // 플레이어 덱에서 카드를 랜덤으로 1장 제거하고 상점 재등장을 막음
    bool RemoveRandomCard();

    // 현재 상점 슬롯 목록을 반환
    const std::vector<ShopCardData>& GetShopCards() const;

    // 현재 플레이어 덱 카드 개수를 반환
    int GetDeckCardCount() const;

    // 플레이어 덱에서 특정 위치의 카드를 반환
    Card* GetDeckCard(int index) const;

    // 현재 플레이어 골드를 반환
    int getGold() const;

    // 상점 리셋 가능 여부를 반환
    bool CanResetShop() const;

    // 카드 제거 가능 여부를 반환
    bool CanRemoveCard() const;

    // 현재 카드 제거 사용 횟수를 반환
    int GetRemoveCardCount() const;

};

#include "Card.h"
#include "PlayerDummy.h"
#include "EnemyDummy.h"

#include <cstdlib>
#include <ctime>

namespace
{
    bool IsValidTarget(const std::vector<Enemy>& enemies, int targetIndex)
    {
        return targetIndex >= 0 &&
            targetIndex < static_cast<int>(enemies.size()) &&
            !enemies[targetIndex].isDead();
    }

    void DealDamageToTarget(std::vector<Enemy>& enemies, int targetIndex, int damage)
    {
        if (IsValidTarget(enemies, targetIndex))
        {
            enemies[targetIndex].takeDamage(damage);
        }
    }

    void DealDamageToAll(std::vector<Enemy>& enemies, int damage)
    {
        for (Enemy& enemy : enemies)
        {
            if (!enemy.isDead())
            {
                enemy.takeDamage(damage);
            }
        }
    }

    int RandomRange(int minValue, int maxValue)
    {
        if (maxValue < minValue)
        {
            int temp = minValue;
            minValue = maxValue;
            maxValue = temp;
        }

        return (std::rand() % (maxValue - minValue + 1)) + minValue;
    }

    bool g_randomSeeded = false;

    void SeedRandomOnce()
    {
        if (!g_randomSeeded)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            g_randomSeeded = true;
        }
    }
}

Card::Card(CardID id,
    CardRarity rarity,
    const std::string& name,
    const std::string& description,
    const std::string& effectText,
    CardType cardType,
    TargetType targetType)
    : id(id),
    rarity(rarity),
    name(name),
    description(description),
    effectText(effectText),
    cardType(cardType),
    targetType(targetType)
{
}

CardID Card::getID() const
{
    return id;
}

CardRarity Card::getRarity() const
{
    return rarity;
}

std::string Card::getName() const
{
    return name;
}

std::string Card::getDescription() const
{
    return description;
}

std::string Card::getEffectText() const
{
    return effectText;
}

CardType Card::getCardType() const
{
    return cardType;
}

TargetType Card::getTargetType() const
{
    return targetType;
}

bool Card::IsPassive() const
{
    return cardType == CardType::Passive;
}

bool Card::IsPlayableInHand() const
{
    return cardType == CardType::Active;
}

Card* Card::clone() const
{
    return new Card(*this);
}

void Card::ApplyPassive(Player& player) const
{
    if (cardType != CardType::Passive)
    {
        return;
    }

    switch (id)
    {
    case CardID::CaffeineOverdose:
        player.addAttack(15);
        break;

    case CardID::CtrlSObsessive:
        player.addDefense(5);
        break;

    case CardID::TruthRoom:
        player.addAttack(20);
        break;

    case CardID::TeamProjectPainBuff:
        player.addAttack(30);
        break;

    case CardID::FocusBurst:
        player.addAttack(20);
        break;

    case CardID::Emergency:
        player.addAttack(30);
        break;

    case CardID::CodeFusion:
        player.addAttack(50);
        break;

    default:
        break;
    }
}

void Card::RemovePassive(Player& player) const
{
    if (cardType != CardType::Passive)
    {
        return;
    }

    switch (id)
    {
    case CardID::CaffeineOverdose:
        player.addAttack(-15);
        break;

    case CardID::CtrlSObsessive:
        player.addDefense(-5);
        break;

    case CardID::TruthRoom:
        player.addAttack(-20);
        break;

    case CardID::TeamProjectPainBuff:
        player.addAttack(-30);
        break;

    case CardID::FocusBurst:
        player.addAttack(-20);
        break;

    case CardID::Emergency:
        player.addAttack(-30);
        break;

    case CardID::CodeFusion:
        player.addAttack(-50);
        break;

    default:
        break;
    }
}

void Card::use(Player& player, std::vector<Enemy>& enemies, int targetIndex) const
{
    SeedRandomOnce();

    // Passive cards are not directly playable in hand.
    if (cardType == CardType::Passive)
    {
        return;
    }

    switch (id)
    {
    case CardID::KeyboardSmash:
        DealDamageToTarget(enemies, targetIndex, 30);
        break;

    case CardID::DoubleClickBug:
        DealDamageToTarget(enemies, targetIndex, 18);
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, 18);
        }
        break;

    case CardID::SuddenBathroom:
        player.addDefense(20);
        break;

    case CardID::MonitorOff:
        player.addDefense(10);
        break;

    case CardID::ChairPush:
        DealDamageToTarget(enemies, targetIndex, 20);
        break;

    case CardID::CtrlZLife:
        player.heal(15);
        break;

    case CardID::SuddenWorkingCode:
    {
        int randomEffect = RandomRange(1, 5);

        switch (randomEffect)
        {
        case 1:
            DealDamageToTarget(enemies, targetIndex, 35);
            break;

        case 2:
            player.heal(20);
            break;

        case 3:
            player.addAttack(15);
            break;

        case 4:
            player.addDefense(15);
            break;

        case 5:
            DealDamageToAll(enemies, 15);
            break;

        default:
            break;
        }
        break;
    }

    case CardID::HitTheComputer:
        DealDamageToTarget(enemies, targetIndex, 50);
        break;

    case CardID::SuddenSleepiness:
        player.heal(20);
        break;

    case CardID::MemeAttack:
        DealDamageToTarget(enemies, targetIndex, 25);
        break;

    case CardID::BlankMaster:
        player.heal(25);
        break;

    case CardID::LaptopFanTurboMode:
        DealDamageToAll(enemies, 12);
        break;

    case CardID::InternetDisconnected:
        player.heal(30);
        break;

    case CardID::DeleteWholeCode:
        DealDamageToTarget(enemies, targetIndex, 60);
        break;

    case CardID::Reboot:
        player.heal(9999);
        break;

    case CardID::ShakeWifi:
        DealDamageToTarget(enemies, targetIndex, 12);
        break;

    case CardID::DebugHell:
        DealDamageToTarget(enemies, targetIndex, 35);
        break;

    case CardID::FileRecovery:
        player.heal(20);
        break;

    case CardID::ServerConnect:
        player.heal(10);
        break;

    case CardID::ServerExplosion:
        DealDamageToAll(enemies, 30);
        break;

    case CardID::KeyboardMash:
        DealDamageToTarget(enemies, targetIndex, 10);
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, 10);
        }
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, 10);
        }
        break;

    case CardID::CodeRampage:
        DealDamageToTarget(enemies, targetIndex, 60);
        break;

    case CardID::AssignmentCurse:
        DealDamageToAll(enemies, 35);
        break;

    case CardID::OverNightTranscendence:
        DealDamageToTarget(enemies, targetIndex, RandomRange(1, 999));
        break;

    case CardID::RescueTouch:
        player.heal(50);
        break;

    case CardID::CpuFullPower:
        DealDamageToTarget(enemies, targetIndex, 70);
        break;

    default:
        break;
    }
}

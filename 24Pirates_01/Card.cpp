#include "Card.h"
#include "Player.h"
#include "Enemy.h"

#include <cstdlib>
#include <ctime>
#include <memory>

namespace
{
    bool IsValidTarget(const std::vector<std::unique_ptr<Enemy>>& enemies, int targetIndex)
    {
        return targetIndex >= 0 &&
            targetIndex < static_cast<int>(enemies.size()) &&
            enemies[targetIndex] != nullptr &&
            !enemies[targetIndex]->IsDead();
    }

    void DealDamageToTarget(std::vector<std::unique_ptr<Enemy>>& enemies, int targetIndex, int damage)
    {
        if (IsValidTarget(enemies, targetIndex))
        {
            enemies[targetIndex]->TakeDamage(damage);
        }
    }

    void DealDamageToAll(std::vector<std::unique_ptr<Enemy>>& enemies, int damage)
    {
        for (auto& enemy : enemies)
        {
            if (enemy != nullptr && !enemy->IsDead())
            {
                enemy->TakeDamage(damage);
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

    int ScaleFromPlayerAttack(Player& player, double multiplier, int bonus = 0)
    {
        int damage = static_cast<int>(player.GetAttack() * multiplier) + bonus;

        if (damage < 0)
        {
            damage = 0;
        }

        return damage;
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
        player.addDefense(1);
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

void Card::use(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, int targetIndex) const
{
    SeedRandomOnce();

    if (cardType == CardType::Passive)
    {
        return;
    }

    switch (id)
    {
    case CardID::KeyboardSmash:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 1.0));
        break;

    case CardID::DoubleClickBug:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.6));
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.6));
        }
        break;

    case CardID::SuddenBathroom:
        player.addDefense(7);
        break;

    case CardID::MonitorOff:
        player.addDefense(3);
        break;

    case CardID::ChairPush:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.8));
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
            DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 1.2));
            break;

        case 2:
            player.heal(20);
            break;

        case 3:
            player.addAttack(15);
            break;

        case 4:
            player.addDefense(6);
            break;

        case 5:
            DealDamageToAll(enemies, ScaleFromPlayerAttack(player, 0.5));
            break;

        default:
            break;
        }
        break;
    }

    case CardID::HitTheComputer:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 1.5));
        break;

    case CardID::SuddenSleepiness:
        player.heal(20);
        break;

    case CardID::MemeAttack:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.9));
        break;

    case CardID::BlankMaster:
        player.heal(25);
        break;

    case CardID::LaptopFanTurboMode:
        DealDamageToAll(enemies, ScaleFromPlayerAttack(player, 0.4));
        break;

    case CardID::InternetDisconnected:
        player.heal(30);
        break;

    case CardID::DeleteWholeCode:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 2.0));
        break;

    case CardID::TeamProjectPainBuff:
        // Passive card, not directly usable
        break;

    case CardID::Reboot:
        player.heal(9999);
        break;

    case CardID::ShakeWifi:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.5));
        break;

    case CardID::DebugHell:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 1.2));
        break;

    case CardID::FileRecovery:
        player.heal(20);
        break;

    case CardID::FocusBurst:
        // Passive card, not directly usable
        break;

    case CardID::ServerConnect:
        player.heal(10);
        break;

    case CardID::ServerExplosion:
        DealDamageToAll(enemies, ScaleFromPlayerAttack(player, 0.8));
        break;

    case CardID::KeyboardMash:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.35));
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.35));
        }
        if (IsValidTarget(enemies, targetIndex))
        {
            DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 0.35));
        }
        break;

    case CardID::CodeRampage:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 2.0));
        break;

    case CardID::Emergency:
        // Passive card, not directly usable
        break;

    case CardID::AssignmentCurse:
        DealDamageToAll(enemies, ScaleFromPlayerAttack(player, 1.0));
        break;

    case CardID::OverNightTranscendence:
        DealDamageToTarget(enemies, targetIndex, RandomRange(1, 999));
        break;

    case CardID::RescueTouch:
        player.heal(50);
        break;

    case CardID::CodeFusion:
        // Passive card, not directly usable
        break;

    case CardID::CpuFullPower:
        DealDamageToTarget(enemies, targetIndex, ScaleFromPlayerAttack(player, 2.3));
        break;

    default:
        break;
    }
}

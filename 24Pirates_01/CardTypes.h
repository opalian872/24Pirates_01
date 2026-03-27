// CardTypes.h

#pragma once

enum class CardType
{
    Active,
    Passive
};

enum class TargetType
{
    Self,
    SingleEnemy,
    AllEnemies,
    None
};

enum class CardRarity
{
    Normal,
    Rare,
    Epic
};

enum class CardID
{
    Strike,
    Heal,
    DefenseBoost,
    AttackBoost,
    DoubleHit,
    MemoryShield,
    Regeneration,
    Whirlwind
};

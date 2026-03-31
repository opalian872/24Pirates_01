// Enemy.cpp

#include "Enemy.h"

Enemy::Enemy(std::string name, int baseHp, int baseAtk, int baseDef, int baseExp, int baseGold, int roomCount)
    : engName(name), maxHp(baseHp), atk(baseAtk), def(baseDef), getExp(baseExp), getGold(baseGold)
{
    // 몬스터 생성 시 현재 roomcount를 기준으로 스탯 증가
    ApplyScaling(roomCount);
    // 스케일링 종료 시 maxHp로 현재 체력 회복
    currentHp = maxHp;
}

void Enemy::ApplyScaling(int roomCount)
{
    // 방 1개 당 스탯 10% 증가
    float scaleFactor = 1.0f + (roomCount * 0.1f);

    maxHp = static_cast<int>(maxHp * scaleFactor);
    atk = static_cast<int>(atk * scaleFactor);
    getExp = static_cast<int>(getExp * scaleFactor);
    getGold = static_cast<int>(getGold * scaleFactor);

    // 방어력 증가의 경우 테스트 후 맞는 방식으로 사용하는 것으로.
    // def += (roomCount / 3);
    def = static_cast<int>(def * scaleFactor);
}

void Enemy::TakeDamage(int damage)
{
    int actualDamage = damage - def;
    if (actualDamage > 0)
    {
        currentHp -= actualDamage;
    }
    if (currentHp < 0) currentHp = 0;
}

bool Enemy::IsDead() const
{
    return currentHp <= 0;
}

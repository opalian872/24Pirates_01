#pragma once
#include <iostream>
#include <string>

class Player
{
private:
    std::string playerName; // 플레이어 이름
    int level; // 플레이어 레벨
    int hp; // 플레이어 현재 체력
    int maxHp; // 플레이어 최대 체력
    int attack; // 플레이어 공격력
    int defense; // 플레이어 방어력
    int exp; // 플레이어 현재 경험치
    int gold; // 플레이어 소지금
    bool playerCondition; // 플레이어의 생존 유무. true 상태일 때가 생존.

public:
    Player(std::string name); // 플레이어 이름

    void ShowStatus(); //플레이어 스테이터스창
    void Usecard(); //플레이어 사용 카드
    void TakeDamage(int damage); //플레이어가 몬스터에게 대미지를 받음
    void Heal(int healAmount); // 플레이어가 체력을 회복함
    void GainExp(int expAmount); // 플레이어가 경험치를 획득함
    void LevelUp(); // 플레이어가 레벨업을 함
    void PlayerMaking(std::string name, int& level, int& maxHp, int& hp, int& attack, int& defense, int& exp, int& gold, bool& playerCondition);
};


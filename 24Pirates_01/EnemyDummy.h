#pragma once

struct Enemy
{
public:
    void takeDamage(int damage) {}
    bool isDead() const { return false; }
};

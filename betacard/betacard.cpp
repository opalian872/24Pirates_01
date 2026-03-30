#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// ======================================================
// Enums
// ======================================================
enum class TargetType
{
    Self,
    SingleEnemy,
    AllEnemies,
    None
};

enum class CardType
{
    Active,
    Passive
};

// ======================================================
// Buff
// ======================================================
struct Buff
{
    string name;
    int attackBonus;
    int defenseBonus;
    int remainingTurns;

    Buff(const string& name, int attackBonus, int defenseBonus, int remainingTurns)
        : name(name), attackBonus(attackBonus), defenseBonus(defenseBonus), remainingTurns(remainingTurns) {
    }
};

// ======================================================
// Forward Declarations
// ======================================================
class Player;
class Enemy;

// ======================================================
// Enemy
// ======================================================
class Enemy
{
private:
    string name;
    int hp;
    int maxHp;
    int attack;
    int defense;

public:
    Enemy(const string& name, int hp, int attack, int defense)
        : name(name), hp(hp), maxHp(hp), attack(attack), defense(defense) {
    }

    string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    bool isDead() const
    {
        return hp <= 0;
    }

    void takeDamage(int damage)
    {
        int finalDamage = damage - defense;
        if (finalDamage < 0)
        {
            finalDamage = 0;
        }

        hp -= finalDamage;
        if (hp < 0)
        {
            hp = 0;
        }

        cout << name << " took " << finalDamage << " damage.\n";

        if (isDead())
        {
            cout << name << " was defeated.\n";
        }
    }
};

// ======================================================
// Player
// ======================================================
class Player
{
private:
    int hp;
    int maxHp;
    int baseAttack;
    int baseDefense;
    vector<Buff> buffs;

public:
    Player(int hp, int attack, int defense)
        : hp(hp), maxHp(hp), baseAttack(attack), baseDefense(defense) {
    }

    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }

    int getTotalAttack() const
    {
        int total = baseAttack;
        for (const Buff& buff : buffs)
        {
            total += buff.attackBonus;
        }
        return total;
    }

    int getTotalDefense() const
    {
        int total = baseDefense;
        for (const Buff& buff : buffs)
        {
            total += buff.defenseBonus;
        }
        return total;
    }

    bool isDead() const
    {
        return hp <= 0;
    }

    void heal(int amount)
    {
        hp += amount;
        if (hp > maxHp)
        {
            hp = maxHp;
        }

        cout << "Player healed " << amount << " HP.\n";
    }

    void takeDamage(int damage)
    {
        int finalDamage = damage - getTotalDefense();
        if (finalDamage < 0)
        {
            finalDamage = 0;
        }

        hp -= finalDamage;
        if (hp < 0)
        {
            hp = 0;
        }

        cout << "Player took " << finalDamage << " damage.\n";
    }

    void addBuff(const string& name, int attackBonus, int defenseBonus, int remainingTurns)
    {
        buffs.push_back(Buff(name, attackBonus, defenseBonus, remainingTurns));
        cout << "Buff applied: " << name << "\n";
    }

    void decreaseBuffTurns()
    {
        for (Buff& buff : buffs)
        {
            buff.remainingTurns--;
        }

        buffs.erase(
            remove_if(
                buffs.begin(),
                buffs.end(),
                [](const Buff& buff)
                {
                    return buff.remainingTurns <= 0;
                }
            ),
            buffs.end()
        );
    }

    const vector<Buff>& getBuffs() const
    {
        return buffs;
    }
};

// ======================================================
// Card Base Class
// ======================================================
class Card
{
protected:
    string name;
    string description;
    CardType cardType;
    TargetType targetType;

public:
    Card(const string& name, const string& description, CardType cardType, TargetType targetType)
        : name(name), description(description), cardType(cardType), targetType(targetType) {
    }

    virtual ~Card() {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    CardType getCardType() const { return cardType; }
    TargetType getTargetType() const { return targetType; }

    virtual void use(Player& player, vector<Enemy>& enemies, int targetIndex) = 0;

    vector<string> getCardLines(int index) const
    {
        vector<string> lines;

        const int cardWidth = 30;
        const int innerWidth = 28;

        string typeText = (cardType == CardType::Active) ? "Active" : "Passive";

        string targetText = "None";
        switch (targetType)
        {
        case TargetType::Self:
            targetText = "Self";
            break;
        case TargetType::SingleEnemy:
            targetText = "SingleEnemy";
            break;
        case TargetType::AllEnemies:
            targetText = "AllEnemies";
            break;
        case TargetType::None:
            targetText = "None";
            break;
        }

        auto makeBorder = [&]() -> string
            {
                return "+" + string(innerWidth, '-') + "+";
            };

        auto makeEmptyLine = [&]() -> string
            {
                return "|" + string(innerWidth, ' ') + "|";
            };

        auto fitText = [&](const string& text, int maxLen) -> string
            {
                if (static_cast<int>(text.length()) <= maxLen)
                {
                    return text;
                }

                if (maxLen <= 3)
                {
                    return text.substr(0, maxLen);
                }

                return text.substr(0, maxLen - 3) + "...";
            };

        auto makeTextLine = [&](const string& text) -> string
            {
                string trimmed = fitText(text, innerWidth - 2);
                string line = "| " + trimmed;

                while (static_cast<int>(line.length()) < cardWidth - 1)
                {
                    line += ' ';
                }

                line += "|";
                return line;
            };

        lines.push_back(makeBorder());                                   // 1
        lines.push_back(makeTextLine("[" + to_string(index) + "]"));     // 2
        lines.push_back(makeTextLine(name));                             // 3
        lines.push_back(makeBorder());                                   // 4
        lines.push_back(makeTextLine("Type: " + typeText));              // 5
        lines.push_back(makeTextLine("Target: " + targetText));          // 6
        lines.push_back(makeEmptyLine());                                // 7
        lines.push_back(makeTextLine("Description"));                    // 8
        lines.push_back(makeBorder());                                   // 9

        string desc1 = fitText(description, innerWidth - 2);
        string remaining = "";

        if (static_cast<int>(description.length()) > innerWidth - 2)
        {
            remaining = description.substr(innerWidth - 2);
        }

        string desc2 = fitText(remaining, innerWidth - 2);

        lines.push_back(makeTextLine(desc1));                            // 10
        lines.push_back(makeTextLine(desc2));                            // 11
        lines.push_back(makeEmptyLine());                                // 12
        lines.push_back(makeEmptyLine());                                // 13
        lines.push_back(makeEmptyLine());                                // 14
        lines.push_back(makeBorder());                                   // 15

        return lines;
    }
};

// ======================================================
// Cards
// ======================================================
class StrikeCard : public Card
{
public:
    StrikeCard()
        : Card("Strike", "Deal 12 damage to one enemy", CardType::Active, TargetType::SingleEnemy) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size()))
        {
            cout << "Invalid target.\n";
            return;
        }

        if (enemies[targetIndex].isDead())
        {
            cout << "That enemy is already defeated.\n";
            return;
        }

        enemies[targetIndex].takeDamage(12 + player.getTotalAttack());
    }
};

class HealCard : public Card
{
public:
    HealCard()
        : Card("Heal", "Recover 10 HP", CardType::Active, TargetType::Self) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        player.heal(10);
    }
};

class DefenseBoostCard : public Card
{
public:
    DefenseBoostCard()
        : Card("Defense Boost", "Gain +3 defense for 3 turns", CardType::Passive, TargetType::Self) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        player.addBuff("Defense +3", 0, 3, 3);
    }
};

class AttackBoostCard : public Card
{
public:
    AttackBoostCard()
        : Card("Attack Boost", "Gain +2 attack for 1 turn", CardType::Passive, TargetType::Self) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        player.addBuff("Attack +2", 2, 0, 1);
    }
};

class DoubleHitCard : public Card
{
public:
    DoubleHitCard()
        : Card("Double Hit", "Hit one enemy 2 times with 70 percent attack", CardType::Passive, TargetType::SingleEnemy) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        if (targetIndex < 0 || targetIndex >= static_cast<int>(enemies.size()))
        {
            cout << "Invalid target.\n";
            return;
        }

        if (enemies[targetIndex].isDead())
        {
            cout << "That enemy is already defeated.\n";
            return;
        }

        int hitDamage = static_cast<int>(player.getTotalAttack() * 0.7);

        enemies[targetIndex].takeDamage(hitDamage);

        if (!enemies[targetIndex].isDead())
        {
            enemies[targetIndex].takeDamage(hitDamage);
        }
    }
};

class MemoryShieldCard : public Card
{
public:
    MemoryShieldCard()
        : Card("Memory Shield", "Gain defense equal to alive enemy count", CardType::Passive, TargetType::None) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        int aliveCount = 0;

        for (const Enemy& enemy : enemies)
        {
            if (!enemy.isDead())
            {
                aliveCount++;
            }
        }

        player.addBuff("Memory Shield", 0, aliveCount, 1);
    }
};

class RegenerationCard : public Card
{
public:
    RegenerationCard()
        : Card("Regeneration", "Recover 1 HP at end of each turn", CardType::Passive, TargetType::Self) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        player.addBuff("Regeneration", 0, 0, 3);
    }
};

class WhirlwindCard : public Card
{
public:
    WhirlwindCard()
        : Card("Whirlwind", "Deal 8 damage to all enemies", CardType::Active, TargetType::AllEnemies) {
    }

    void use(Player& player, vector<Enemy>& enemies, int targetIndex) override
    {
        for (Enemy& enemy : enemies)
        {
            if (!enemy.isDead())
            {
                enemy.takeDamage(8 + player.getTotalAttack());
            }
        }
    }
};

// ======================================================
// Helper Functions
// ======================================================
void printEnemies(const vector<Enemy>& enemies)
{
    cout << "\n=== Enemies ===\n";
    for (int i = 0; i < static_cast<int>(enemies.size()); i++)
    {
        cout << "[" << i + 1 << "] "
            << enemies[i].getName()
            << " HP: " << enemies[i].getHp()
            << "/" << enemies[i].getMaxHp();

        if (enemies[i].isDead())
        {
            cout << " [DEAD]";
        }

        cout << "\n";
    }
}

void printBuffs(const Player& player)
{
    const vector<Buff>& buffs = player.getBuffs();

    cout << "\n=== Buffs ===\n";
    if (buffs.empty())
    {
        cout << "No active buffs.\n";
        return;
    }

    for (const Buff& buff : buffs)
    {
        cout << buff.name
            << " | ATK +" << buff.attackBonus
            << " | DEF +" << buff.defenseBonus
            << " | Turns: " << buff.remainingTurns << "\n";
    }
}

bool allEnemiesDead(const vector<Enemy>& enemies)
{
    for (const Enemy& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            return false;
        }
    }
    return true;
}

int chooseTarget(const vector<Enemy>& enemies)
{
    while (true)
    {
        cout << "Choose target enemy number: ";
        int input;
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        int index = input - 1;

        if (index < 0 || index >= static_cast<int>(enemies.size()))
        {
            cout << "Invalid target number.\n";
            continue;
        }

        if (enemies[index].isDead())
        {
            cout << "That enemy is already defeated.\n";
            continue;
        }

        return index;
    }
}

void processRegeneration(Player& player)
{
    const vector<Buff>& buffs = player.getBuffs();

    for (const Buff& buff : buffs)
    {
        if (buff.name == "Regeneration")
        {
            player.heal(1);
        }
    }
}

void enemyTurn(Player& player, vector<Enemy>& enemies)
{
    cout << "\n=== Enemy Turn ===\n";

    for (Enemy& enemy : enemies)
    {
        if (!enemy.isDead())
        {
            cout << enemy.getName() << " attacks!\n";
            player.takeDamage(enemy.getAttack());

            if (player.isDead())
            {
                return;
            }
        }
    }
}

void printCardGroupHorizontal(const vector<Card*>& hand, int startIndex, int endIndex)
{
    vector<vector<string>> allCards;

    for (int i = startIndex; i < endIndex; i++)
    {
        allCards.push_back(hand[i]->getCardLines(i + 1));
    }

    int lineCount = static_cast<int>(allCards[0].size());

    for (int line = 0; line < lineCount; line++)
    {
        for (int card = 0; card < static_cast<int>(allCards.size()); card++)
        {
            cout << allCards[card][line] << "  ";
        }
        cout << "\n";
    }
}

void printHandHorizontal(const vector<Card*>& hand)
{
    cout << "\n=== Hand ===\n";

    if (hand.empty())
    {
        cout << "Hand is empty.\n";
        return;
    }

    const int cardsPerRow = 5;

    for (int start = 0; start < static_cast<int>(hand.size()); start += cardsPerRow)
    {
        int end = min(start + cardsPerRow, static_cast<int>(hand.size()));
        printCardGroupHorizontal(hand, start, end);
        cout << "\n";
    }
}

// ======================================================
// Main
// ======================================================
int main()
{
    Player player(100, 10, 3);

    vector<Enemy> enemies;
    enemies.push_back(Enemy("Goblin", 30, 8, 1));
    enemies.push_back(Enemy("Orc", 45, 10, 2));
    enemies.push_back(Enemy("Slime", 25, 6, 0));

    vector<Card*> hand;
    hand.push_back(new StrikeCard());
    hand.push_back(new HealCard());
    hand.push_back(new DefenseBoostCard());
    hand.push_back(new AttackBoostCard());
    hand.push_back(new DoubleHitCard());

    while (!player.isDead() && !allEnemiesDead(enemies) && !hand.empty())
    {
        cout << "\n============================================================\n";
        cout << "Player HP: " << player.getHp() << "/" << player.getMaxHp()
            << " | ATK: " << player.getTotalAttack()
            << " | DEF: " << player.getTotalDefense() << "\n";

        printBuffs(player);
        printEnemies(enemies);
        printHandHorizontal(hand);

        cout << "Choose a card number to use (0 to end turn): ";
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 0)
        {
            processRegeneration(player);
            enemyTurn(player, enemies);
            player.decreaseBuffTurns();
            continue;
        }

        int cardIndex = choice - 1;

        if (cardIndex < 0 || cardIndex >= static_cast<int>(hand.size()))
        {
            cout << "Invalid card number.\n";
            continue;
        }

        Card* selectedCard = hand[cardIndex];
        int targetIndex = -1;

        if (selectedCard->getTargetType() == TargetType::SingleEnemy)
        {
            printEnemies(enemies);
            targetIndex = chooseTarget(enemies);
        }

        cout << "\nUsed card: " << selectedCard->getName() << "\n";
        selectedCard->use(player, enemies, targetIndex);

        delete selectedCard;
        hand.erase(hand.begin() + cardIndex);

        if (allEnemiesDead(enemies))
        {
            break;
        }

        processRegeneration(player);
        enemyTurn(player, enemies);
        player.decreaseBuffTurns();
    }

    cout << "\n============================================================\n";
    if (player.isDead())
    {
        cout << "Game Over\n";
    }
    else if (allEnemiesDead(enemies))
    {
        cout << "Victory\n";
    }
    else
    {
        cout << "Battle ended.\n";
    }

    for (Card* card : hand)
    {
        delete card;
    }

    return 0;
}

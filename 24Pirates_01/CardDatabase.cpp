#include "CardDatabase.h"

CardDatabase::CardDatabase()
{
    initialize();
}

CardDatabase::~CardDatabase()
{
    for (Card* card : cardList)
    {
        delete card;
    }

    cardList.clear();
}

void CardDatabase::initialize()
{
    addCard(new Card(
        CardID::KeyboardSmash,
        CardRarity::Normal,
        "Keyboard Smash",
        "You kick the keyboard instead of typing with your hands.",
        "Deal damage equal to 100% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::DoubleClickBug,
        CardRarity::Normal,
        "Double-Click Bug",
        "The mouse glitches and clicks twice at the perfect moment.",
        "Deal damage equal to 60% of your attack twice to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::SuddenBathroom,
        CardRarity::Normal,
        "Sudden Bathroom Trip",
        "You urgently run away and somehow become harder to hit.",
        "Gain 7 defense.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::MonitorOff,
        CardRarity::Normal,
        "Monitor Turned Off",
        "The screen goes dark, but you brace yourself and stay calm.",
        "Gain 3 defense.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::ChairPush,
        CardRarity::Normal,
        "Chair Push",
        "You shove the chair forward to hit the enemy.",
        "Deal damage equal to 80% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::CtrlZLife,
        CardRarity::Normal,
        "Ctrl + Z Life",
        "You wish real life had an undo button.",
        "Recover 15 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::SuddenWorkingCode,
        CardRarity::Rare,
        "Sudden Working Code",
        "It suddenly works for no reason. Nobody understands why.",
        "Trigger one random effect.",
        CardType::Active,
        TargetType::None
    ));

    addCard(new Card(
        CardID::HitTheComputer,
        CardRarity::Rare,
        "Hit the Computer",
        "It is not scientific, but sometimes violence fixes everything.",
        "Deal damage equal to 150% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::SuddenSleepiness,
        CardRarity::Rare,
        "Sudden Sleepiness",
        "You get sleepy in the middle of the fight and recover instead.",
        "Recover 20 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::MemeAttack,
        CardRarity::Rare,
        "Meme Attack",
        "A cursed meme is shown to the enemy's face.",
        "Deal damage equal to 90% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::CaffeineOverdose,
        CardRarity::Rare,
        "Caffeine Overdose",
        "Too much coffee makes your body shake with power.",
        "While held, gain 15 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::CtrlSObsessive,
        CardRarity::Rare,
        "Ctrl + S Obsession",
        "You save every three seconds and feel strangely safer.",
        "While held, gain defense.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::BlankMaster,
        CardRarity::Epic,
        "Master of Zoning Out",
        "You stare at the screen and recover through pure emptiness.",
        "Recover 25 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::LaptopFanTurboMode,
        CardRarity::Epic,
        "Laptop Fan Turbo Mode",
        "The fan screams like an airplane and damages all enemies.",
        "Deal damage equal to 40% of your attack to all enemies.",
        CardType::Active,
        TargetType::AllEnemies
    ));

    addCard(new Card(
        CardID::TruthRoom,
        CardRarity::Epic,
        "Room of Truth",
        "A brutal lesson reveals how weak your understanding truly is.",
        "While held, gain 20 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::InternetDisconnected,
        CardRarity::Epic,
        "Internet Disconnected",
        "The network dies completely. You stop and recover yourself.",
        "Recover 30 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::DeleteWholeCode,
        CardRarity::Epic,
        "Delete the Entire Code",
        "The whole project vanishes in one fatal mistake.",
        "Deal damage equal to 200% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::TeamProjectPainBuff,
        CardRarity::Epic,
        "Team Project Pain Buff",
        "The suffering of teamwork hardens your fighting spirit.",
        "While held, gain 30 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::Reboot,
        CardRarity::Epic,
        "Reboot",
        "The universal solution to every problem.",
        "Fully recover HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::ShakeWifi,
        CardRarity::Normal,
        "Shake the Wi-Fi",
        "You desperately try to make the signal come back.",
        "Deal damage equal to 50% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::DebugHell,
        CardRarity::Rare,
        "Debug Hell",
        "You return alive from debugging hell and strike back.",
        "Deal damage equal to 120% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::FileRecovery,
        CardRarity::Rare,
        "File Recovery",
        "A deleted file suddenly returns as if nothing happened.",
        "Recover 20 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::FocusBurst,
        CardRarity::Rare,
        "Focus Burst",
        "Everything suddenly makes sense for a short moment.",
        "While held, gain 20 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::ServerConnect,
        CardRarity::Rare,
        "Server Connected",
        "The connection is finally established and your mind stabilizes.",
        "Recover 10 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::ServerExplosion,
        CardRarity::Rare,
        "Server Explosion",
        "Someone pushed broken code. Everything explodes.",
        "Deal damage equal to 80% of your attack to all enemies.",
        CardType::Active,
        TargetType::AllEnemies
    ));

    addCard(new Card(
        CardID::KeyboardMash,
        CardRarity::Rare,
        "Keyboard Mash",
        "You lose patience and smash every key at once.",
        "Deal damage equal to 35% of your attack three times to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::CodeRampage,
        CardRarity::Rare,
        "Code Rampage",
        "Hardcoded chaos erupts and crushes the target.",
        "Deal damage equal to 200% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::Emergency,
        CardRarity::Epic,
        "Emergency",
        "Only thirty minutes remain before the deadline.",
        "While held, gain 30 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::AssignmentCurse,
        CardRarity::Epic,
        "Curse of Assignments",
        "An unbearable amount of homework curses the whole field.",
        "Deal damage equal to 100% of your attack to all enemies.",
        CardType::Active,
        TargetType::AllEnemies
    ));

    addCard(new Card(
        CardID::OverNightTranscendence,
        CardRarity::Epic,
        "Overnight Transcendence",
        "Staying up all night pushes you beyond normal limits.",
        "Deal random damage from 1 to 999 to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));

    addCard(new Card(
        CardID::RescueTouch,
        CardRarity::Epic,
        "Helping Hand",
        "A merciful hand reaches out and saves you.",
        "Recover 50 HP.",
        CardType::Active,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::CodeFusion,
        CardRarity::Epic,
        "Code Fusion",
        "Multiple fragments merge into one impossible masterpiece.",
        "While held, gain 50 attack.",
        CardType::Passive,
        TargetType::Self
    ));

    addCard(new Card(
        CardID::CpuFullPower,
        CardRarity::Epic,
        "CPU Full Power",
        "The processor overheats as every calculation is forced through at once.",
        "Deal damage equal to 230% of your attack to one enemy.",
        CardType::Active,
        TargetType::SingleEnemy
    ));
}

void CardDatabase::addCard(Card* card)
{
    cardList.push_back(card);
}

Card* CardDatabase::getCardByID(CardID id) const
{
    for (Card* card : cardList)
    {
        if (card->getID() == id)
        {
            return card;
        }
    }

    return nullptr;
}

Card* CardDatabase::getCardByIndex(int index) const
{
    if (index < 0 || index >= static_cast<int>(cardList.size()))
    {
        return nullptr;
    }

    return cardList[index];
}

int CardDatabase::getCardCount() const
{
    return static_cast<int>(cardList.size());
}

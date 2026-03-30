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
    KeyboardSmash,
    DoubleClickBug,
    SuddenBathroom,
    MonitorOff,
    ChairPush,
    CtrlZLife,
    SuddenWorkingCode,
    HitTheComputer,
    SuddenSleepiness,
    MemeAttack,
    CaffeineOverdose,
    CtrlSObsessive,
    BlankMaster,
    LaptopFanTurboMode,
    TruthRoom,
    InternetDisconnected,
    DeleteWholeCode,
    TeamProjectPainBuff,
    Reboot,
    ShakeWifi,
    DebugHell,
    FileRecovery,
    FocusBurst,
    ServerConnect,
    ServerExplosion,
    KeyboardMash,
    CodeRampage,
    Emergency,
    AssignmentCurse,
    OverNightTranscendence,
    RescueTouch,
    CodeFusion,
    CpuFullPower,

    // Compatibility aliases for old code
    Strike = KeyboardSmash,
    Heal = CtrlZLife,
    DefenseBoost = SuddenBathroom,
    AttackBoost = CaffeineOverdose,
    DoubleHit = DoubleClickBug,
    MemoryShield = ChairPush,
    Regeneration = CtrlSObsessive,
    Whirlwind = LaptopFanTurboMode
};

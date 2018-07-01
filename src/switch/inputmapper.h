#pragma once

#include <vector>

#include "config.h"

enum class MappableKey {
    Left,
    Up,
    Right,
    Down,
    A,
    B,
    Select,
    Start,
    L,
    R,

    AutoFire,

    EmuFastForward,
    EmuScreenshot,
    EmuPause,

    MenuUp,
    MenuDown,
    MenuAccept,
    MenuBack,
    MenuExit,

    Count
};

class InputMapper : public Serialiseable {
public:
    InputMapper();

    void update(uint64_t keysHeld);

    uint32_t readJoypad();

    void io(Config& cfg) override;

    inline bool keyHeld(MappableKey key)
    {
        return keysHeld_ & keys_[int(key)];
    }
    inline bool keyDown(MappableKey key)
    {
        return keysDown_ & keys_[int(key)];
    }
    inline bool keysUp(MappableKey key)
    {
        return keysUp_ & keys_[int(key)];
    }

    inline void assignKey(MappableKey target, uint64_t key)
    {
        keys_[int(target)] = key;
    }

private:
    std::vector<uint64_t> keys_;

    uint64_t keysHeld_ = 0, keysUp_ = 0, keysDown_ = 0;

    bool autoFire_ = false;
};

extern const char* MappableKeyNames[];
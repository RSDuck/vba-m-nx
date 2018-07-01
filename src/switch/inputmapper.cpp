#include "inputmapper.h"

#include <switch.h>

const char* MappableKeyNames[int(MappableKey::Count)] = {
    "Left",
    "Up",
    "Right",
    "Down",
    "A",
    "B",
    "Select",
    "Start",
    "L",
    "R",

    "Auto Fire",

    "Fast Forward",
    "Screenshot",
    "Pause",

    "Menu Up",
    "Menu Down",
    "Menu Accept",
    "Menu Back",
    "Menu Exit"
};

InputMapper::InputMapper()
{
    keys_.resize(int(MappableKey::Count));
}

void InputMapper::update(uint64_t keysHeld)
{
    keysDown_ = (keysHeld_ ^ keysHeld) & keysHeld;
    keysUp_ = (keysHeld_ ^ keysHeld) & keysHeld_;
    keysHeld_ = keysHeld;
}

#define BIT(n) (1 << (n))

uint32_t InputMapper::readJoypad()
{
    uint32_t result = 0;
    if (keyHeld(MappableKey::A))
        result |= BIT(0);
    if (keyHeld(MappableKey::B))
        result |= BIT(1);
    if (keyHeld(MappableKey::Select))
        result |= BIT(2);
    if (keyHeld(MappableKey::Start))
        result |= BIT(3);
    if (keyHeld(MappableKey::Right))
        result |= BIT(4);
    if (keyHeld(MappableKey::Left))
        result |= BIT(5);
    if (keyHeld(MappableKey::Up))
        result |= BIT(6);
    if (keyHeld(MappableKey::Down))
        result |= BIT(7);
    if (keyHeld(MappableKey::R))
        result |= BIT(8);
    if (keyHeld(MappableKey::L))
        result |= BIT(9);

    // disallow L+R or U+D of being pressed at the same time
    if ((result & 48) == 48)
        result &= ~16;
    if ((result & 192) == 192)
        result &= ~128;

    if (keyHeld(MappableKey::EmuFastForward))
        result |= BIT(10);
    if (keyHeld(MappableKey::EmuScreenshot))
        result |= BIT(11);

    if (autoFire_ && keyHeld(MappableKey::AutoFire)) {
        result &= ~(BIT(0) | BIT(1));
    }
    autoFire_ ^= true;

    return result;
}

static_assert(sizeof(long) >= 8, "int has to be atleast 64-Bit wide to load and store Switch inputs");

void InputMapper::io(Config& cfg)
{
    const int defaultMappings[] = {
        // Left, Up, Right, Down
        KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN,
        // A, B
        KEY_A, KEY_B,
        // Select, Start
        KEY_MINUS, KEY_PLUS,
        // L, R
        KEY_L, KEY_R,
        // Auto Fire
        KEY_Y,

        // Fast Forward, Screenshot, Pause
        KEY_ZR, KEY_ZL, KEY_X,

        // Menu Up, Menu Down, Accept, Back, Exit
        KEY_UP, KEY_DOWN, KEY_A, KEY_B, KEY_X
    };
    for (int i = 0; i < int(MappableKey::Count); i++) {
        keys_[i] = cfg.io("Key Mappings", MappableKeyNames[i], defaultMappings[i]);
        printf("Mapped %s to %d\n", MappableKeyNames[i], keys_[i]);
    }
}
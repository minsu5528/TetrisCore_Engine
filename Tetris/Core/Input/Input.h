#pragma once
#include <windows.h>

enum class KeyCode {
    Left,
    Right,
    Down,
    Space,
    Up,
    None
};

class Input {
public:
    static KeyCode GetKeyDown();
};
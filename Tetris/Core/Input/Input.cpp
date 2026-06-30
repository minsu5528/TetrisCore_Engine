#include "Core/Input/Input.h"

KeyCode Input::GetKeyDown() {
    static bool prevSpace = false;
    static bool prevUp = false;

    bool currSpace = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    bool currUp = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;

    // 1. prev를 갱신하기 전에, "막 눌렸는지" 여부를 먼저 판정해서 변수에 저장
    bool spaceJustPressed = currSpace && !prevSpace;
    bool upJustPressed = currUp && !prevUp;

    // 2. 분기와 무관하게 매 프레임 무조건 상태 갱신 (이게 핵심 수정)
    prevSpace = currSpace;
    prevUp = currUp;

    // 3. 판정 결과에 따라 반환
    if (spaceJustPressed) return KeyCode::Space;
    if (upJustPressed)    return KeyCode::Up;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)   return KeyCode::Left;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)  return KeyCode::Right;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)   return KeyCode::Down;

    return KeyCode::None;
}
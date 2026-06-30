#include "Core/Input/Input.h"

KeyCode Input::GetKeyDown() {
    // static 변수는 함수가 끝나도 값이 날아가지 않고 계속 기억돼! (이전 프레임의 상태 저장용)
    static bool prevSpace = false;
    static bool prevUp = false;

    // 1. 현재 프레임에서 스페이스바와 위쪽 화살표가 눌려있는지 확인
    bool currSpace = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    bool currUp = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;

    // 2. 단발성 입력 체크 (이전엔 안 눌렸는데, 지금 눌렸을 때만 발동!)
    if (currSpace && !prevSpace) {
        prevSpace = currSpace;
        return KeyCode::Space;
    }
    if (currUp && !prevUp) {
        prevUp = currUp;
        return KeyCode::Up;
    }

    // 3. 상태 업데이트 (다음 프레임을 위해 현재 상태를 기억)
    prevSpace = currSpace;
    prevUp = currUp;

    // 4. 좌우 이동과 아래로 내리기는 꾹 누르고 있으면 연속으로 작동해야 하니까 그대로 둠!
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)   return KeyCode::Left;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)  return KeyCode::Right;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)   return KeyCode::Down;

    return KeyCode::None;
}
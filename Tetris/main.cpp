#include <iostream>
#include <windows.h> // Sleep 함수 사용을 위해 필요
#include "Core/Time/Timer.h"

int main() {
    // 1. 게임 루프 시작 전에 타이머 생성 (이때 QPC 초기 시간과 주파수가 세팅됨)
    Timer timer;

    // 블록이 떨어지기까지 흘러간 시간을 계속 모아둘 '누적기' 변수
    float dropTimer = 0.0f;

    std::cout << "=== 실시간 테트리스 엔진 시작 ===\n";

    // 2. 무한 루프 (이것이 바로 게임 엔진의 심장!)
    while (true) {
        // [1단계] 시간 갱신
        timer.Tick();
        float deltaTime = timer.GetDeltaTime();

        // [2단계] 시간 누적 및 로직 업데이트
        dropTimer += deltaTime; // 프레임마다 아주 미세한 시간(예: 0.016초)을 계속 더함

        // 누적된 시간이 1.0초(1000ms)를 넘어가면 블록 낙하 이벤트 발생!
        if (dropTimer >= 1.0f) {
            std::cout << "틱! 1초가 지나서 블록이 한 칸 떨어집니다.\n";

            // 이벤트가 터졌으니 누적기를 다시 0으로 초기화해서 다음 1초를 잼
            dropTimer -= 1.0f;
        }

        // [3단계] 렌더링 (지금은 콘솔 출력으로 대체)
        // ...

        // CPU가 100% 혹사당하는 걸 막기 위해 매 프레임마다 아주 잠깐(1ms) 휴식
        Sleep(1);
    }

    return 0;
}
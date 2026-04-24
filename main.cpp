#include "Core/Memory/ObjectPool.h"
#include <iostream>

// 테스트용 테트리스 블록 더미 구조체
struct Tetromino {
    int x, y;
    int type;
};

int main() {
    std::cout << "=== [Week 2] Object Pool Test ===\n\n";

    // 극한의 테스트를 위해 용량이 3개뿐인 금고를 생성
    ObjectPool<Tetromino, 3> pool;

    std::cout << "[초기 상태] 남은 방 개수: " << pool.GetAvailableCount() << "\n\n";

    // 1. 정상 할당 테스트
    std::cout << "--- 1. 객체 3개 할당 ---\n";
    Tetromino* t1 = pool.Allocate();
    Tetromino* t2 = pool.Allocate();
    Tetromino* t3 = pool.Allocate();
    std::cout << "남은 방 개수: " << pool.GetAvailableCount() << "\n\n";

    // 2. 한계 초과 테스트 (방어 코드 검증)
    std::cout << "--- 2. 용량 초과 할당 시도 (4번째 블록) ---\n";
    Tetromino* t4 = pool.Allocate();
    if (t4 == nullptr) {
        std::cout << "-> 성공: 예상대로 nullptr이 반환되었습니다.\n\n";
    }

    // 3. 반납 및 m_top 변화 테스트
    std::cout << "--- 3. 2번째 블록(t2) 반납 ---\n";
    pool.Free(t2);
    std::cout << "현재 m_top 위치: " << pool.GetTopIndex() << "\n";
    std::cout << "남은 방 개수: " << pool.GetAvailableCount() << "\n\n";

    // 4. 재사용성(Reuse) 검증 (O(1) 속도의 마법)
    std::cout << "--- 4. 새로운 블록 할당 (빈 자리 즉시 재사용 검증) ---\n";
    Tetromino* t5 = pool.Allocate();
    std::cout << "기존 t2 주소: " << t2 << "\n";
    std::cout << "신규 t5 주소: " << t5 << "\n";
    if (t2 == t5) {
        std::cout << "-> 성공: 탐색 없이 반납된 방이 즉시 재사용되었습니다!\n\n";
    }

    // 5. 비정상 반납 방어 테스트
    std::cout << "--- 5. 비정상(nullptr) 반납 시도 ---\n";
    pool.Free(nullptr);

    return 0;
}
#include <iostream>
#include "Core/Logic/Board.h"
#include "Core/Logic/Tetromino.h"

// 플레이어의 회전 입력을 처리하는 가상 시뮬레이션 함수
void HandleInput_Rotate(Tetromino& currentBlock, const Board& gameBoard) {
    Vector2 tempTiles[4];
    currentBlock.GetRotatedTiles(tempTiles); // 1. 원본을 보존한 채 회전 시뮬레이션

    // 2. 가상 회전된 좌표가 맵에서 유효한지(벽/블록 충돌) 검사
    if (gameBoard.IsValidPosition(currentBlock.GetWorldPos(), tempTiles)) {
        currentBlock.CommitRotation(tempTiles); // 3. 통과 시에만 원본에 확정
        std::cout << "-> [성공] 회전이 안전하게 적용되었습니다.\n";
    }
    else {
        std::cout << "-> [실패] 충돌이 감지되어 회전이 취소되었습니다.\n";
    }
}

int main() {
    std::cout << "=== [Week 4] Tetromino Rotation & Collision Test ===\n\n";

    Board board;
    Tetromino tBlock(TetrominoType::T); // T자 블록 생성

    // [테스트 1] 정상 회전 (맵 중앙)
    std::cout << "--- Test 1: 맵 중앙(빈 공간)에서 회전 ---\n";
    tBlock.SetWorldPos(Vector2(5, 10)); // 중앙으로 이동
    HandleInput_Rotate(tBlock, board);  // 성공해야 정상
    std::cout << "\n";

    // [테스트 2] 벽 충돌 방어 (맵 오른쪽 끝)
    std::cout << "--- Test 2: 맵 오른쪽 끝(벽)에서 회전 ---\n";
    tBlock.SetWorldPos(Vector2(9, 10)); // 오른쪽 끝으로 이동
    // T블록이 x=9에서 회전하면 x=10으로 타일이 튀어나가므로 막혀야 함
    HandleInput_Rotate(tBlock, board);  // 실패해야 정상
    std::cout << "\n";

    // [테스트 3] O자 블록 예외 처리 확인
    std::cout << "--- Test 3: O자 블록 회전 시도 ---\n";
    Tetromino oBlock(TetrominoType::O);
    oBlock.SetWorldPos(Vector2(5, 10));
    HandleInput_Rotate(oBlock, board);  // O자 블록은 예외처리로 안전하게 성공해야 함
    std::cout << "\n";

    return 0;
}
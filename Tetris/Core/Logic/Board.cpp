#include "Board.h"
#include <cstring> // memset을 사용하기 위한 헤더

// 1. 올바른 생성자 구현 (클래스명::클래스명)
Board::Board() {
    memset(m_board, 0, sizeof(m_board));
}

// 2. 올바른 멤버 함수 구현 (반환형 클래스명::함수명)
bool Board::IsValidPosition(const Vector2& worldPos, const Vector2 localTiles[4]) const {
    for (int i = 0; i < 4; ++i) {
        // 1. 맵 상의 절대 좌표 계산
        Vector2 absPos = worldPos + localTiles[i];
        int x = absPos.GetRoundedX();
        int y = absPos.GetRoundedY();

        // 2. 맵의 범위를 벗어났는지 확인 (벽, 바닥 충돌)
        if (x < 0 || x >= 10 || y >= 20) {
            return false;
        }

        // [예외 처리] 블록이 맵 위쪽(y < 0)에서 생성되어 떨어지는 중일 때는 배열 검사 스킵
        if (y < 0) {
            continue;
        }

        // 3. 다른 블록과 겹치는지 확인
        if (m_board[y][x] != 0) {
            return false;
        }
    }

    return true;
}
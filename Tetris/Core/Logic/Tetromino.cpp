#include "Tetromino.h"
#include <algorithm> // std::copy 사용을 위한 헤더

// 익명 네임스페이스: 이 파일 안에서만 접근 가능한 전역 데이터
namespace {
    // 7가지 블록 모양에 대한 로컬 좌표 룩업 테이블 (Look-up Table)
    const Vector2 INITIAL_SHAPES[7][4] = {
        /* I (0) */ { Vector2(0,0), Vector2(-1,0), Vector2(1,0), Vector2(2,0) },
        /* J (1) */ { Vector2(0,0), Vector2(-1,0), Vector2(1,0), Vector2(-1,-1) },
        /* L (2) */ { Vector2(0,0), Vector2(-1,0), Vector2(1,0), Vector2(1,-1) },
        /* O (3) */ { Vector2(0,0), Vector2(1,0), Vector2(0,1), Vector2(1,1) },
        /* S (4) */ { Vector2(0,0), Vector2(-1,0), Vector2(0,-1), Vector2(1,-1) },
        /* T (5) */ { Vector2(0,0), Vector2(-1,0), Vector2(1,0), Vector2(0,-1) },
        /* Z (6) */ { Vector2(0,0), Vector2(1,0), Vector2(0,-1), Vector2(-1,-1) }
    };
}

Tetromino::Tetromino(TetrominoType type)
    : m_type(type), m_worldPos(Vector2(5, 0)) // 기본 생성 위치는 맵 상단 중앙 (x=5, y=0)
{
    // enum 값을 정수 인덱스로 변환하여 테이블에서 해당 블록의 좌표를 복사 (O(1) 속도)
    int index = static_cast<int>(m_type);
    std::copy(std::begin(INITIAL_SHAPES[index]), std::end(INITIAL_SHAPES[index]), m_localTiles);
}

void Tetromino::GetRotatedTiles(Vector2 outTiles[4]) const {
    // 예외 처리: O자 블록(네모)은 회전해도 모양이 같으므로 연산 생략
    if (m_type == TetrominoType::O) {
        for (int i = 0; i < 4; ++i) {
            outTiles[i] = m_localTiles[i];
        }
        return;
    }

    // 나머지 블록: 90도 회전 행렬 생성 (라디안 단위)
    Matrix2x2 rotMat;
    const float PI = 3.141592f;
    rotMat.SetRotation(PI / 2.0f);

    // 각 로컬 타일에 행렬을 곱하여 회전된 위치 계산
    for (int i = 0; i < 4; ++i) {
        outTiles[i] = rotMat.Multiply(m_localTiles[i]);
    }
}

void Tetromino::CommitRotation(const Vector2 newTiles[4]) {
    // 안전 검사가 끝난 새로운 좌표를 원본 타일에 덮어쓰기
    for (int i = 0; i < 4; ++i) {
        m_localTiles[i] = newTiles[i];
    }
}
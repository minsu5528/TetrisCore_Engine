#pragma once
#include "../Math/Vector2.h"
#include "../Math/Matrix2x2.h"

// 블록의 7가지 형태 (정수 인덱스로 활용하기 위해 0부터 명시)
enum class TetrominoType { I = 0, J, L, O, S, T, Z };

class Tetromino {
private:
    TetrominoType m_type;     // 블록의 종류
    Vector2 m_worldPos;       // 맵 상의 절대 좌표 (블록의 중심 위치)
    Vector2 m_localTiles[4];  // 중심축 기준 4개 타일의 상대 좌표

public:
    // 생성자: 타입에 맞는 초기 좌표 세팅
    Tetromino(TetrominoType type);

    // [Getter & Setter] 절대 좌표 관리
    Vector2 GetWorldPos() const { return m_worldPos; }
    void SetWorldPos(const Vector2& pos) { m_worldPos = pos; }

    // [회전 시뮬레이션] 원본은 건드리지 않고 회전된 결과만 outTiles에 채워줌
    void GetRotatedTiles(Vector2 outTiles[4]) const;

    // [회전 확정] 충돌 검사를 통과했을 때, 새로운 타일 좌표를 원본에 덮어씀
    void CommitRotation(const Vector2 newTiles[4]);
};
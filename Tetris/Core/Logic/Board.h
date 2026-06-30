#pragma once
#include "../Math/Vector2.h"

class Board {
private:
    // 20x10 테트리스 게임 판 
    // 0: 빈칸, 1~7: 각 블록의 타입(색상) 번호
    int m_board[20][10];

public:
    Board();

    int GetValue(int x, int y) const;
    int ClearLines();
    void SetValue(int x, int y, int value);
    // 특정 위치(worldPos)에 블록(localTiles)이 배치될 수 있는지 충돌 검사
    bool IsValidPosition(const Vector2& worldPos, const Vector2 localTiles[4]) const;
};
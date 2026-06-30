#pragma once
#include <windows.h>

class Renderer {
private:
    HANDLE m_hConsole[2]; // 이중 버퍼링용 콘솔 핸들 배열
    int m_currentBuffer;  // 현재 활성화된 버퍼 인덱스 (0 or 1)

public:
    Renderer();
    ~Renderer();

    void Clear();  // 백 버퍼 초기화
    void Render(); // 프론트/백 버퍼 스왑

    void SetCursorPosition(int x, int y);
    void DrawTextAt(int x, int y, const char* text);
};
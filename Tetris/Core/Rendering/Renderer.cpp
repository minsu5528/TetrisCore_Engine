#include "Core/Rendering/Renderer.h"
#include <iostream>
#include <cstring>   // strlen 사용을 위해 추가

Renderer::Renderer() : m_currentBuffer(0) {
    // 콘솔 화면 버퍼 2개 생성
    m_hConsole[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    m_hConsole[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 콘솔 커서 숨김 처리
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(m_hConsole[0], &cursorInfo);
    SetConsoleCursorInfo(m_hConsole[1], &cursorInfo);

    SetConsoleActiveScreenBuffer(m_hConsole[0]);
}

Renderer::~Renderer() {
    CloseHandle(m_hConsole[0]);
    CloseHandle(m_hConsole[1]);
}

void Renderer::Clear() {
    int backBuffer = 1 - m_currentBuffer;
    COORD startPos = { 0, 0 };
    DWORD charsWritten;
    // 백 버퍼를 공백으로 채워 초기화
    FillConsoleOutputCharacter(m_hConsole[backBuffer], ' ', 80 * 25, startPos, &charsWritten);
}

void Renderer::Render() {
    m_currentBuffer = 1 - m_currentBuffer;
    SetConsoleActiveScreenBuffer(m_hConsole[m_currentBuffer]);
}

void Renderer::SetCursorPosition(int x, int y) {
    COORD pos;
    pos.X = x * 2; // 전각 문자 출력을 위한 X 좌표 보정
    pos.Y = y;
    SetConsoleCursorPosition(m_hConsole[1 - m_currentBuffer], pos);
}

void Renderer::DrawTextAt(int x, int y, const char* text) {
    SetCursorPosition(x, y);
    DWORD charsWritten;
    WriteConsoleA(m_hConsole[1 - m_currentBuffer], text, strlen(text), &charsWritten, NULL);
}
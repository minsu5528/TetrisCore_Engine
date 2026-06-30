#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Core/Time/Timer.h"
#include "Core/Input/Input.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Logic/Board.h"
#include "Core/Logic/Tetromino.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Timer timer;
    Renderer renderer;
    Board gameBoard;

    Tetromino currentBlock(static_cast<TetrominoType>(rand() % 7));
    currentBlock.SetWorldPos(Vector2(4, 0));

    float dropTimer = 0.0f;
    float inputDelay = 0.0f;

    // 화면 출력을 전체적으로 띄워줄 오프셋(여백) 변수
    const int offsetX = 2;
    const int offsetY = 1;

    bool isGameOver = false;

    while (!isGameOver) {
        timer.Tick();
        float dt = timer.GetDeltaTime();
        dropTimer += dt;
        inputDelay += dt;

        // [입력 처리]
        if (inputDelay > 0.08f) {
            KeyCode key = Input::GetKeyDown();
            if (key != KeyCode::None) {
                Vector2 currentPos = currentBlock.GetWorldPos();
                Vector2 tiles[4];
                currentBlock.GetLocalTiles(tiles);

                if (key == KeyCode::Left) {
                    Vector2 nextPos(currentPos.GetRoundedX() - 1, currentPos.GetRoundedY());
                    if (gameBoard.IsValidPosition(nextPos, tiles)) {
                        currentBlock.SetWorldPos(nextPos);
                    }
                }
                else if (key == KeyCode::Right) {
                    Vector2 nextPos(currentPos.GetRoundedX() + 1, currentPos.GetRoundedY());
                    if (gameBoard.IsValidPosition(nextPos, tiles)) {
                        currentBlock.SetWorldPos(nextPos);
                    }
                }
                else if (key == KeyCode::Down) {
                    dropTimer = 1.0f;
                }
                else if (key == KeyCode::Up) {
                    Vector2 rotatedTemp[4];
                    currentBlock.GetRotatedTiles(rotatedTemp);
                    if (gameBoard.IsValidPosition(currentPos, rotatedTemp)) {
                        currentBlock.CommitRotation(rotatedTemp);
                    }
                }
                else if (key == KeyCode::Space) {
                    Vector2 hardDropPos = currentPos;
                    while (true) {
                        Vector2 nextPos(hardDropPos.GetRoundedX(), hardDropPos.GetRoundedY() + 1);
                        if (gameBoard.IsValidPosition(nextPos, tiles)) {
                            hardDropPos = nextPos;
                        }
                        else {
                            break;
                        }
                    }
                    currentBlock.SetWorldPos(hardDropPos);
                    dropTimer = 1.0f;
                }
                inputDelay = 0.0f;
            }
        }

        // [로직 업데이트]
        if (dropTimer >= 1.0f) {
            Vector2 currentPos = currentBlock.GetWorldPos();
            Vector2 nextPos(currentPos.GetRoundedX(), currentPos.GetRoundedY() + 1);
            Vector2 tiles[4];
            currentBlock.GetLocalTiles(tiles);

            if (gameBoard.IsValidPosition(nextPos, tiles)) {
                currentBlock.SetWorldPos(nextPos);
            }
            else {
                for (int i = 0; i < 4; ++i) {
                    int bx = currentPos.GetRoundedX() + tiles[i].GetRoundedX();
                    int by = currentPos.GetRoundedY() + tiles[i].GetRoundedY();
                    gameBoard.SetValue(bx, by, 1);
                }

                gameBoard.ClearLines();

                // 새 블록 생성
                currentBlock = Tetromino(static_cast<TetrominoType>(rand() % 7));
                currentBlock.SetWorldPos(Vector2(4, 0));

                // === [게임 오버 체크] 새 블록이 나오자마자 부딪힌다면? ===
                Vector2 newTiles[4];
                currentBlock.GetLocalTiles(newTiles);
                if (!gameBoard.IsValidPosition(Vector2(4, 0), newTiles)) {
                    isGameOver = true; // 메인 루프 탈출!
                }
            }
            dropTimer -= 1.0f;
        }

        // [렌더링]
        renderer.Clear();

        // 1. 맵 테두리 (벽) 그리기
        for (int y = 0; y < 20; ++y) {
            renderer.DrawTextAt(offsetX - 1, offsetY + y, "▩"); // 왼쪽 벽
            renderer.DrawTextAt(offsetX + 10, offsetY + y, "▩"); // 오른쪽 벽
        }
        for (int x = -1; x <= 10; ++x) {
            renderer.DrawTextAt(offsetX + x, offsetY + 20, "▩"); // 바닥 벽
        }

        // 2. 보드 내부 블록 그리기
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (gameBoard.GetValue(x, y) == 1) {
                    renderer.DrawTextAt(offsetX + x, offsetY + y, "■");
                }
                else {
                    renderer.DrawTextAt(offsetX + x, offsetY + y, "  ");
                }
            }
        }

        // 3. 현재 떨어지고 있는 활성화 블록 그리기
        Vector2 pos = currentBlock.GetWorldPos();
        Vector2 tiles[4];
        currentBlock.GetLocalTiles(tiles);
        for (int i = 0; i < 4; ++i) {
            int drawX = pos.GetRoundedX() + tiles[i].GetRoundedX();
            int drawY = pos.GetRoundedY() + tiles[i].GetRoundedY();
            renderer.DrawTextAt(offsetX + drawX, offsetY + drawY, "▣");
        }

        // 4. UI 렌더링
        renderer.DrawTextAt(offsetX + 14, offsetY + 1, "=== C++ TETRIS ===");
        renderer.DrawTextAt(offsetX + 14, offsetY + 3, "[ CONTROLS ]");
        renderer.DrawTextAt(offsetX + 14, offsetY + 5, "Left/Right : Move");
        renderer.DrawTextAt(offsetX + 14, offsetY + 6, "Down       : Soft Drop");
        renderer.DrawTextAt(offsetX + 14, offsetY + 7, "Up         : Rotate");
        renderer.DrawTextAt(offsetX + 14, offsetY + 8, "Space      : Hard Drop");

        renderer.Render();
        Sleep(1);
    }

    // === 게임 오버 연출 ===
    renderer.Clear();
    renderer.DrawTextAt(5, 10, "===========================");
    renderer.DrawTextAt(5, 12, "      G A M E   O V E R    ");
    renderer.DrawTextAt(5, 14, "===========================");
    renderer.Render();

    Sleep(3000); // 3초 대기 후 프로그램 종료

    return 0;
}
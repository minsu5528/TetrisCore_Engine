# TetrisCore : C++ Micro Game Engine Core

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Windows API](https://img.shields.io/badge/Windows%20API-0078D6?style=for-the-badge&logo=windows&logoColor=white)

> **"단순한 테트리스 클론이 아닌, 게임 엔진의 핵심(메모리, 공간, 시간, 렌더링)을 바닥부터 통제하는 C++ 마이크로 엔진 프로젝트입니다."**

## 프로젝트 개요
상용 게임 엔진(Unity, Unreal)에 의존하지 않고, C++과 Windows API만을 사용하여 게임이 동작하는 가장 밑바닥의 원리를 이해하기 위해 시작된 6주간의 마일스톤 프로젝트입니다. 
테트리스라는 친숙한 룰을 매개체로 삼아 **객체 풀링(Object Pooling), 선형대수(Matrix) 기반 회전, 고해상도 타이머(QPC), 이중 버퍼링(Double Buffering)** 등 렌더링 엔진으로 넘어가기 위한 필수 기초 체력을 구현했습니다.

* **개발 기간:** 2026.04 ~ 2026.05 (6주)
* **개발 언어:** C++ (Standard)
* **환경/라이브러리:** Windows API (콘솔 렌더링 및 비동기 입력 제어)

---

## 개발 회고록 (Tech Blog)
개발 과정에서의 아키텍처 설계 의도(Insight)와 트러블슈팅(Trouble) 과정은 아래 기술 블로그 시리즈에 상세히 기록되어 있습니다.

**[Velog 기술 블로그: C++ 마이크로 엔진 코어 구축기 (총 6편)](https://velog.io/@roql/series/C-%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9C-%EC%97%94%EC%A7%84-%EC%BD%94%EC%96%B4-%EA%B5%AC%EC%B6%95%EA%B8%B0)**

---

## 코어 아키텍처 및 구현 기능

### 1. Memory (설계 및 단위 검증, 게임 빌드 미통합)
* **커스텀 메모리 추적기:** `new`/`delete` 연산자를 오버로딩하여 할당/해제를 추적하는 모듈(`MemoryTracker.h`)을 독립적으로 설계하고 단위 테스트로 검증함. 현재 게임 빌드(main.cpp)에는 통합되어 있지 않음.
* **객체 풀링 (Object Pool):** O(1) 할당/반납이 가능한 `ObjectPool<T>` 템플릿(`ObjectPool.h`)을 설계하고 단위 테스트로 검증함. `Tetromino`가 기본 생성자를 갖지 않아 현재 구조로는 직접 적용이 불가능했고, 게임 루프에도 통합하지 않음. 이 한계를 인지하고 있으며, 다음 프로젝트인 MSEngine에서 `placement new` 기반으로 재설계하여 통합할 예정.

### 2. Space & Math (공간과 수학)
* **Vector2 / Matrix2x2 클래스 구현:** 하드코딩된 좌표 이동이 아닌, 2D 벡터와 2x2 회전 변환 행렬을 이용한 수학적 블록 회전 로직 구현.
* **Simulate & Commit 패턴:** 회전 연산 후 가상 타일(Virtual Tiles)로 충돌 검사를 먼저 수행하고, 안전할 때만 상태를 갱신.

### 3. Time (시간 제어와 프레임 독립성)
* **QPC 고해상도 타이머:** `<chrono>` 대신 Windows 하드웨어 수준의 정밀도를 가진 `QueryPerformanceCounter`를 사용하여 `DeltaTime` 측정.
* **시간 누적기 (Accumulator):** 기기 성능(FPS)에 의존하지 않고 정확히 현실 시간(1초)에 맞춰 블록이 낙하하도록 프레임 독립적(Frame-Independent) 게임 루프 설계.

### 4. Rendering & Input (출력과 입력)
* **이중 버퍼링 (Double Buffering):** 콘솔 `HANDLE` 버퍼 2장을 활용하여 프론트/백 버퍼 스왑(Swap) 파이프라인 구축. 화면 지우기(cls)로 인한 화면 깜빡임(Flickering) 완벽 제거.
* **비동기 키보드 제어:** `GetAsyncKeyState`를 활용하여 메인 루프를 블로킹하지 않는 실시간 키 입력 구현.
* **Just Pressed 상태 관리:** 스페이스바(하드 드랍) 입력 시 이전 프레임 상태를 기억하여, 다중 입력(연타) 버그를 방지하는 단발성 입력 상태 머신 구현.

---

## Next Step : 3D 렌더링 엔진 (MSEngine)
이 `TetrisCore` 프로젝트를 통해 확보한 메모리, 시간, 공간 통제력을 바탕으로, 다음 프로젝트인 **DirectX 11 기반 자체 3D 렌더링 엔진(`MSEngine`)** 개발로 이어집니다. 본 프로젝트의 메모리 추적기와 수학 코어(Vector/Matrix)는 MSEngine의 기반 모듈로 흡수될 예정입니다.
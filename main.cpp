#include "Core/Memory/MemoryTracker.h"

int main() {
    // 1. 정상 할당 및 해제 테스트
    int* p = new int(10);
    delete p;

    new int[100];

    // 2. 의도적 누수 테스트 (주석 해제하며 확인)
    //double* d = new double[10]; 

    g_metrics.PrintReport();
    return 0;
}
#include <stdio.h>
#include <time.h> // clock_gettime() 함수를 위해 필요
#include <stdint.h> // uint64_t를 위해 필요 (선택 사항이지만 안전)

int main() {
    long long a = 1;
    long long b = 1;
    long long c = 0;

    struct timespec start_ts, end_ts; // 시간을 저장할 구조체

    // CLOCK_MONOTONIC: 시스템 부팅 이후 경과된 시간을 측정 (시스템 시간 변경에 영향받지 않음)
    // CLOCK_REALTIME: 실제 시간 (시스템 시간 변경에 영향받음)
    clock_gettime(CLOCK_MONOTONIC, &start_ts); // 시작 시간 기록

    for (int i = 0; i < 90; i++) {
        // 이 부분에서 long long 오버플로우 발생 가능성 있습니다.
        // 90번째 피보나치 수는 약 2.88 x 10^18 이고, long long 최대는 9.22 x 10^18 이므로
        // 간신히 담기거나, 루프 반복 횟수를 늘리면 바로 오버플로우 됩니다.
        c = a + b;
        a = b;
        b = c;
    }

    clock_gettime(CLOCK_MONOTONIC, &end_ts); // 종료 시간 기록

    // 나노초 단위로 총 경과 시간 계산
    uint64_t elapsed_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1000000000ULL +
                          (end_ts.tv_nsec - start_ts.tv_nsec);

    // 나노초를 마이크로초로 변환
    double elapsed_us = (double)elapsed_ns / 1000.0;

    printf("계산된 피보나치 값 (오버플로우 발생 가능): %lld\n", c);
    printf("경과 시간: %.3f 마이크로초 (%.6f 초)\n", elapsed_us, elapsed_us / 1000000.0);

    return 0;
}
// 0.383µs
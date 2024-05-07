#include <stdio.h>
#include <stdbool.h>

// 프로세스 구조체 정의
typedef struct {
    int pid;        // 프로세스 ID
    int burstTime;  // 버스트 시간
    int remainingTime; // 남은 실행 시간
} Process;

// Round Robin 스케줄링 함수
void roundRobin(Process processes[], int count, int timeQuantum) {
    int time = 0; // 시간 초기화
    bool done;

    // 초기에 남은 실행 시간 설정
    for (int i = 0; i < count; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    // 모든 프로세스가 완료될 때까지 반복
    do {
        done = true;

        for (int i = 0; i < count; i++) {
            if (processes[i].remainingTime > 0) {
                done = false; // 아직 끝나지 않은 프로세스가 있음

                if (processes[i].remainingTime > timeQuantum) {
                    // 실행 시간이 타임 퀀텀보다 긴 경우
                    time += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                    printf("프로세스 %d가 %d 시간 동안 실행됨.\n", processes[i].pid, timeQuantum);
                } else {
                    // 남은 시간이 타임 퀀텀보다 작거나 같은 경우
                    time += processes[i].remainingTime;
                    printf("프로세스 %d가 %d 시간 동안 실행됨.\n", processes[i].pid, processes[i].remainingTime);
                    processes[i].remainingTime = 0; // 프로세스 완료
                }
            }
        }
    } while (!done);
}

int rr() {
    int n, timeQuantum;

    printf("프로세스 수를 입력하세요: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("프로세스 %d의 버스트 타임을 입력하세요: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
    }

    printf("타임 퀀텀을 입력하세요: ");
    scanf("%d", &timeQuantum);

    roundRobin(processes, n, timeQuantum);
    return 0;
}

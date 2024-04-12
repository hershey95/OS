#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For shared memory
#include <unistd.h>   // For ftruncate
#include <sys/stat.h> // For mode constants

int prov() {
    const int SIZE = 4096;             // 공유 메모리 객체의 크기
    const char *name = "OS";           // 공유 메모리 객체의 이름
    char message[SIZE];                // 입력 받을 메시지

    int shm_fd;     // 공유 메모리 파일 디스크립터
    char *ptr;      // 공유 메모리 객체를 가리키는 포인터

    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // 현재 프로세스(부모 프로세스)의 PID 얻기
    pid_t parent_pid = getpid();

    // 메시지 입력 받기
    while(1) {
        printf("메시지를 입력하세요 (PID %d, 종료: end): ", parent_pid);
        fflush(stdout); // 화면에 바로 출력되도록 버퍼를 비움
        fgets(message, SIZE, stdin); // 표준 입력에서 메시지를 받음

        if (strncmp(message, "end", 3) == 0) {
            break; // "end" 입력 시 루프 종료
        }

        // 공유 메모리 객체에 데이터 쓰기
        sprintf(ptr, "%s", message);
        ptr += strlen(message);
    }

    return 0;
}


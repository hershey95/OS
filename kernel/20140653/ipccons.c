#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For shared memory
#include <unistd.h>   // For ftruncate
#include <sys/stat.h> // For mode constants
#include <string.h>   // For strcmp

int cons() {
    const int SIZE = 4096;     // 공유 메모리 객체의 크기
    const char *name = "OS";   // 공유 메모리 객체의 이름
    pid_t child_pid = getpid();

    int shm_fd;                // 공유 메모리 파일 디스크립터
    char *ptr;                 // 공유 메모리 객체를 가리키는 포인터

    // 공유 메모리 객체 열기
    shm_fd = shm_open(name, O_RDONLY, 0666);

    // 공유 메모리 객체를 메모리에 매핑
    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // 공유 메모리 객체에서 데이터 읽기
    if (strcmp(ptr, "") == 0) {
        printf("(PID %d)메시지가 없습니다. 종료합니다.\n", child_pid);
    } else {
        printf("(PID %d)수신된 메시지: %s\n", child_pid, ptr);
    }

    // 공유 메모리 객체 제거
    shm_unlink(name);

    return 0;
}


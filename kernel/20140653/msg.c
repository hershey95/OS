#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // fork(), getpid()
#include <msg.h>


int msg() {
    pid_t pid = fork();

    if (pid == -1) {
        // fork 실패
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // 자식 프로세스
        prov(); // ipcprod.c의 기능을 실행
    } else if (pid > 0) { // 부모 프로세스
        wait(NULL);  // 자식 프로세스의 종료를 기다림
        cons(); // ipccons.c의 기능을 실행
    }
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For getpid() and fork()
#include <readline/readline.h>
#include <readline/history.h>

#include "basic_include.h"
#include "fork.h"
#include "msg.h"
#include "pi.h"

void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;
    pid_t original_pid = getpid();  // Get the original (parent) process ID

    while(getpid() == original_pid) {  // Only continue in the parent process
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");

        if (strcmp(input,"exit") == 0) {
            break;
        }
        if (strcmp(input,"minisystem") == 0){
            minisystem();
        }
        else if (strcmp(input,"20140653") == 0){
            student_id();
        }
        else if (strcmp(input,"fork") == 0){
            myFork();
        }
        else if (strcmp(input,"msg") == 0){
            msg();
        }
        else if (strcmp(input,"pi") == 0){
            pi();
        }
        else if (strcmp(input,"rr") == 0){
            rr();
        }
        else {
            system(input);
        }
    }

    // 메모리 해제
    if (input) free(input);
    if (getpid() == original_pid) {
        print_minios("[MiniOS SSU] MiniOS Shutdown........");
    }

    return 1;
}

void print_minios(char* str) {
    printf("%s\n", str);
}

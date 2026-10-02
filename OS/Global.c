#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int globalvar = 6;

void printGlobalVar() {
    int count = 0;
    int sleep_time = 50;
    while(count < 3) {
        usleep(sleep_time);
        printf("PID: %d, Global Variable: %d\n",
            getpid(), globalvar);
        count++;
    }
}

int main(int argc, char *argv[]) {

    pid_t pid = fork();
        
    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        // Child process        
        globalvar = 8;
        printGlobalVar();
        exit(0);
    } else {
        printGlobalVar();
        exit(0);
    }    
    return 0;
}

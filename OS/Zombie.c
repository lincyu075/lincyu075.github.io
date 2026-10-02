#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    
    printf("Parent process started (PID: %d)\n", getpid());
    
    // Create a child process
    child_pid = fork();
    
    if (child_pid < 0) {
        // Error occurred
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process
        printf("Child process started (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        
        exit(EXIT_SUCCESS);

    } else {
        // Parent process
        printf("Parent created child with PID: %d\n", child_pid);        
        while(1) {}
        exit(EXIT_SUCCESS);
    }   
    return 0; // This should never be reached
}

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
    } 
    else if (child_pid == 0) {
        // Child process
        printf("Child process started (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        
        // Child creates its own child (grandchild of original process)
        pid_t grandchild_pid = fork();
        
        if (grandchild_pid < 0) {
            perror("Grandchild fork failed");
            exit(EXIT_FAILURE);
        }
        else if (grandchild_pid == 0) {
            // This is the grandchild process
            printf("Grandchild process started (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            
            printf("Grandchild (PID: %d): My parent is (PID: %d)\n", 
                       getpid(), getppid());
                       
            sleep(10);
            if (getppid() == 1) {
                    printf("Grandchild (PID: %d): My parent is (PID: %d)\n", 
                       getpid(), getppid());
            }            
            printf("Grandchild process exiting normally\n");
            exit(EXIT_SUCCESS);
        }
        else {
            // Back in the child process
            printf("Child process created grandchild with PID: %d\n", grandchild_pid);
            
            // Child sleeps for 3 seconds and then exits
            // This will orphan the grandchild if no cascading termination
            printf("Child process will exit in 3 seconds...\n");
            sleep(3);
            printf("Child process exiting now\n");
            exit(EXIT_SUCCESS);
        }
    } 
    else {
        // Parent process
        printf("Parent created child with PID: %d\n", child_pid);        
        // Optional: wait for child to complete first
        int status;
        waitpid(child_pid, &status, 0);
        printf("Parent: Child process has exited\n");
        
        printf("Parent process exiting now\n");
        exit(EXIT_SUCCESS);
    }
    
    return 0; // This should never be reached
}

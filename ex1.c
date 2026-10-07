#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    int n = 4;
    pid_t pid = fork();

    if (pid < 0){ exit(EXIT_FAILURE);}

    if (pid == 0)
    {
        printf("Hello from CHILD  [PID - %d - &n = %p]\n", getpid(), (void*)&n);
        exit(EXIT_SUCCESS);
    } else{
        printf("Hello from PARENT [PID - %d - &n = %p]\n", getpid(), (void*)&n);
        exit(EXIT_FAILURE);
    }
}

// After fork(), two processes are parent and child. 
// The child is a copy of the parent, but they are not the same processes and have different PIDs.

// Max PID = 32768
// Which process has no parents like root (/) directory in case of files? - init. It's PPID = 0.

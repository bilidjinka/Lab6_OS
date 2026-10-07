#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

double elapsed_ms(clock_t start) {return (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;}

int main(void) {
    clock_t start_main = clock();
    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
        clock_t start_child1 = clock(); 
        printf("Child 1: PID=%d  PPID=%d\n", getpid(), getppid());
        printf("Child 1: Execution time = %.3f ms\n", elapsed_ms(start_child1));
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        clock_t start_child2 = clock();
        printf("Child 2: PID=%d  PPID=%d\n", getpid(), getppid());
        printf("Child 2: Execution time = %.3f ms\n", elapsed_ms(start_child2));
        exit(EXIT_SUCCESS);
    }
    
    wait(NULL);
    wait(NULL);

    printf("Parent: PID=%d  PPID=%d\n", getpid(), getppid());
    printf("Parent: Execution time = %.3f ms\n", elapsed_ms(start_main));
    printf("Child 1 PID=%d, Child 2 PID=%d\n", pid1, pid2);

    return 0;
}

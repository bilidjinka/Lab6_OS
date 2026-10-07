#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n < 0)
    {
        fprintf(stderr, "n must be >= 0\n");
        return EXIT_FAILURE;
    }

    printf("Program started. PID=%d, PPID=%d, n=%d\n", getpid(), getppid(), n);
    fflush(stdout);

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        printf("[iter %d] fork() -> pid=%d, my PID=%d, my PPID=%d\n", i + 1, pid, getpid(), getppid());
        fflush(stdout);
        sleep(5);
    }

    sleep(30);
    return 0;
}

// 8 processes were created
// After fork() both the parent and the child execute the loop.
// On every iteration, every existing process calls fork() once, doubling counter of processes.

// Going from n=3 to n=5 doubles the count of processes two times (2*2=4).
// Number of processes doubles at each iteration, so the the formula is 2^n.

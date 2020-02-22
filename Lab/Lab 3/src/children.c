#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t child1, child2;
    int status;

    child1 = fork();
    if (child1 < 0)
    {
        printf("[Error] Forking child process");
        return 1;
    }
    else if (child1 == 0)
    { // Child1
        printf("I am child 1, my pid is %d\n", getpid());
    }
    else
    { // Parent
        child2 = fork();
        if (child2 < 0)
        {
            printf("[Error] Forking child process\n");
            return 1;
        }
        else if (child2 == 0)
        {
            printf("I am child 2, my pid is %d\n", getpid());
        }
        else
        {
            pid_t w = waitpid(child1, &status);
            pid_t q = waitpid(child1, &status);
            wait(NULL);
            printf("[PARENT] My child 1 is %d\n", getpid());
            printf("[PARENT] My child 2 is %d\n", getpid());
        }
    }

    return 0;
}
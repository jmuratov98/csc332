#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t p1, p2; // processes
    int fd;       // file descriptor
    int mypipe[2];
    char buff[1024];
    ssize_t numb_read = -1;

    printf("Main program executed\n");

    if (pipe(mypipe) == -1)
    {
        fprintf(stderr, "Failed to create a pipe\n");
        return 1;
    }

    printf("Successfully created the pipes\n");

    p1 = fork(); // Creating a fork
    // Child one failed to fork
    if (p1 < 0)
    {
        fprintf(stderr, "Failed to fork the first child\n");
        return 1;
    }
    // Child one succeded to be forked from child.
    else if (p1 == 0)
    {
        printf("[CHILD 1] I am working\n");

        // Close reading end of this childs pipe
        if (close(mypipe[0]) == -1)
        {
            fprintf(stderr, "[CHILD 1]Error closing reading end of the pipe\n");
            return 1;
        }

        dup2(mypipe[1], 1);
        execlp("ls", "ls", "-F", NULL);

        if (close(mypipe[1]) == -1)
        {
            fprintf(stderr, "[CHILD 1] Error closing writing end of the pipe\n");
            return 1;
        }

        printf("[CHILD 1] I am done\n");
    }
    // Time to work on the second fork
    else
    {
        p2 = fork(); // Create child process 2
        // Fork failed
        if (p2 < 0)
        {
            fprintf(stderr, "Failed to fork the second child\n");
            return 1;
        }
        // Child process 2
        else if (p2 == 0)
        {
            // Child Two working
            printf("[CHILD 2] I am working\n");

            if(close(mypipe[1]) == -1) {
                fprintf(stderr, "[CHILD 2] Error closing writing end of the pipe\n");
                return 1;
            }

            dup2(mypipe[0], 0);
            execlp("nl", "nl", NULL);

            if(close(mypipe[0]) == -1) {
                fprintf(stderr, "[CHILD 2] Error closing reading end of the pipe\n");
                return 1;
            }

            printf("[CHILD 2] I am done\n");
        }
        // Parent process
        else
        {
            if (close(mypipe[0]) == -1)
            {
                printf("[PARENT] Error closing reading end of the pipe.\n");
                exit(EXIT_FAILURE);
            }

            if (close(mypipe[1]) == -1)
            {
                printf("[PARENT] Error closing writing end of the pipe.\n");
                exit(EXIT_FAILURE);
            }

            printf("[PARENT] Waiting for children completion...\n");
            
            if (wait(NULL) == -1)
            {
                printf("Error waiting.\n");
                exit(EXIT_FAILURE);
            }

            if (wait(NULL) == -1)
            {
                printf("Error waiting.\n");
                exit(EXIT_FAILURE);
            }

            // A GOOD PARENT WAITS UNTIL THE CHILD DIES (this is dark :( )
            printf("Parent killed children and is now depressed\n");
        }

        printf("[PARENT] I am Done\n");
    }

    printf("Good bye cruel world\n");
    return 0;
}
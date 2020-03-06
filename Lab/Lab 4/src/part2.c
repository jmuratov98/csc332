#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid;
    
    pid = fork();

    if(pid < 0) {
        perror("Could not fork child");
        return 1;
    } else if(pid == 0) {
        printf("[CHILD] I am working my pid is %d\n", getpid());
        execvp("ls", &argv[0]);
    } else {
        wait(NULL);
    }

    return 0;
}
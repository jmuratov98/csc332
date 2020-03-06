#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    pid_t child1, child2;

    child1 = fork();
    if(child1 < 0) {
        printf("[ERROR] Forking child");
        return 1;
    } else if(child1 == 0) { // Child 1
        execvp("bin/p1", argv);
    } else { // Parent
        child2 = fork();
        if(child2 < 0) {
            printf("[ERROR] Forking child");
            return 1;
        } else if(child2 == 0) { // Child 1
            execvp("./bin/p2", argv);
        } else { // Parent
            wait(NULL);
            wait(NULL);
        }
    }
}
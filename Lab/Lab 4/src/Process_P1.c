#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd1, fd2;

    fd1 = creat(argv[1], 00777);
    fd2 = creat(argv[2], 00777);

    return 0;
}
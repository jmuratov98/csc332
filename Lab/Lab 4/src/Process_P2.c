#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    const char* filepath_source = argv[3], *filepath_dest1 = argv[1], *filepath_dest2 = argv[2];
    
    int source, dest1, dest2;
    char* buffer;

    source = open(filepath_source, O_RDONLY);
    if(source < 1) {
        perror("Cannot open file :(");
        return 1;
    } else {
        struct stat st;
        int size = stat(filepath_source, &st);
        buffer = malloc(st.st_size);

        // Open both files
        int dest1 = open(filepath_dest1, O_WRONLY);
        if(dest1 < 0) {
            perror("Cannot open file :(");
            return 1;        
        }

        int dest2 = open(filepath_dest2, O_WRONLY);
        if(dest2 < 0) {
            perror("Cannot open file :(");
            return 1;        
        }

        // Reads from source file and puts it to buffer
        int i = 0;
        int count = 0;
        while(read(source, buffer, 50)) {
            if(i % 2 == 0) {
                // Write the next hundred bytes
                lseek(source, count, SEEK_CUR);
                write(dest1, buffer, 100);
                count += 100;
            } else {
                // Write the next fifty bytes
                lseek(source, count, SEEK_CUR);
                write(dest2, buffer, 50);
                count += 50;
            }
            i++;
        }

        close(dest1);
        close(dest2);

        free(buffer);
    }

    close(source);

    return 0;
}
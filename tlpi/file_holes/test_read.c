#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*
    TEST
    read pre 10 bytes from a file and print the number of byte
*/

int main(int argc, char *argv[]){
    char *filepath;
    int fd;
    char buf[10];
    ssize_t numRead;

    if (argc < 2) {
        printf("Usage: read_file_holes filepath\n");
        exit(3);
    }

    filepath = argv[1];
    fd = open(filepath, O_RDONLY );

    if (fd == -1) {
        printf("ERROR open() failed\n");
        exit(2);
    }

    /* read previous 10 bytes */
    while ((numRead = read(fd, buf, 10)) > 0) {
        int i;
        for(i = 0; i < numRead; i++) {
            unsigned char ch;
            ch = (unsigned char) buf[i];
            printf("buf[%d]=%d\n", i, ch);
        }
        break;
    }

    if (lseek(fd, -10, SEEK_END) == -1) {
        printf("ERROR lseek() failed\n");
        exit(8);
    }

    /* read last 10 bytes */
    while ((numRead = read(fd, buf, 10)) > 0) {
        int i;
        for(i = 0; i < numRead; i++) {
            unsigned char ch;
            ch = (unsigned char) buf[i];
            printf("buf[%d]=%d\n", i, ch);
        }
        break;
    }

    if (close(fd) == -1) {
        printf("ERROR close() failed\n");
        exit(7);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

/*
    TEST
    create a file with holes, which size is 100MB.
*/


int main(int argc, char *argv[]){
    char *filepath;
    int fd;
    mode_t filePerms;


    if (argc < 2) {
        printf("Usage: create_file_holes filepath\n");
        exit(3);
    }

    filepath = argv[1];

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP ;
    fd = open(filepath, O_WRONLY | O_CREAT, filePerms);

    if (fd == -1) {
        printf("ERROR open() failed:file create failed\n");
        exit(2);
    }

    if (write(fd, "0", sizeof("0")) != sizeof("0")) {
        printf("ERROR write() failed\n");
        exit(4);
    }

    if (lseek(fd, 100 * 1024 * 1024, SEEK_END) == -1) {
       printf("ERROR lseek() failed\n");
        exit(5);
    }

    /* 字符串常量结尾带\0 */
    if (write(fd, "0", sizeof("0")) != sizeof("0")) {
        printf("ERROR write() failed\n");
        exit(6);
    }

    if (close(fd) == -1) {
        printf("ERROR close() failed\n");
        exit(7);
    }

    return 0;
}
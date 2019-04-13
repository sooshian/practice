#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

/*
    practice for tlpi chapter 4
    my own implement of tee
*/

int main(int argc, char *argv[]) {
    int opt, afnd;
    char *filepath;
    int inputFd, outputFd, f_outputFd;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    afnd = 0;

    while ((opt = getopt(argc, argv, ":a")) != -1) {
        switch (opt) {
            case 'a':
                afnd = 1;
                break;
            case '?':
            default: 
                printf("Usage: mytee [option] output_file\n");
                exit(-1);
        }
    }
    if (optind < argc) filepath = argv[optind];
    else {
        printf("ERROR missing output file !\n");
        exit(-1);
    }

    /* open file for output */
    if (afnd) {
        f_outputFd = open(filepath, O_WRONLY | O_APPEND);
    } else {
        f_outputFd = open(filepath, O_WRONLY);
    }

    if (f_outputFd == -1) {
        if (errno == ENOENT) {
            /* files not existed */
            filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP ;
            f_outputFd = open(filepath, O_WRONLY | O_CREAT, filePerms);
        } else {
            printf("ERROR open() failed, errno = %d\n", errno);
            exit(-1);
        }
    }
    
    if (f_outputFd == -1) {
        /* file create failed */
        printf("ERROR open() failed, errno = %d\n", errno);
        exit(-1);
    }

    /* open stdin/stdout */
    inputFd = STDIN_FILENO;
    outputFd = STDOUT_FILENO;

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            printf("ERROR write() failed, errno = %d\n", errno);
            exit(-1);
        }
        if (write(f_outputFd, buf, numRead) != numRead) {
            printf("ERROR write() failed, errno = %d\n", errno);
            exit(-1);
        }
    }
    if (numRead == -1) {
        printf("ERROR read() failed, errno = %d\n", errno);
        exit(-1);
    }

    if (close(f_outputFd) == -1) {
        printf("ERROR close() failed, errno = %d\n", errno);
        exit(-1);
    }

    return 0;
}
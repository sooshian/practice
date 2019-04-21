#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    char *srcFilePath;
    char *dstFilePath;
    int inFd, outFd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    int bytes_count = 0;
    int final_hole = 0;

    if (argc < 3) {
        printf("Usage:mycp srcFile dstFile\n");
        exit(1);
    }

    srcFilePath = argv[1];
    dstFilePath = argv[2];

    inFd = open(srcFilePath, O_RDONLY);
    if (inFd == -1) {
        printf("ERROR open() failed\n");
        exit(2);
    }

    outFd = open(dstFilePath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (outFd == -1) {
        printf("ERROR open() failed\n");
        exit(3);
    }


    while((numRead = read(inFd, buf, BUF_SIZE)) > 0) {
        int i;
        int pre_ch_same_type_start = 0;
        int pre_ch_is_hole = (buf[0] == '\0' ? 1 : 0 );
        for(i = 1; i < numRead; i++) {
            int cur_ch_is_hole = (buf[i] == '\0' ? 1 : 0 );
            if (pre_ch_is_hole == cur_ch_is_hole) {
                continue;
            } else {
                /* continuous holes or non-holes end, need to write */
                if (pre_ch_is_hole) {
                    int length = i - pre_ch_same_type_start;
                    if (lseek(outFd, length, SEEK_CUR) == -1) {
                        printf("ERROR lseek() failed\n");
                        exit(5);
                    }
                    bytes_count += length;
                } else {
                    char * sub_buf = buf + pre_ch_same_type_start;
                    int length = i - pre_ch_same_type_start;
                    if (write(outFd, sub_buf, length) != length) {
                        printf("ERROR write() failed\n");
                        exit(4);
                    }
                    bytes_count += length;
                }
                /* reset variables */
                pre_ch_same_type_start = i;
                pre_ch_is_hole = cur_ch_is_hole;
            }
        }
        
        /* continuous holes or non-holes end, need to write */
        if (pre_ch_is_hole) {
            int length = i - pre_ch_same_type_start;
            if (lseek(outFd, length, SEEK_CUR) == -1) {
                printf("ERROR lseek() failed\n");
                exit(5);
            }
            bytes_count += length;
        } else {
            char * sub_buf = buf + pre_ch_same_type_start;
            int length = i - pre_ch_same_type_start;
            if (write(outFd, sub_buf, length) != length) {
                printf("ERROR write() failed\n");
                exit(4);
            }
            bytes_count += length;
        }

        final_hole = pre_ch_is_hole;
    }

    /* for final hole */
    if (final_hole) {
        if (lseek(outFd, -1, SEEK_CUR) == -1) {
            printf("ERROR lseek() failed\n");
            exit(11);
        } 
        if (write(outFd, "\0", 1) != 1) {
            printf("ERROR write() failed\n");
            exit(12);
        }
    }

    if (close(inFd) == -1) {
        printf("ERROR close() failed\n");
        exit(6);
    }

    if (close(outFd) == -1) {
        printf("ERROR close() failed\n");
        exit(7);
    }
    printf("%d copied \n", bytes_count);
    return 0;
}
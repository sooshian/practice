#!/bin/bash
make create
make cp

./test_create test
./mycp test test1

ls -l test test1
du test test1
md5sum test test1

hexdump -c test
hexdump -c test1

## spare file, which contains a large of holes

4.9 section in tlpi show:
> Using lseek(), we can explicitly reposition the file offset to any location within the file or past the end of the file. Writing data at a position beyond the previous end of the file creates a hole in the file. Reads from a file hole return bytes containing zeros.

my code have those executable:

```bash
./test_create # create a spare file
./test_read # show first 10 bytes and last 10 bytes of a file
./mycp # copy a spare file and remain same holes in new file
```


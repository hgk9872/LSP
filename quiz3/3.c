#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[])
{
    char buf[BUFFER_SIZE];
    int fd1, fd2;
    ssize_t size;
    
    if ((fd1 = open(argv[1], O_RDONLY, 0644)) < 0){
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    if ((fd2 = creat(argv[2], 0644)) < 0){
        fprintf(stderr, "open error for %s\n", argv[2]);
        exit(1);
    }

    if ((size = read(fd1, buf, BUFFER_SIZE)) < 0){
        printf("read error");
        exit(1);
    }

    if (write(fd2, buf, size) < 0){
        printf("write error"); 
        exit(1);
    }

    close(fd1);
    close(fd2);
}

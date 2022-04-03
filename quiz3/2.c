#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define WORD_MAX 100 // 최대 문장 수

int main(void)
{
    int fd;
    int length = 0, offset = 0, count = 0;
    char character;
    char *fname = "ssu_test.txt";
    char buf[WORD_MAX][BUFFER_SIZE];
    int i;

    if ((fd = open(fname, O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s.\n", fname);
        exit(1);
    }

    
    while(1){
        if (read(fd, &character, 1) > 0){
            length++;
            if (character == '\n'){
                length--;
                lseek(fd, offset, SEEK_SET);
                read(fd, buf[count], BUFFER_SIZE);
                i = length;
                offset = offset + i + 1;
                lseek(fd, offset, SEEK_SET);
                count++;
                length = 0;
            }
        }
        else break;
    }
    close(fd);

    // 한 문장씩 출력
    for(i = 0; i < count; i++)
        printf("%s\n", buf[i]);

    // 문장 수 출력
    printf("line number : %d\n", count);
    exit(0);
}

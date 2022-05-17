#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "american_maid" // named ���������� fifo

int main(void)
{
	char s[300];
	int num, fd;

	//mknod(FIFO_NAME, S_IFIFO | 0666, 0);
	mkfifo(FIFO_NAME, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH); // 0666 ���� fifo ����
	printf("waiting for readers... \n");
	fd = open(FIFO_NAME, O_WRONLY); // fifo ����
	printf("got a reader--type some stuff\n");
	while (gets(s), !feof(stdin)) { // ǥ���Է����� eof�� ���������� ���ڿ� �Է¹���
		if ((num = write(fd, s, strlen(s))) == -1) // ���ۿ� ����������fd write
			perror("write");
		else
			printf("speak: wrote %d bytes \n", num);
	}
	exit(0);
}

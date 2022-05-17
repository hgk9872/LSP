#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	int pid;
	int pipe_fd[2]; // ���������� �迭

	if (pipe(pipe_fd) < 0) { // ���������� ����
		fprintf(stderr, "fork error\n");
		exit(1);
	}

	if ((pid = fork()) < 0) { // ����ó��
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0) { // �ڽ����μ���
		close(pipe_fd[0]); // ���������� read fd ����
		while(1) {
			memset(buf, 0x00, BUFFER_SIZE); // ���� �ʱ�ȭ
			sprintf(buf, "Hello Mother Process. My name is %d\n", getpid()); // �ڽ� ���μ��� pid ���۷� ���
			write(pipe_fd[1], buf, strlen(buf)); // write ���������� ��ũ���Ϳ� ���� write
			sleep(1);
		}
	}
	else { // �θ� ���μ���
		close(pipe_fd[1]); // ���������� write fd ����
		while(1) {
			memset(buf, 0x00, BUFFER_SIZE); // ���� �ʱ�ȭ
			read(pipe_fd[0], buf, BUFFER_SIZE); // ���������� read fd���� read�ؼ� ���ۿ� ����
			fprintf(stderr, "%s", buf); // ���
		}
	}

	exit(0);
}

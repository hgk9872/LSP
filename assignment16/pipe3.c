#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	int pid;
	int pipe_fd[2]; // 파이프파일 배열

	if (pipe(pipe_fd) < 0) { // 파이프파일 생성
		fprintf(stderr, "fork error\n");
		exit(1);
	}

	if ((pid = fork()) < 0) { // 에러처리
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0) { // 자식프로세스
		close(pipe_fd[0]); // 파이프파일 read fd 닫음
		while(1) {
			memset(buf, 0x00, BUFFER_SIZE); // 버퍼 초기화
			sprintf(buf, "Hello Mother Process. My name is %d\n", getpid()); // 자식 프로세스 pid 버퍼로 출력
			write(pipe_fd[1], buf, strlen(buf)); // write 파이프파일 디스크립터에 버퍼 write
			sleep(1);
		}
	}
	else { // 부모 프로세스
		close(pipe_fd[1]); // 파이프파일 write fd 닫음
		while(1) {
			memset(buf, 0x00, BUFFER_SIZE); // 버퍼 초기화
			read(pipe_fd[0], buf, BUFFER_SIZE); // 파이프파일 read fd에서 read해서 버퍼에 저장
			fprintf(stderr, "%s", buf); // 출력
		}
	}

	exit(0);
}

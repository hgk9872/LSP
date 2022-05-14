#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

int ssu_daemon_init(void);
int main(void)
{
	pid_t pid;

	pid = getpid(); // daemon 실행 전 부모 프로세스 pid
	printf("parent process: %d\n", pid);
	printf("daemon process initialization\n");

	if (ssu_daemon_init() < 0) { // 디몬 실행 및 에러 처리
		fprintf(stderr, "ssu_daemon_init failed\n");
		exit(1);
	}
	exit(0);
}

int ssu_daemon_init(void) {
	pid_t pid;
	int fd, maxfd;

	if ((pid = fork()) < 0) { // 자식 프로세스의 PPID는 부모프로세스의 PID가 됨
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid != 0) // 부모 프로세스
		exit(0); // 부모 프로세스를 죽이고, 자식 프로세스(고아)의 PPID는 init 프로세스(PID=1)가 된다

	pid = getpid(); // 디몬 프로세스 pid
	printf("process %d running at daemon\n", pid);
	setsid(); // 새 세션을 생성하고, 세션의 리더, 프로세스 리더가 됨, 결국 터미널을 가지지 않는 프로세스가 됨

	// 터미널과 관련된 시그널을 모두 무시함
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	maxfd = getdtablesize(); // 열린 모든 fd의 수
	for (fd = 0; fd < maxfd; fd++) // 오픈된 모든 fd를 닫는다
		close(fd);

	umask(0); // 파일 mask 금지
	chdir("/"); // 현재 프로세스의 working directory를 root로 변경
	
	fd = open("/dev/null", O_RDWR); // 터미널을 없앰
	dup(0);
	dup(0);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

sigjmp_buf jmp_buf1;
sigjmp_buf jmp_buf2;

int main(void)
{
	struct sigaction act_sig1;
	struct sigaction act_sig2;
	int i, ret;

	printf("My PID is %d\n", getpid());
	ret = sigsetjmp(jmp_buf1, 1); // jump될 위치 설정, 리턴 값 ret = 0 설정

	if (ret == 0) {
		act_sig1.sa_handler = ssu_signal_handler1; // handler1 설정
		sigaction(SIGINT, &act_sig1, NULL); // 핸들러 호출
	}
	else if (ret == 3)
		printf("--------------------\n");

	printf("Starting\n");
	sigsetjmp(jmp_buf2, 2); // 두 번째 setjmp 설정
	act_sig2.sa_handler = ssu_signal_handler2; // handler2 설정
	sigaction(SIGUSR1, &act_sig2, NULL); // 핸들러 호출

	for (i = 0; i < 20; i++) {
		printf("i = %d\n", i);
		sleep(1);
	}

	exit(0);
}

static void ssu_signal_handler1(int signo)
{
	fprintf(stderr, "\nInterrupted\n"); // 에러 메세지 출력
	siglongjmp(jmp_buf1, 3); // sigsetjmp로 jump후, 3 리턴
}

static void ssu_signal_handler2(int signo)
{
	fprintf(stderr, "\nSIGUSR1\n"); // 에러 메세지 출력
	siglongjmp(jmp_buf2, 2); // sigset jump 후, 2 리턴
}

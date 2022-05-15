#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);

jmp_buf jump_buffer;

int main(void)
{
	signal(SIGINT, ssu_signal_handler); // SIGINT 시그널 설정

	while (1) {
		if (setjmp(jump_buffer) == 0) { // sigsetjmp 대신 setjmp사용
			printf("Hit Ctrl-c at anytime ... \n");
			pause();
		}
	}

	exit(0);
}

void ssu_signal_handler(int signo)
{
	char character;

	signal(signo, SIG_IGN); //  SIGINT 시그널 무시
	printf("Did you Ctrl-c?\n" "Do you really want to quit? [y/n]");
	character = getchar();
	if (character == 'y' || character == 'Y')
		exit(0);
	else {
		signal(SIGINT, ssu_signal_handler); // SIGINT 시그널 핸들러를 다시 설정
		longjmp(jump_buffer, 1); // setjmp로 돌아감
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t old_set;
	sigset_t sig_set;

	sigemptyset(&sig_set); // 새로운 시그널 집합인 sig_set 인자 초기화 
	sigaddset(&sig_set, SIGINT); // SIGINT를 sig_set 인자에 포함
	sigprocmask(SIG_BLOCK, &sig_set, &old_set); // sig_set 인자 블록, 기존 시그널 집합을 old_set 인자에 저장
	sigsuspend(&old_set); // old_set 인자에 있는 시그널들이 발생할 때까지 프로세스 일시 정지
	exit(0);
}

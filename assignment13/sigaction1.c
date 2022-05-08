#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo) {
    printf("ssu_signal_handler control\n");
}

int main(void) {
    struct sigaction sig_act;
    sigset_t sig_set;

    sigemptyset(&sig_act.sa_mask); // sig_act의 sa_mask 초기화
    sig_act.sa_flags = 0;
    sig_act.sa_handler = ssu_signal_handler;
    sigaction(SIGUSR1, &sig_act, NULL); // SIGUSR1 시그널 발생했을 때 액션정보 전달
    printf("before first kill()\n"); 
    kill(getpid(), SIGUSR1); // kill호출하여 시그널을 발생시킴
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGUSR1); // SIGUSR1 시그널 추가
    sigprocmask(SIG_SETMASK, &sig_set, NULL); // 시그널을 블록
    printf("before second kill()\n");
    kill(getpid(), SIGUSR1); // SIGUSR1 시그널을 발생시켜 블록되었는지 확인
    printf("after second kill()\n");
    exit(0);
}

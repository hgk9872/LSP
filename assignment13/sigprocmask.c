#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    sigset_t sig_set;
    int count;

    sigemptyset(&sig_set); // sig_set 인자 초기화
    sigaddset(&sig_set, SIGINT); // SIGINT signal을 sig_set 인자에 추가
    sigprocmask(SIG_BLOCK, &sig_set, NULL); // SIG_BLOCK를 사용하여 SIGINT 블록시킴

    for (count = 3; 0 < count ; count--) { // count 3초동안 SIGINT 발생 대기
        printf("count %d\n", count);
        sleep(1);
    }

    printf("Ctrl-C에 대한 블록을 해제\n");
    sigprocmask(SIG_UNBLOCK, &sig_set, NULL); // 발생하는 경우 SIGINT 시그널 핸들러 실행
    printf("count 중 Ctrl-C 입력하면 이 문장은 출력되지 않음.\n");

    while (1);

    exit(0);
}

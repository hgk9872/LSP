#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
    sigset_t set;

    sigemptyset(&set);   // 시그널 집합 초기화
    sigaddset(&set, SIGINT); // SIGINT 시그널 추가

    switch (sigismember(&set, SIGINT)) // SIGINT 있는지 검사
    {
        case 1 : // exist
            printf("SIGINT is included.\n");
            break;
        case 0 : 
            printf("SIGINT is not included.\n");
            break;
        default :
            printf("failed to call sigismember()\n");
    }

    switch (sigismember(&set, SIGSYS)) // SIGSYS 있는지 검사
    {
        case 1 : // exist
            printf("SIGSYS is included.\n");
            break;
        case 0 :
            printf("SIGSYS is not included.\n");
            break;
        default :
            printf("failed to call sigismember()\n");
    }

    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child1, child2;
    int pid, status;

    if ((child1 = fork()) == 0)
        execlp("date", "date", (char *)0);

    if ((child2 = fork()) == 0)
        execlp("who", "who", (char *)0);

    printf("parent: waiting for children\n");

    // 자식 프로세스가 종료될때까지 기다린 후 출력
    while ((pid = wait(&status)) != -1) {
        if (child1 == pid)
            printf("parent: first child: %d\n", (status >> 8));
        else if (child2 == pid)
            printf("parent: second child: %d\n", (status >> 8));
    }

    printf("parent: all children terminated\n");
    exit(0);
}


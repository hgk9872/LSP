#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("this is original program\n");
    execl("./ssu_execl_test_1", "ssu_execl_test_1", "param1", "param2", "param3", (char *)0);
    printf("%s\n", "This line should never get printed\n");
    exit(0);
}


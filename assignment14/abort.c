#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("abort terminate this program\n");
	abort(); // abort를 호출해서 SIGABRT 시그널 발생시킴. 디폴트 액션은 비정상 종료
	printf("this line is never reached\n");
	exit(0);
}

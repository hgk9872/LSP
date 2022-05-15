#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void ssu_timestamp(char *str);

int main(void)
{
	unsigned int ret;

	ssu_timestamp("before sleep()"); // sleep() 호출 전 time stamp
	ret = sleep(10); // 프로세스 일시정지
	ssu_timestamp("after sleep()");
	printf("sleep() returned %d\n", ret); // sleep() 호출 후 time stamp
	exit(0);
}

// time stamp 출력 함수
void ssu_timestamp(char *str)
{
	time_t time_val;

	time(&time_val);
	printf("%s the time is %s\n", str, ctime(&time_val));
}

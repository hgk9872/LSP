#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHARED_MEMORY_SIZE 1024

int main(int argc, char *argv[])
{
	key_t key;
	char *data;
	int shared_memory_id;

	if (argc > 2) {
		fprintf(stderr, "usage: %s [data_to_write] \n", argv[0]);
		exit(1);
	}

	if ((key = ftok("ssu_shmdemo.c", 'R')) == -1) { // key 생성
		fprintf(stderr, "ftok error\n");
		exit(1);
	}

	if ((shared_memory_id = shmget(key, SHARED_MEMORY_SIZE, 0644 | IPC_CREAT)) == -1) { // IPC shared memory 생성
		fprintf(stderr, "shmget error\n");
		exit(1);
	}

	if ((data = shmat(shared_memory_id, (void *)0, 0)) == (char*)(-1)) { // shared memory에 데이터 저장
		fprintf(stderr, "shmat error\n");
		exit(1);
	}

	if (argc == 2) {
		printf("writing to segment: \"%s\" \n", argv[1]);
		strncpy(data, argv[1], SHARED_MEMORY_SIZE);
	}
	else
		printf("segment contains: \"%s\" \n", data);

	if (shmdt(data) == -1) { // shared memory에서 데이터 가져옴
		fprintf(stderr, "shmdt error\n");
		exit(1);
	}
	
	exit(0);
}

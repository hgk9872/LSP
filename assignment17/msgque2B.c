#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

struct ssu_msgbuf {
	char msg_text[BUFFER_SIZE];
	long msg_type;
};

int main(void)
{
	struct ssu_msgbuf buf;
	key_t key;
	int msg_queueid;

	if ((key = ftok("msgque1.c", 'B')) == -1) { // key 생성
		fprintf(stderr, "ftok error\n");
		exit(1);
	}

	if ((msg_queueid = msgget(key, 0644 | IPC_CREAT)) == -1) { // 생성한 키를 받아 메세지생성
		fprintf(stderr, "msgget error\n");
		exit(1);
	}

	printf("spock: ready to receive messages, captain.\n");

	while (1) {
		if (msgrcv(msg_queueid, &buf, sizeof(buf.msg_text), 0, 0) == -1) {
			fprintf(stderr, "msgrcv: Identifier removed\n");
			exit(1);
		}

		printf("spock: \"%s\"\n", buf.msg_text);
	}

	exit(0);
}

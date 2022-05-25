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

	printf("Enter lines of text, ^D to quit: \n");
	buf.msg_type = 1;

	while (fgets(buf.msg_text, sizeof(buf.msg_text), stdin) != NULL) {
		int length = strlen(buf.msg_text);

		if (buf.msg_text[length-1] == '\n')
			buf.msg_text[length-1] = '\0';

		if (msgsnd(msg_queueid, &buf, length+1, 0) == -1)
			fprintf(stderr, "msgsnd error");
	}

	if (msgctl(msg_queueid, IPC_RMID, NULL) == -1) { // 메세지 종료
		fprintf(stderr, "msgctl error");
		exit(1);
	}

	exit(0);
}

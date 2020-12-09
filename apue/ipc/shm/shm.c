#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(void)
{
	int shmid;
	pid_t pid;
	void *ptr;
	
	shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == shmid) {
		perror("shmget()");
		exit(1);
	}

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);
		if ((void *)-1 == ptr) {
			perror("shmat()");
			exit(1);
		}
		memcpy(ptr, "good afternoon", 14);
		shmdt(ptr);
		exit(0);
	}
	wait(NULL);
	ptr = shmat(shmid, NULL, 0);
	// if error
	puts(ptr);
	shmdt(ptr);

	shmctl(shmid, IPC_RMID, NULL);

	exit(0);
ERROR:
	shmctl(shmid, IPC_RMID, NULL);
	exit(1);
}


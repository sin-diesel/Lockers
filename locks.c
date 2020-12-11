



#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main (int argc, char** argv) {
	struct flock f1 = {0};
	f1.l_type = F_WRLCK;
	f1.l_whence = SEEK_CUR;
	f1.l_start = 0;
	f1.l_len = 1;
	f1.l_pid = 0;

	struct flock f2 = {0};
	f2.l_type = F_WRLCK;
	f2.l_whence = SEEK_CUR;
	f2.l_start = 2;
	f2.l_len = 2;
	f2.l_pid = 0;

	if (argc < 2) {
		printf("Not enough arguments");
		exit(-1);
	}

	int fd = open(argv[1], O_RDWR);
	if (fd < 1) {
		perror("Unable to open file");
		exit(-1);
	}


	int ret = fcntl(fd, F_SETLK, &f1);
	if (ret < 0) {
		perror("Unable to lock file");
	}

	ret = fcntl(fd, F_SETLK, &f2);
	if (ret < 0) {
		perror("Unable to lock file");
		close(fd);
		exit(-1);
	}

	sleep(1000);
	close(fd);
	return 0;
}









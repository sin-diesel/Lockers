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
	f1.l_type = 0;
	f1.l_whence = SEEK_CUR;
	f1.l_start = 2;
	f1.l_len = 2;
	f1.l_pid = 0;

	if (argc < 2) {
		printf("Not enough arguments");
		exit(-1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 1) {
		perror("Unable to open file");
		exit(-1);
	}

	int ret = 0;

	while (1) {

		ret = fcntl(fd, F_GETLK, &f1);

		if (ret < 0) {
			perror("Unable to get lock from file");
			close(fd);
			exit(-1);
		} else {
			printf("%d - %s, %d - %s, %d - %s\n", F_RDLCK, "F_RDLCK", F_WRLCK, "F_WRLCK", F_UNLCK, "F_UNLCK");
			printf("Read lock successfull\n");
			printf("Lock Type   : %d\n", f1.l_type);
    		printf("Lock pid    : %d\n", f1.l_pid);
    		printf("Lock offset : %ld\n", f1.l_start);;
		}
	}
	return 0;
}
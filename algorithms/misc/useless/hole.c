#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s input offset\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		printf("Error opening file \n");
		exit(EXIT_FAILURE);
	}
	int offset;
	offset = atoi(argv[2]);
	lseek(fd, offset, SEEK_END);
	char ch = '\n';
	write(fd, &ch, 1);
	close(fd);
}


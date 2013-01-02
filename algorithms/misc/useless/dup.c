#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC);
	if (fd == -1) {
		printf("Error opening file \n");
		exit(EXIT_FAILURE);
	}
	int offset;
	int fd1 = dup(fd);

	char buf[1024];
	char sbuf[1024];
	sprintf(sbuf, "Please enter data writing using fd = %d: ", fd);
	write(1, sbuf, strlen(sbuf));
	int cnt = read(0, buf, sizeof(buf)-1) - 1;
	write(fd, buf, cnt); 
	

	sprintf(sbuf, "Please enter data writing using fd = %d: ", fd1);
	write(1, sbuf, strlen(sbuf));
	cnt = read(0, buf, sizeof(buf)-1) - 1;
	write(fd1, buf, cnt); 

	close(fd);
	close(fd1);
}


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE  *fd = fopen(argv[1],"r");
	if (argc != 3) {
		printf("Usage: %s input outputfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if (fd == 0) {
		printf("Error opening file for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE *fd1 = fopen(argv[2], "w");
	if (fd1 == 0) {
		printf("Error opening file for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	int ch;
	while (1) {
		ch = fgetc(fd);
		if (feof(fd))
			break;
		ch = toupper(ch);
		fputc(ch, fd1);
	}
	fclose(fd);
	fclose(fd1);
}


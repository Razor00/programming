#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s input outputfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	FILE  *fd = fopen(argv[1],"r");// O_RDONLY);
	if (fd == 0) {
		printf("Error opening file \n");
		exit(EXIT_FAILURE);
	}

	FILE *fd1 = fopen(argv[2], "w");
	if (fd1 == 0) {
		printf("Error opening file \n");
		exit(EXIT_FAILURE);
	}
	
	int wc = 0;
	int start_word = 0;
	int ch;
	while (1) {
		ch = fgetc(fd);	
		if (feof(fd)) 
			break;
		wc++;
		if (isspace(ch)){
			start_word = 1;
			fputc(ch, fd1);
		}
		else if (start_word  &&  isalpha(ch)) {
			ch = toupper(ch);
			start_word = 0;
		}
		fputc(ch, fd1);
	}
	wc--;
	fclose(fd);
	fclose(fd1);
//	printf("%d\n", wc);
}


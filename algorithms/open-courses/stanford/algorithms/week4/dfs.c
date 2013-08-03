#include <fcntl.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
    int n;
    int fd;
    int  

    fd = fopen(argv[0], O_RDONLY);
    if (fd <  0) {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fd, "%d", &n);
}


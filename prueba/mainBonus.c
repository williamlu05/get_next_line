#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("quijote.txt", O_RDONLY);
	// int fd = 1;
	printf("%s", get_next_line(42));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd2));
	
	// while (1) printf("%s", get_next_line(fd2));
    // close(fd);
    return (0);
}

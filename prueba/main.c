#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    
	int fd = open("test.txt", O_RDONLY);
	// int fd = open("quijote.txt", O_RDONLY);
	// int fd = 1;
	printf("%s", get_next_line(42));
	while (1) printf("%s", get_next_line(fd));
    // close(fd);
    return (0);
}

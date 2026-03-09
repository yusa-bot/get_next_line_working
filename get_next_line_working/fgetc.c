#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	FILE *fd = fopen("test2.txt", O_RDONLY);
	int c = fgetc(fd);
	printf("c: %d\n", c);
	putchar(c);
	return 0;
}

//int
//     fgetc(FILE *stream);

//     int
//     getc(FILE *stream);

//     int
//     getc_unlocked(FILE *stream);

//     int
//     getchar(void);

//     int
//     getchar_unlocked(void);

//     int
//     getw(FILE *stream);

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

// github
ssize_t getdelim(char **buf, size_t *bufsiz, int delimiter, FILE *fp)
{
	char *ptr, *eptr;

	if (*buf == NULL || *bufsiz == 0)
	{
		*bufsiz = BUFSIZ;
		if ((*buf = malloc(*bufsiz)) == NULL)
			return (-1);
	}

	for (ptr = *buf, eptr = *buf + *bufsiz;;)
	{
		int c = fgetc(fp);

		if (c == -1)
		{
			if (feof(fp))
			{
				ssize_t diff = (ssize_t)(ptr - *buf);
				if (diff != 0)
				{
					*ptr = '\0';
					return diff;
				}
			}
			return -1;
		}
		*ptr++ = c;

		if (c == delimiter)
		{
			*ptr = '\0';
			return ptr - *buf;
		}

		if (ptr + 2 >= eptr)
		{
			char *nbuf; // ポインタ
			size_t nbufsiz = *bufsiz * 2; // 作るbufサイズ
			ssize_t d = ptr - *buf; // 進んだ長さ

			if ((nbuf = realloc(*buf, nbufsiz)) == NULL)
				return -1;

			*buf = nbuf;
			*bufsiz = nbufsiz;
			eptr = nbuf + nbufsiz;
			ptr = nbuf + d;
		}
	}
}

ssize_t getline(char **buf, size_t *bufsiz, FILE *fp)
{
	return getdelim(buf, bufsiz, '\n', fp);
}

int main(int argc, char *argv[])
{
	char *p = NULL;
	ssize_t len;
	size_t n = 0;

	int fd = open("test2.txt", O_RDONLY);
	FILE *fp = fdopen(fd, "r");

	while ((len = getline(&p, &n, stdin)) != -1)
		(void)printf("%zd %s", len, p);
	free(p);
	return 0;
}


/////////////////// zenn


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_getc(int fd)
{
	static char buf[BUFSIZ];
	static char *bufp;
	static int n = 0;

	if (n < 0)
		return (1);

	if (n == 0)
	{
		n = read(fd, buf, sizeof buf);
		if (n < 0)
			return (1);
		bufp = buf;
	}

	--n;
	if (n >= 0)
		return (unsigned char)*bufp++;
	else
		return EOF;
}

char *get_next_line(int fd)
{
	while (1)
	{
		int c = ft_getc(fd);
		if (c == "\n")
			break;
		return (c);
	}
}

int main()
{
	int fd = open("test2.txt", O_RDONLY);
	//int fd = 0;

	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
	}
	close(fd);
	return (0);
}

///// tochuu

int main(void)
{
	FILE *fd = fopen("test2.txt", "r");

	int c = fgetc(fd);
	fputc(c, stdout);

	return 0;
}



char *get_next_line(void)
{
	char *result_line;

	int fd = open("test2.txt", O_RDONLY);

	char *buf = malloc(BUFSIZE);
	if (!buf) return (NULL);

	while ()
	{
		int read_bytes = read(fd, buf, BUFSIZE - 1);
		if (read_bytes <= 0 || buf[0] == EOF) return (NULL);

		if (strchr(buf, "\n"))
	}

	return (result_line);
}

int main(void)
{
	char *return_line = get_next_line();
	if (!return_line)
	{
		printf("no more read line. or occur error.")
		return (0);
	}
	printf("return_line: %s", return_line);
	free(return_line);
	return (0);
}
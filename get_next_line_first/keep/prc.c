#include <stdio.h>
#include <stdlib.h>
//notionに貼る

int	main(void)
{
	FILE	*fp;
	int	n, m, l = 0;

	fp = fopen("c.txt", "r");
	if (!fp)
	{
		perror("no file open");
		return 1;
	}

	m = fgetc(fp);
	putchar(m);
	//while ((l = getc(fp)) != EOF)
	//	putchar(l);
	fclose(fp);

	//n = getchar();
	//printf("%d", n);
	return (0);
}

//ssize_t	getline(char ** restrict linep, size_t * restrict linecapp,  FILE * restrict stream)
//{

//}

//int	main()
//{
//	char	*line = NULL;
//	size_t	len = 0;
//	ssize_t	read;

//	printf("Enter some text (Ctrl+D to end):\n");

//	while ((read = getline(&line, &len, stdin)) != -1)
//	{
//		printf("You entered: %s", line);
//        printf("Length: %zd\n", read);
//	}
//	free(line);

//	return 0;
//}

//ssize_t getdelim(char **buf, size_t *bufsiz, int delimiter, FILE *fp)

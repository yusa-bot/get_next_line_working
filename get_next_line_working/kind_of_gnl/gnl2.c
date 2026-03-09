#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_buf
{
	char	data[BUFFER_SIZE];
	ssize_t	len;
	ssize_t	pos;
}	t_buf;

static int	ensure_cap(char **line, size_t *cap, size_t need)
{
	size_t	newcap;
	char	*tmp;

	if (need <= *cap)
		return (1);

	newcap = (*cap == 0) ? 64 : *cap;

	while (newcap < need)
		newcap *= 2;

	tmp = (char *)realloc(*line, newcap);
	if (!tmp)
	{
		free(*line);
		*line = NULL;
		*cap = 0;
		return (0);
	}

	*line = tmp;
	*cap = newcap;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buf	b;
	char			*line;
	size_t			len;
	size_t			cap;
	int				c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	line = NULL;
	len = 0;
	cap = 0;

	while (1)
	{
		if (b.pos >= b.len)
		{
			b.len = read(fd, b.data, BUFFER_SIZE);
			b.pos = 0;

			if (b.len < 0)
			{
				free(line);
				return (NULL);
			}

			if (b.len == 0)
				break ;
		}

		c = (unsigned char)b.data[b.pos++];

		if (!ensure_cap(&line, &cap, len + 1))
			return (NULL);
		
		line[len++] = (char)c;
		if (c == '\n')
			break ;
	}
	if (len == 0)
	{
		free(line);
		return (NULL);
	}
	if (!ensure_cap(&line, &cap, len + 1))
		return (NULL);
	line[len] = '\0';
	return (line);
}

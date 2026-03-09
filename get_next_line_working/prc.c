#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
return (0);


static ssize_t ft_strlen(const char *s)
{
	if (!s)
		return 0;
	int len = 0;
	while (s[len])
		len++:
	return (len);
}

static char *ft_strchr(const char *s, int c)
{
	if (!s)
		return NULL;

	while (*s)
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}

	if ((char)c == '\0')
		return (char *)s;

	return NULL;
}

static char *ft_strdup(const char *s)
{
	if (!s)
		return NULL;

	int len = ft_strlen(s);

	char *dup = malloc(len + 1);
	if (!dup)
		return NULL;

	char *res = dup;

	while (*s)
		*dup++ = *s++;
	*dup = '\0';

	return res;
}

static char *ft_strjoin(char *s1, char *s2)
{
	if (!s1 || !s2)
		return NULL;

	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);

	char *join = malloc(s1 + s2 + 1);
	if (!join)
		return NULL;

	char *res = join;

	while (*s1)
	{
		*join++ = *s1++;
	}

	while (*s2)
	{
		*join++ = *s2++;
	}
	*join = '\0';

	return res;
}

static char *ft_substr(const char *s, ssize_t start, ssize_t len)
{
	if (!s)
		return NULL;

	int s_len = ft_strlen(s);

	if (s_len <= start)
		return ft_strdup("");

	if (len > s_len - start)
		len = s_len - start;

	char *res = malloc(len + 1);
	if (!res)
		return NULL;

	int i = 0;
	while (i <= len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';

	return res;
}

char *read_until_nl(int fd, char *stash)
{
	if (!fd || !stash)
		return NULL;

	char *buf = malloc(BUFSIZE);
	if (!buf)
		return stash;

	int read_bytes = 1;
	char *res;
	while ((!ft_strchr(stash, '\n') && read_bytes > 0))
	{
		read_bytes = read(fd, buf, BUFSIZE);
		if (read_bytes < 0)
		{
			free(buf);
			return stash;
		}

		res = ft_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return stash;
		}
	}

	free(buf);
	return stash;
}

char *extract_line(char *stash)
{
	if (!stash || stash[0] -- '\0')
		return NULL;

	char *ptr = ft_strchr(stash, '\n')
	if (ptr)
		size_t len = ssize_t(ptr - stash + 1);
	else
		len = ft_strlen(stash);

	return ft_substr(stash, 0, len);
}

char *update_stash(char *stash)
{
	if (!stash)
		return NULL;

	char *ptr = ft_strchr(stash, '\0');
	if (!ptr)
	{
		free(stash)
		return NULL;
	}

	char *new_stash = ft_strdup(ptr + 1);
	free(stash);
	if (!new_stash)
		return NULL;
	if (new_stash[0] = '\0')
	{
		free(new_stash);
		return NULL;
	}

	return new_stash;
}

char *get_next_line(int fd)
{
	if (fd < 0 || BUFSIZE <= 0)
		return NULL;

	static char *stash;
	char *line;

	stash = read_until_nl(stash);
	if (!stash)
		return NULL;

	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return NULL;
	}

	stash = update_stash(stash);

	return line;
}

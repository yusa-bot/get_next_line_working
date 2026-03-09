#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);

	len = ft_strlen(s);

	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);

	i = 0;
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strjoin(char *s1, const char *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = (char *)malloc(len1 + len2 + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		dst[len1 + i] = s2[i];
		i++;
	}
	dst[len1 + len2] = '\0';
	return (dst);
}

static char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);

	s_len = ft_strlen(s);

	if (start >= s_len)
		return (ft_strdup(""));

	if (len > s_len - start)
		len = s_len - start;

	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);

	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';

	return (dst);
}

static char	*read_until_nl(int fd, char *stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes;
	char	*tmp;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);

	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			return (NULL);
		}
		buf[bytes] = '\0';

		tmp = ft_strjoin(stash, buf);

		free(stash);

		stash = tmp;
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line(const char *stash)
{
	size_t	len;
	char	*nl;

	if (!stash || stash[0] == '\0')
		return (NULL);

	nl = ft_strchr(stash, '\n');
	if (nl)
		len = (size_t)(nl - stash) + 1;
	else
		len = ft_strlen(stash);

	return (ft_substr(stash, 0, len));
}

static char	*update_stash(char *stash)
{
	char	*nl;
	char	*new_stash;

	if (!stash)
		return (NULL);

	nl = ft_strchr(stash, '\n');
	if (!nl)
	{
		free(stash);
		return (NULL);
	}

	new_stash = ft_strdup(nl + 1);
	free(stash);

	if (!new_stash || new_stash[0] == '\0')
	{
		free(new_stash);
		return (NULL);
	}
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	stash = read_until_nl(fd, stash);
	if (!stash)
		return (NULL);

	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}

	stash = update_stash(stash);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 06:30:37 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/11 04:19:08 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// readで保存先変数が必要なため最初にmalloc(stash)
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	 // stashに改行がまだ無いなら
	while (!has_newline(stash))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		//EOF or error
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		stash = str_join(stash, buf);
	}
	free(buf);
	//stashに改行がある
	line = extract_line(stash);//改行までにする
	stash = update_stash(stash);//改行以降をstashに保存
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buf;
	int		bytes_read;

	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	printf("buf: %s\n", buf);
	if (!buf)
		return (NULL);

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);

	printf("bytes_read: %d\n", bytes_read);
	printf("buf:\n%s\n", buf);
	free(buf);
	return (NULL);
}

int	main(void)
{
	int		fd;
	//char	*line;

	fd = open("c.txt", O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
		return (1);
	}
	printf("fd: %d\n", fd);
	get_next_line(fd);
	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, sizeof(line));
		free(line);
	}
	close(fd);
	return (0);
}

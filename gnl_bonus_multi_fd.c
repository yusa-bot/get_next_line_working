/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:59:50 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/15 01:09:49 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"
//last_str配列をchar *last_strとして受け取っているから、last_strとして扱える。
char	*read_until_nl_in_buf(int fd, char *last_str)
{
	char	*buf;
	int		read_bytes;

	if (!fd || fd < 0)
		return (NULL);
	if (!last_str)
		last_str = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(last_str);//!!
		return (NULL);
	}
	read_bytes = 1;
	while (!ft_strchr(last_str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			free(last_str);
			last_str = NULL;
			return (NULL);
		}
		buf[read_bytes] = '\0';
		last_str = ft_strjoin(last_str, buf);
		if (!last_str)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	if (last_str[0] == '\0')
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	return (last_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*last_str[4096];

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);

	last_str[fd] = read_until_nl_in_buf(fd, last_str[fd]);
	if (!last_str[fd])
		return (NULL);
	line = get_nl_line(last_str[fd]);
	if (!line)
	{
		free(last_str[fd]);
		last_str[fd] = NULL;
		return (NULL);
	}
	last_str[fd] = new_last_str(last_str[fd]);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		fd1 = open("test1.txt", O_RDONLY);
// 	int		fd2 = open("test2.txt", O_RDONLY);
// 	int		fd3 = open("test3.txt", O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0)
// 		return (1);

// 	while (1)
// 	{
// 		char	*line1 = get_next_line(fd1);
// 		char	*line2 = get_next_line(fd2);
// 		char	*line3 = get_next_line(fd3);
// 		if (!line1 && !line2 && !line3)
// 			break ;
// 		if (line1)
// 		{
// 			printf("fd1: %s", line1);
// 			free(line1);
// 		}
// 		if (line2)
// 		{
// 			printf("fd2: %s", line2);
// 			free(line2);
// 		}
// 		if (line3)
// 		{
// 			printf("fd3: %s", line3);
// 			free(line3);
// 		}
// 	}

// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }

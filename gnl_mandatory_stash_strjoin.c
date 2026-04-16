/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:12:03 by ayusa             #+#    #+#             */
/*   Updated: 2026/01/23 20:11:30 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// while not '\n' in buf, read and strjoin
char	*read_until_nl_in_buf(int fd, char *last_str)
{
	char	*buf;
	int		read_bytes;

	if (!fd || fd < 0)
		return (NULL);
	if (!last_str)
		last_str = ft_strdup("");
	//first, buf.
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(last_str);//!!
		return (NULL);
	}
	read_bytes = 1;//first time, while in !
	//last read, read_bytes = 0: EOF
	while (!ft_strchr(last_str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)//read error
		{
			free(buf);
			free(last_str);
			last_str = NULL;
			return (NULL);
		}
		buf[read_bytes] = '\0';
		// last_str exchange malloc
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
	static char	*last_str;

	if (!fd || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	last_str = read_until_nl_in_buf(fd, last_str);//until nl in buf
	//not malloc buf or read error
	if (!last_str)
		return (NULL);
	line = get_nl_line(last_str);//RESULT(until nl str)
	if (!line)
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	last_str = new_last_str(last_str);//after '\n' str
	return (line);
}

 #include <stdio.h>

 int	main(void)
 {
 	//int	i = 0;

 	int	fd = open("test1.txt", O_RDONLY);
 	if (fd < 0)
 		return (1);
 	close(fd);
 	//get_next_line(fd);
 	printf("B");
	while (i < 17)
	{
		char	*line = get_next_line(fd);
		if (!line)
			break ;
		printf("result: [%s]\n", line);
		free(line);
		i++;
	}
 	close(fd);
 	return (0);
 }

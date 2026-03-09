/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:43:42 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/12 09:39:04 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_string	ret;
	char		c;

	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		c = ft_getc(fd);
		if (エラー)
		{
			//ret.strのfree
		}
		if (c == EOF)
			break ;
		ft_putc(&ret, c);
		if (エラー)
		{
			//ret.strのfree
		}
		if (c == '\n')
			break ;
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');
	return (ret.str);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("c.txt", O_RDONLY);

	if (fd == -1)
	{
		write(2, "Error opening file\n", 19);
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, sizeof(line));
		free(line);
	}
	printf("%d", BUFFER_SIZE);
	close(fd);
	return (0);
}

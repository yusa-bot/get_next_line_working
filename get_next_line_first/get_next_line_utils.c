/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:43:45 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/12 09:33:00 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*buf_ptr;
	static int	n = 0;

	//if (!buf)
	//{
	//	buf = malloc(BUFFER_SIZE);
	//	if (!buf)
	//		return (EOF);
	//}
	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			return (EOF);
		buf_ptr = buf;
	}
	if (--n >= 0)
		return ((unsigned char)*buf_ptr++);
	else
		return (EOF);
}

int	ft_putc(t_string *str, char c)
{
	size_t	new_capa;
	char	*new_str;

	if (str->len + 1 > str->capa)
	{
		if (str->capa == 0)
			new_capa = 8;
		else
			new_capa = str->capa * 2;
		new_str = malloc(new_capa);
		if (!new_str)
			return (-1);
		ft_memcpy(new_str, str->str, str->len);
		free(str->str);
		str->str = new_str;
		str->capa = new_capa;
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}

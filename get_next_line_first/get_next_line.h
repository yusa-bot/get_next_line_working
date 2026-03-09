/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 06:40:14 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/12 09:36:41 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1200
#endif

typedef struct	s_string
{
	char	*str;//文字
	size_t	len;//文字の長さ
	size_t	capa;//キャパ
}	t_string;

int		ft_getc(int fd);
int		ft_putc(t_string *str, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif

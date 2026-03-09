/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:26:34 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/11 09:29:40 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

typedef struct s_fd_node
{
	int					fd;
	char				*buf;
	struct s_fd_node	*next;
}	t_fd_node;

static t_fd_node	*fd_list = NULL;

char	*get_next_line(int fd)
{
	t_fd_node	*node;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	node = find_fd_node
}

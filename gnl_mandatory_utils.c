/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:11:56 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/15 01:10:48 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strlen(char	*s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	char	ch;

	if (!s)
		return (0);
	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			return (s);
		s++;
	}
	if (ch == '\0')
		return (s);
	return (0);
}

char	*ft_strjoin(char  *last_str, char *buf)
{
	char	*ptr;
	int		i;
	int		j;

	if (!buf)
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	if (!last_str)
	{
		last_str = (char *)malloc(1 * sizeof(char));
		if (!last_str)
			return (NULL);
		last_str[0] = '\0';
	}
	ptr = malloc(sizeof(char) * (ft_strlen(last_str) + ft_strlen(buf) + 1));
	if (!ptr)
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	i = -1;
	//after second
	if (last_str)
		while  (last_str[++i] != '\0')
			ptr[i] = last_str[i];
	j = 0;
	while (buf[j] != '\0')
		ptr[i++] = buf[j++];
	ptr[i] = '\0';
	free(last_str);
	last_str = NULL;
	return (ptr);
}

//last_str extaction until nl
char	*get_nl_line(char *last_str)
{
	int		i;
	char	*str;

	if (!last_str)
		return (NULL);
	i = 0;
	while (last_str[i] && last_str[i] != '\n')
		i++;
	//改行が無い場合でも、'\0'で埋まるので終端保証される。
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (last_str[i] && last_str[i] != '\n')
	{
		str[i] = last_str[i];
		i++;
	}
	if (last_str[i] == '\n')
	{
		str[i] = last_str[i];
		i++;
	}
	str[i] = '\0';
	//last_strはnew_last_strで使った後にfree
	return (str);
}

char	*new_last_str(char *last_str)
{
	int		i;
	int		j;
	char	*str;

	if (!last_str)
		return (NULL);
	i = 0;
	while (last_str[i] && last_str[i] != '\n')
		i++;
	// str finish '\n'

	//この関数で作っているlast_strは次のgnl()呼び出し時に使う用
	//改行があった場合複数回に分けてgnlするから、改行がなければもう文字列は全て出し終えている。
	if (!last_str[i])
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	// new last_str
	str = malloc(sizeof(char) * (ft_strlen(last_str) - i + 1));
	if (!str)
	{
		free(last_str);
		last_str = NULL;
		return (NULL);
	}
	i++; //'\n'
	j = 0;
	while (last_str[i])
		str[j++] = last_str[i++];
	str[j] = '\0';
	free(last_str);
	last_str = NULL;
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 06:46:57 by ayusa             #+#    #+#             */
/*   Updated: 2025/05/11 04:21:53 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

//読み込んだデータを前のデータ（stash）にくっつける
void	str_join(char *s1, char*s2)
{

}

//stashの改行までをextract
char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

//改行以降をstashに保存
char	*update_stash(char *stash)
{
	int		i = 0;
	int		j = 0;
	char	*new_stash;

	if (!stash)
		return (NULL);

	// 改行までスキップ
	while (stash[i] && stash[i] != '\n')
		i++;

	// 改行がなかったら、もう残りはない
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}

	i++; // 改行もスキップしてその次から

	// 残りを新しくコピー
	new_stash = malloc(str_len(stash + i) + 1);
	if (!new_stash)
		return (NULL);

	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';

	free(stash);
	return (new_stash);
}

int	main(void)
{
	char	s[] = "asd\nsa";
	int	res;
	res = has_newline(s);
	printf("%d", res);
	return (0);
}

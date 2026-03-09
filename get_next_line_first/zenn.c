#include "get_next_line.h"
//一文字づつputchar→文字列にして返す

typedef struct	s_string
{
	char	*str;
	size_t	len;
	size_t	capa;
}	t_string;

//1文字づつ読み込む
int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	//*移動のため
	static char	*buf_fp;
	static int	n = 0;

	if (n == 0)
	{
		//n: bytes
		//バッファリング
		n = read(fd, buf, sizeof(buf));
		buf_fp = buf;
	}
	return (--n >= 0) ? (unsigned char) *buf_fp++ : EOF;
}

//1文字つづメモリに書き込む
int	ft_putc(t_string *str, char c)
{
	if (str->len + 1 > str->capa)
	{
		size_t new_capa = (str->capa == 0) ? 8 : str->capa * 2;
		char *new_str = malloc(new_capa);
		if (!new_str)
			return -1; // malloc失敗

		ft_memcpy(new_str, str->str, str->len); // 古いデータをコピー

		free(str->str);            // 古い領域を開放
		str->str = new_str;        // ポインタ更新
		str->capa = new_capa;      // 新しい容量を記録
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}

char	*get_next_line(int fd)
{
	t_string ret;
	char	c;

	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;

	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		ft_putc(&ret, c);
		if (c == '\n')
			break ;
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');
	return (ret.str);//line
}

int	main(void)
{
	int	fd;
	int	c;

	fd = open("c.txt",O_RDONLY);
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		printf("%c", c);
	}
	close(fd);
	return (0);
}

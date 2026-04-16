#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


// getc()
int getchar(void)
{
  static char buf[BUFSIZ];
  static char *bufp;
  static int n = 0;

  if(n == 0) { /* バッファはカラ */
    n = read(0, buf, sizeof buf);
    bufp = buf;
  }
  return (--n >= 0) ? (unsignd char) *bufp++ : EOF;
}

// putc()
int main(void)
{
    int fd;
    int c;

    fd = open("test.txt", O_RDONLY);
    while (1) {
        c = ft_getc(fd);
        if (c == EOF)
            break ;
        printf("%c", c);
    }
    close(fd);
    return (0);
}

// get_next_line
char *get_next_line(int fd)
{
    // 今回の場合はt_string　 *retではなく、 t_string retとしておけば、
    // 構造体をmalloc & freeする必要がないので実装が楽になります。
    t_string ret;
    char c;

    // 初期化
    ret.str = NULL;
    ret.len = 0;
    ret.capa = 0;

    while(1) {　// 無限ループ
        c = ft_getc(fd); // 1文字読み込む

        if(c == EOF) {
            break;　// ファイルの最後ならループから抜ける
        }
        ft_putc(&ret, c);　// 1文字詰める
        if(c == '\n') {
            break;　// 改行だったらループから抜ける
        }
    }
    if(ret.len > 0) {
        ft_putc(&ret, '\0');　// 最後にNULL文字を詰める
    }
    return ret.str;
}

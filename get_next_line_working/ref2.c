#include "stdio_impl.h"
#include <string.h>
#include <inttypes.h>
#include <errno.h>

#define MIN(a,b) ((a)<(b) ? (a) : (b))

#include <stdio.h>

ssize_t getdelim(char **restrict s, size_t *restrict n, int delim, FILE *restrict f)
{
	char *tmp;
	unsigned char *z;
	size_t k;
	size_t i=0;
	int c;

	/* 引数チェック */
	if (!n || !s) {
		errno = EINVAL;
		return -1;
	}

	/* 未確保ならサイズ0として扱う */
	if (!*s) *n=0;

	/* FILEロック（スレッドセーフ） */
	FLOCK(f);

	for (;;) {
		/* 内部バッファから区切り文字を探す */
		z = memchr(f->rpos, delim, f->rend - f->rpos);
		/* 今回コピーする長さを決める */
		k = z ? z - f->rpos + 1 : f->rend - f->rpos;
		/* バッファ不足なら拡張 */
		if (i+k >= *n)
		{
			/* サイズ計算のオーバーフロー防止 */
			if (k >= SIZE_MAX/2-i) goto oom;
			/* 必要量を見積もって拡張 */
			*n = i+k+2;
			/* 余裕があるときは倍に伸ばす */
			if (*n < SIZE_MAX/4) *n *= 2;
			tmp = realloc(*s, *n);
			if (!tmp)
			{
				/* 最小限サイズで再試行 */
				*n = i+k+2;
				tmp = realloc(*s, *n);
				if (!tmp) goto oom;
			}
			/* 新しいバッファを反映 */
			*s = tmp;
		}
		/* 内部バッファからまとめてコピー */
		memcpy(*s+i, f->rpos, k);
		f->rpos += k;
		i += k;
		/* 区切り文字が見つかれば終了 */
		if (z) break;
		/* 追加の1文字を読んで区切り確認 */
		if ((c = getc_unlocked(f)) == EOF)
		{
			if (!i || !feof(f))
			{
				FUNLOCK(f);
				return -1;
			}
			break;
		}
		/* 1文字追加して区切りなら終了 */
		if (((*s)[i++] = c) == delim) break;
	}
	/* NUL終端 */
	(*s)[i] = 0;

	/* ロック解除 */
	FUNLOCK(f);

	return i;
oom:
	/* OOM処理 */
	FUNLOCK(f);
	errno = ENOMEM;
	return -1;
}

weak_alias(getdelim, __getdelim);

ssize_t getline(char **restrict s, size_t *restrict n, FILE *restrict f)
{
	return getdelim(s, n, '\n', f);
}

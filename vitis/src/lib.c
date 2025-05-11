#include "lib.h"

#include <stdio.h>

void *co_memset(void *b, int c, long len)
{
    char *p;
    for (p = b; len > 0; len--)
        *(p++) = c;
    return b;
}

void *co_memcpy(void *dst, const void *src, long len)
{
    char *d = dst;
    const char *s = src;
    for (; len > 0; len--)
        *(d++) = *(s++);
    return dst;
}

int co_memcmp(const void *b1, const void *b2, long len)
{
    const char *p1 = b1, *p2 = b2;
    for (; len > 0; len--)
    {
        if (*p1 != *p2)
            return (*p1 > *p2) ? 1 : -1;
        p1++;
        p2++;
    }
    return 0;
}

int co_strlen(const char *s)
{
    int len;
    for (len = 0; *s; s++, len++)
        ;
    return len;
}

char *co_strcpy(char *dst, const char *src)
{
    char *d = dst;
    for (;; dst++, src++)
    {
        *dst = *src;
        if (!*src)
            break;
    }
    return d;
}

int co_strcmp(const char *s1, const char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
    }
    return 0;
}

int co_strncmp(const char *s1, const char *s2, int len)
{
    while ((*s1 || *s2) && (len > 0))
    {
        if (*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
        len--;
    }
    return 0;
}

/* １文字送信 */
int co_putc(unsigned char c)
{
    if (c == '\n')
    {
        putchar('\n');
    }
    else
    {
        putchar(c);
    }
    fflush(stdout);
    return c;
}
#include <stdio.h>

/* １文字受信 */
unsigned char co_getc(void)
{
    unsigned char c = getc(stdin);
    return (c == '\r') ? '\n' : c; // 改行コードを統一
}
/* 文字列送信 */
int co_puts(unsigned char *str)
{
    while (*str)
        co_putc(*(str++));
    fflush(stdout);

    return 0;
}

/* 文字列受信 */
int co_gets(unsigned char *buf)
{
    int i = 0;
    int rst_flg = 0;
    char *special_char;
    unsigned char c;
    do
    {
        c = co_getc();
        if (c == '\n')
        {
            c = '\0';
        }
        else if (c == '\b' || c == 127) // バックスペースまたはDELキー
        {
            if (i > 0)
            {
                i--;
                buf[i] = '\0';
                co_putc('\b'); // カーソルを戻す
                co_putc(' ');  // 空白で上書き
                co_putc('\b'); // 再度カーソルを戻す
            }
            continue;
        }
        else if (c == '\x1b' && (c = co_getc()) == '[') // エスケープシーケンス
        {
            c = co_getc(); // さらに次の文字を取得
            rst_flg = 1;
            if (c == 'A') // 上矢印キー
            {
                // bufferを全てクリア
                buf[i] = '\0'; // バッファをクリア
                special_char = "\x1b[A";
                continue;
            }
            else if (c == 'B') // 下矢印キー
            {
                buf[i] = '\0'; // バッファをクリア
                special_char = "\x1b[B";
                continue;
            }
        }
        else
        {
            co_putc(c);
            buf[i++] = c;
        }
    } while (c);
    if (rst_flg)
    {
        co_memcpy(buf, special_char, co_strlen(special_char));
        i = co_strlen(special_char);
        buf[i] = '\0'; // バッファをクリア
    }
    return i - 1;
}

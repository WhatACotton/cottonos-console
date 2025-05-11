#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "lib.h"
// #include "program.h"

void buf_rst(char *buf, char *last_command)
{
    co_memset(last_command, 0, sizeof(last_command));
    co_strcpy(last_command, buf);
    // buffer clear
    co_memset(buf, 0, sizeof(buf));
    return;
}
void print_banner()
{
    co_puts("\r\n             __    __                                     \r\n");
    co_puts("            /\\ \\__/\\ \\__                                  \r\n");
    co_puts("  ___    ___\\ \\ ,_\\ \\ ,_\\   ___     ___     ___     ____  \r\n");
    co_puts(" /'___\\ / __`\\ \\ \\/\\ \\ \\/  / __`\\ /' _ `\\  / __`\\  /',__\\ \r\n");
    co_puts("/\\ \\__//\\ \\L\\ \\ \\ \\_\\ \\ \\_/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\__, `\\\r\n");
    co_puts("\\ \\____\\ \\____/\\ \\__\\\\ \\__\\ \\____/\\ \\_\\ \\_\\ \\____/\\/\\____/ \r\n");
    co_puts(" \\/____/\\/___/  \\/__/ \\/__/\\/___/  \\/_/\\/_/\\/___/  \\/___/  \r\n");
    co_puts("                                                          \r\n");
}
int main()
{

    static char buf[16];
    static char last_command[16] = "";

    init_platform();
    print_banner();
    co_puts("\r\nType commands (Enter exit to stop):\r\n");
    while (1)
    {
        co_puts("cottonos_console > ");
        co_gets(buf);
        if (!co_strcmp(buf, "\x1b[A")) // 上矢印キー
        {
            co_puts(last_command);
            co_strcpy(buf, last_command);
        }
        if (!co_strcmp(buf, "load"))
        {
            buf_rst(buf, last_command);
            co_puts("\nload command received.\n\r");
        }
        else if (!strcmp(buf, "dump"))
        {
            buf_rst(buf, last_command);
            co_puts("\ndump command received.\n\r");
        }
        else if (!strcmp(buf, "run"))
        {
            buf_rst(buf, last_command);
            co_puts("\nrun command received.\n\r");
        }
        else if (!strcmp(buf, "exit"))
        {
            buf_rst(buf, last_command);
            co_puts("\nExiting...\n\r");
            break;
        }
        else if (!strcmp(buf, "help"))
        {
            buf_rst(buf, last_command);
            co_puts("\nAvailable commands:\r\n");
            co_puts("\tload - Load a program\r\n");
            co_puts("\tdump - Dump memory\r\n");
            co_puts("\trun  - Run a program\r\n");
            co_puts("\thelp - Show this help message\r\n");
            co_puts("\texit - Exit the console\r\n");
        }
        else
        {
            co_puts("\nunknown command:");
            co_puts(buf);
            co_puts("\r\n");
            co_memset(buf, 0, sizeof(buf));
        }
    }
    co_puts("\nFinished receiving characters.\r\n");
    cleanup_platform();
    return 0;
}

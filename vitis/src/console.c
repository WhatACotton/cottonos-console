#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "lib.h"
#include <stdlib.h>
#include <string.h>

void copy_last_command(char *buf, char *last_command)
{
    memset(last_command, 0, sizeof(last_command));
    strcpy(last_command, buf);
}

void buf_rst(char *buf, size_t size)
{
    memset(buf, 0, size);
}
void print_banner()
{
    printf("\r\n             __    __                                     \r\n");
    printf("            /\\ \\__/\\ \\__                                  \r\n");
    printf("  ___    ___\\ \\ ,_\\ \\ ,_\\   ___     ___     ___     ____  \r\n");
    printf(" /'___\\ / __`\\ \\ \\/\\ \\ \\/  / __`\\ /' _ `\\  / __`\\  /',__\\ \r\n");
    printf("/\\ \\__//\\ \\L\\ \\ \\ \\_\\ \\ \\_/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\__, `\\\r\n");
    printf("\\ \\____\\ \\____/\\ \\__\\\\ \\__\\ \\____/\\ \\_\\ \\_\\ \\____/\\/\\____/ \r\n");
    printf(" \\/____/\\/___/  \\/__/ \\/__/\\/___/  \\/_/\\/_/\\/___/  \\/___/  \r\n");
    printf("                                                          \r\n");
}
int main()
{
    static char buf[16];
    static char last_command[16] = "";

    init_platform();
    print_banner();
    printf("\r\nType commands (Enter exit to stop):\n");
    while (1)
    {
        printf("cottonos_console > ");
        co_gets(buf);

        if (!strcmp(buf, "\x1b[A")) // 上矢印キー
        {
            strcpy(buf, last_command);
            printf("%s", buf);
        }

        if (!strcmp(buf, "run"))
        {
            printf("\nrun command received.\n");
            copy_last_command(buf, last_command);
            buf_rst(buf, sizeof(buf));
        }
        else if (!strcmp(buf, "\0"))
        {
            printf("\n");
            buf_rst(buf, sizeof(buf));
        }
        else if (!strcmp(buf, "exit"))
        {
            printf("\nExiting...\n");
            break;
        }
        else if (!strcmp(buf, "help") || !strcmp(buf, "?"))
        {
            printf("\nAvailable commands:\n");
            printf("\trun  - Run a program\n");
            printf("\thelp - Show this help message\n");
            printf("\texit - Exit the console\n");
            copy_last_command(buf, last_command);
            buf_rst(buf, sizeof(buf));
        }
        else
        {
            printf("\nunknown command: ");
            printf("%s", buf);
            printf("\n");
            buf_rst(buf, sizeof(buf));
        }
    }
    printf("\nFinish Bootloader.\n");
    cleanup_platform();
    return 0;
}
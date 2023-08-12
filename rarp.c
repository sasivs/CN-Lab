#include <stdio.h>
#include <string.h>
#include <conio.h>
int main()
{
    char ip[10][20] = {"192.168.0.64", "192.168.0.60", "192.168.0.68", "132.147.3.3"};
    char et[10][20] = {"00_A8_00_40_8E_FS", "00_16_17_31_8e_22", "00_16_17_31_8E_F7", "00_16_17_31_8E_08"};
    char ipaddr[20], etaddr[20];
    int i, op;
    int x = 0, y = 0;
    clrscr();
    printf("enter ethernet address");
    scanf("%s", etaddr);
    for (i = 0; i <= 20; i++)
    {
        if (strcmp(etaddr, et[i]) == 0)
        {
            printf("IP address is %s", ip[i]);
            y = 1;
        }
    }
    if (y == 0)
        printf("Invalid ethernet address");
}
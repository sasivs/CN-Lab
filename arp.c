#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
        struct sockaddr_in sin = {0};
        struct arpreq myarp = {{0}};
        unsigned char *ptr;
        int sd;
        sin.sin_family = AF_INET;
        if (inet_aton(argv[1], &sin.sin_addr) == 0)
        {
                printf("IP address Entered '%s' is not valid \n", argv[1]);
                exit(0);
        }
        memcpy(&myarp.arp_pa, &sin, sizeof(myarp.arp_pa));
        strcpy(myarp.arp_dev, "echo");
        sd = socket(AF_INET, SOCK_DGRAM, 0);

        if (ioctl(sd, SIOCGARP, &myarp) == 1)
        {
                printf("No Entry in ATP cache for '%s'\n", argv[1]);
                exit(0);
        }
        ptr = &myarp.arp_pa.sa_data[0];
        printf("\nMAC Address for '%s' : ", argv[1]);
        printf("%x:%x:%x:%x:%x:%x\n", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));
        printf("\n\t\t\t\t%x:%x:%x:%x:%x:%x\n", myarp.arp_ha.sa_data[0],
               myarp.arp_ha.sa_data[1], myarp.arp_ha.sa_data[2],
               myarp.arp_ha.sa_data[3], myarp.arp_ha.sa_data[4], myarp.arp_ha.sa_data[5]);
        return 0;
}

/*
This C program takes an IP address as input and looks up the corresponding MAC address in the Address Resolution Protocol (ARP) 
cache of the system. It uses the struct arpreq and ioctl() system call to perform the lookup.

Here's a breakdown of the program:

#include statements: These import the required libraries and headers for the program.

main() function: This is the entry point of the program. It takes the IP address as a command-line argument.

struct sockaddr_in: This is a structure that represents an internet address. In this program,
it is used to store the IP address passed as an argument.

if(inet_aton(argv[1],&sin.sin_addr)==0): 
This line converts the IP address in string format to binary format and stores it in sin.sin_addr. 
If the IP address is not valid, the program prints an error message and exits.

struct arpreq: This is a structure used to perform the ARP lookup. 
It has two fields: arp_pa (the IP address to look up) and arp_dev (the network interface to use). 
In this program, arp_dev is set to "echo" which is not a valid interface,
but this does not matter since the field is not used in the lookup.

memcpy(&myarp.arp_pa,&sin,sizeof(myarp.arp_pa)): 
This line copies the binary IP address stored in sin to myarp.arp_pa.

sd=socket(AF_INET,SOCK_DGRAM,0): This line creates a socket of type SOCK_DGRAM for IPv4 addresses.

ioctl(sd,SIOCGARP,&myarp): This line performs the ARP lookup using the ioctl() system call with the SIOCGARP command. 
If the lookup fails, the program prints an error message and exits.

ptr=&myarp.arp_pa.sa_data[0]: This line points ptr to the first byte of the MAC address stored in myarp.arp_pa.sa_data.

printf("%x:%x:%x:%x:%x:%x\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5)): 
This line prints the MAC address in hexadecimal format using the values pointed to by ptr and the subsequent 5 bytes.

printf("\n\t\t\t\t%x:%x:%x:%x:%x:%x\n", myarp.arp_ha.sa_data[0], 
myarp.arp_ha.sa_data[1], myarp.arp_ha.sa_data[2], myarp.arp_ha.sa_data[3], myarp.arp_ha.sa_data[4], 
myarp.arp_ha.sa_data[5]): 
This line prints the MAC address in hexadecimal format using the sa_data field of myarp.arp_ha, 
which is the hardware address field of the ARP reply. This is equivalent to the MAC address obtained from ptr in the previous line.

return 0: This line ends the program and returns 0 to the calling process.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void generateOctets(char* addr, int* array){
    char dot = '.';
    char* endptr;
    char* iterptr = addr;
    for (int i=0; i<4; i++){
        array[i] = strtol(iterptr, &endptr, 10);
        iterptr = endptr+1;
    }
}


void forwardingTable(char* addr, int mask){
    int* array = (int*)malloc(sizeof(int)*4);
    int* dba = (int*)malloc(sizeof(int)*4);
    int* subnet_id = (int*)malloc(sizeof(int)*4);
    int* dba_subnet = (int*)malloc(sizeof(int)*4);
    int* mask_array = (int *) malloc(sizeof(int)*4);
    int* first_host = (int *) malloc(sizeof(int)*4);
    int* last_host = (int *) malloc(sizeof(int)*4);
    int iter_mask = mask;
    for (int i=0; i<4; i++){
        if (iter_mask>=8){
            mask_array[i]=255;
        }
        else if (iter_mask>0){
            mask_array[i]=(int)pow(2,8)-(int)pow(2,8-iter_mask);
        }
        else{
            mask_array[i]=0;
        }
        iter_mask-=8;
    }

    generateOctets(addr, array);
    int mask_dec = (int)pow(2,32) - (int)pow(2,32-mask);
    int subnets, hosts;
    hosts = (int)pow(2,32-mask);
    for(int i=0; i<4; i++){
        subnet_id[i] = array[i] & mask_array[i];
    }
    for(int i=0; i<4; i++){
        if (mask_array[i]!=255){
            dba_subnet[i] = array[i] | (255-mask_array[i]);
        }
        else{
            dba_subnet[i] = array[i];
        }
    }
    for (int i=0; i<3; i++){
        first_host[i] = subnet_id[i];
        last_host[i] = dba_subnet[i];
    }
    first_host[3] = subnet_id[3]+1;
    last_host[3] = dba_subnet[3]-1;
    if (array[0]<=127){
        subnets = (int)pow(2, mask-8);
        dba[0]=array[0];
        dba[1]=255;
        dba[2]=255;
        dba[3]=255;
    }
    else if(array[0]<=191){
        subnets = (int)pow(2, mask-16);
        dba[0]=array[0];
        dba[1]=array[1];
        dba[2]=255;
        dba[3]=255;
    }
    else if(array[0]<=223){
        subnets = (int)pow(2, mask-24);
        dba[0]=array[0];
        dba[1]=array[1];
        dba[2]=array[2];
        dba[3]=255;
    }

    printf("# of subnets: %d\n", subnets);
    printf("Subnet mask: %f\n", pow(2,32)-pow(2,32-mask));
    printf("DBA: %d.%d.%d.%d\n", dba[0], dba[1], dba[2], dba[3]);
    printf("Subnet DBA: %d.%d.%d.%d\n", dba_subnet[0], dba_subnet[1], dba_subnet[2], dba_subnet[3]);
    printf("# of hosts per network %d\n", hosts);
    printf("First host id %d.%d.%d.%d\n", first_host[0], first_host[1], first_host[2], first_host[3]);
    printf("Last host id %d.%d.%d.%d\n", last_host[0], last_host[1], last_host[2], last_host[3]);
    printf("Subnet network id: %d.%d.%d.%d\n", subnet_id[0], subnet_id[1], subnet_id[2], subnet_id[3]);
    printf("\n\n");
}

int main(){
    char addr[] = "192.168.1.0";
    int mask = 27;
    forwardingTable(addr, mask);
    char addr1[] = "1.3.5.192";
    mask = 26;
    forwardingTable(addr1, mask);
    char addr2[] = "20.0.5.0";
    mask = 13;
    forwardingTable(addr2, mask);
    char addr3[] = "132.6.128.0";
    mask = 18;
    forwardingTable(addr3, mask);
}
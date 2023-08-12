#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


char* sender(char* data, char* crc){
    char* new_data = (char*)malloc(sizeof(char)*(strlen(data)+strlen(crc)));
    for (int i=0; i<(strlen(data)); i++){
        new_data[i] = data[i];
    }
    for (int i=(strlen(data)); i<(strlen(data)+strlen(crc)-1); i++){
        new_data[i] = '0';
    }
    new_data[strlen(data)+strlen(crc)-1] = '\0';
    char* div = (char*)malloc(sizeof(char)*(strlen(crc)+1));
    for (int i=0; i<(strlen(crc)); i++){
        div[i]=data[i];
    }
    div[strlen(div)-1] = '\0';
    int j = strlen(crc);
    while(true){
        for (int i=0; i<strlen(crc); i++){
            if (div[i]=='0' && crc[i]=='0'){
                div[i] = '0';
            }
            else if (div[i]=='1' && crc[i]=='1'){
                div[i]='0';
            }
            else{
                div[i] = '1';
            }
        }
        while(j<(strlen(data)+strlen(crc)-1) && div[0]=='0'){
            for (int i=1; i<strlen(crc); i++){
                div[i-1]=div[i];
            }
            div[strlen(crc)-1]=new_data[j];
            j++;
        }
        if (div[0]=='0'){
            break;
        }
    }
    for (int i=(strlen(data)); i<(strlen(data)+strlen(crc)-1); i++){
        new_data[i] = div[i-strlen(data)+1];
    }
    return new_data;
}


int receiver(char* data, char* crc){
    char* div = (char*)malloc(sizeof(char)*(strlen(crc)+1));
    for (int i=0; i<(strlen(crc)); i++){
        div[i]=data[i];
    }
    div[strlen(div)-1] = '\0';
    int j = strlen(crc);
    while(true){
        for (int i=0; i<strlen(crc); i++){
            if (div[i]=='0' && crc[i]=='0'){
                div[i] = '0';
            }
            else if (div[i]=='1' && crc[i]=='1'){
                div[i]='0';
            }
            else{
                div[i] = '1';
            }
        }

        while(j<(strlen(data)) && div[0]=='0'){
            for (int i=1; i<strlen(crc); i++){
                div[i-1]=div[i];
            }
            div[strlen(crc)-1]=data[j];
            j++;
        }

        if (div[0]=='0'){
            break;
        }
    }
    for (int i=0; i<(strlen(crc)); i++){
        if (div[i]!='0'){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int main(){
    char data[] = "101101";
    char crc[] = "1101";
    printf("Data: %s\n", data);
    char* sender_data = sender(data, crc);
    printf("Valid: %d\n", receiver(sender_data, crc));
    return 0;
}
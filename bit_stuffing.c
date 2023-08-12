#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* bitStuffing(char* data){
    int len = strlen(data);
    char* stuffed_data = (char*)malloc(sizeof(char)*len+1);
    int count = 0, stuffed_data_len = len+1;
    int j=0;
    for (int i=0; i<len; i++){
        stuffed_data[j++]=data[i];
        if (count==4){
            stuffed_data = (char*)realloc(stuffed_data, stuffed_data_len++);
            stuffed_data[j++] = '0';
            count=0;
        }
        if (data[i]=='1' && (i+1)<len && data[i+1]=='1'){
            count++;
        }
        else{count=0;}
    }
    stuffed_data[stuffed_data_len-1]='\0';
    return stuffed_data;
}

char* bitStuffingReceiver(char* data){
    int len = strlen(data);
    char* decode_data = (char*)malloc(sizeof(char)*len+1);
    int count = 0, stuffed_data_len = len+1;
    int j=0, i=0, data_len=0;
    while(i<len){
        decode_data[j++]=data[i];
        data_len++;
        if (count==4){
            i++;
            count=0;
        }
        if (data[i]=='1' && (i+1)<len && data[i+1]=='1'){
            count++;
        }
        else{count=0;}
        i++;
    }
    decode_data[data_len]='\0';
    return decode_data;
}

int main(){
    char data[] = "111111101";
    char* stuffed_data = bitStuffing(data);
    printf("%s\n", stuffed_data);
    char* decoded_data = bitStuffingReceiver(stuffed_data);
    printf("%s\n", decoded_data);
    return 0;
}

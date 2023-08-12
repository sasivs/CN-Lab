#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* byteStuffing(char* data, char* delim){
    int len = strlen(data);
    int delim_len = strlen(delim);
    int i=0,j=0;
    int stuffed_data_len = len;
    char* stuffed_data = (char*)malloc(sizeof(char)*len+1);
    while(i<len){
        if (data[i]==delim[0]){
            int k=1;
            while (k<delim_len && (i+k)<len){
                if (data[i+k]!=delim[k]) break;
                k++;
            }
            if (k==delim_len){
                stuffed_data_len+=delim_len;
                stuffed_data = (char*)realloc(stuffed_data, sizeof(char)*(stuffed_data_len));
                for (int m=0; m<delim_len; m++){
                    stuffed_data[j] = data[i++];
                    stuffed_data[j+delim_len] = delim[m];
                    j++;
                }
                j+=delim_len;
            }
            else{
                stuffed_data[j++] = data[i++];
            }
        }
        else{
            stuffed_data[j++] = data[i++];
        }
    }
    stuffed_data[stuffed_data_len]='\0';
    return stuffed_data;
}

char* byteStuffingReceiver(char* data, char* delim){
    int len = strlen(data);
    int delim_len = strlen(delim);
    int i=0,j=0;
    int destuffed_data_len = 0;
    char* destuffed_data = (char*)malloc(sizeof(char)*len+1);
    while(i<len){
        if (data[i]==delim[0]){
            int k=1;
            while (k<delim_len && (i+k)<len){
                if (data[i+k]!=delim[k]) break;
                k++;
            }
            if (k==delim_len){
                for (int m=0; m<delim_len; m++){
                    destuffed_data[j] = data[i++];
                    j++;
                }
                i+=delim_len;
                destuffed_data_len+=delim_len;
            }
            else{
                destuffed_data[j++] = data[i++];
                destuffed_data_len++;
            }
        }
        else{
            destuffed_data[j++] = data[i++];
            destuffed_data_len++;
        }
    }
    destuffed_data[destuffed_data_len]='\0';
    return destuffed_data;
}

int main(){
    char data[] = "11101111";
    char delim[] = "111";
    char* stuffed_data = byteStuffing(data, delim);
    printf("%s\n", stuffed_data);
    char* destuffed_data = byteStuffingReceiver(stuffed_data, delim);
    printf("%s\n", destuffed_data);
    return 0;
}
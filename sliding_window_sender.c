#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int window_size = 2;
    int nframes = 5;
    int frame_len = 3;
    char** frames = (char*)malloc(sizeof(char*)*nframes);
    for(int i=0; i<nframes; i++){
        frames[i] = (char*)malloc(sizeof(char)*frame_len);
        gets(frames[i]);
    }

    int fd;
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    char ack[window_size];
    int i=0,j=0,k=0;
    while(j<nframes){
        k=0;
        fd = open(myfifo,O_WRONLY);
        while(k<window_size && (j+k)<nframes){
            write(fd, frames[j+k], strlen(frames[j+k])+1);
            k++;
        }
        close(fd);
        // while(k-- >0){
        //     fd = open(myfifo,O_RDONLY);
        //     read(fd, ack, sizeof(char));
        //     printf("Ack: %s\n", ack);
        //     close(fd);
        //     if (ack=='1'){
        //         j++;
        //     }
        // }
        fd = open(myfifo,O_RDONLY);
        read(fd, ack, window_size);
        printf("Ack: %s\n", ack);
        close(fd);
        j+=window_size;
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int window_size = 2, frame_len=3, nframes=5;
    char ack[window_size], frame[frame_len];

    int fd1;
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    int j=0, k=0;
    while(j<nframes){
        k=0;
        while(k<window_size && (j+k)<nframes){
            fd1 = open(myfifo,O_RDONLY);
            read(fd1, frame, 80);

            printf("User1: %s\n", frame);
            scanf("%c", &ack[j]);
            if (ack[j]=='1'){
                j++;
            }
            close(fd1);
        }
        fd1 = open(myfifo,O_WRONLY);
        write(fd1, ack, window_size);
        close(fd1);
    }
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

int parity(int n){
    int rem, parity=0;
    while(n>0){
        rem = n%2;
        n = n/2;
        if (rem){
            parity = !parity;
        }
    }
    return parity;
}

int oddParity(int n){
    n = n << 1;
    if (!parity(n)){
        n++;
    }
    return n;
}

int evenParity(int n){
    n = n << 1;
    if (parity(n)){
        n++;
    }
    return n;
}

void tamper(char* data){
    int random_num = rand()%(strlen(data));
    int reqChar = (int)data[random_num];
    int ran_index = rand()%32;
    int i = -1, bit=0, n=reqChar;
    while(i<ran_index){
        if (n%2){
            bit = !bit;
        }
        n = n/2;
        i++;
    }
    if (bit){
        reqChar-=(int)pow(2,ran_index);
    }
    else{
        reqChar+=(int)pow(2,ran_index);
    }
    data[random_num] = (char)reqChar;
}

void senderOddParity(char* data){
    int len = strlen(data);
    printf("Sender(Odd Parity): %s\n",data);
    int par = 0, iter_par;
    for (int i=0; i<len; i++){
        for (int j=0; j<8; j++) {
            int bit = (data[i] >> j) & 1; // extract the jth bit of the ith byte
            iter_par = (bit == 1) ? 0 : 1; // set iter_par to 0 if bit is 1, 1 otherwise
            par += iter_par;
        }
    }
    int last_char = (int)data[len-1];
    last_char = last_char << 1;
    if (!(par%2)){
        last_char++;
    }
    data[len-1] = (char)last_char;
    return;
}

void receiverOddParity(char* data){
    int len = strlen(data);
    int par = 0, iter_par;
    for (int i=0; i<len; i++){
        for (int j=0; j<8; j++) {
            int bit = (data[i] >> j) & 1; // extract the jth bit of the ith byte
            iter_par = (bit == 1) ? 0 : 1; // set iter_par to 0 if bit is 1, 1 otherwise
            par += iter_par;
        }
    }
    data[len-1] = data[len-1] >> 1;
    printf("Receiver(Odd Parity): %s\n",data);
    if ((par%2)){
        printf("Data is consistent\n");
    }
    else{
        printf("Error!! Data corrupted\n");
    }
}

void senderEvenParity(char* data){
    int len = strlen(data);
    printf("Sender(Even Parity): %s\n",data);
    int par = 0, iter_par;
    for (int i=0; i<len; i++){
        for (int j=0; j<8; j++) {
            int bit = (data[i] >> j) & 1; // extract the jth bit of the ith byte
            iter_par = (bit == 1) ? 0 : 1; // set iter_par to 0 if bit is 1, 1 otherwise
            par += iter_par;
        }
    }
    int last_char = (int)data[len-1];
    last_char = last_char << 1;
    if (par%2){
        last_char++;
    }
    data[len-1] = (char)last_char;
    tamper(data);
    return;
}

void receiverEvenParity(char* data){
    int len = strlen(data);
    int par = 0, iter_par;
    for (int i=0; i<len; i++){
        for (int j=0; j<8; j++) {
            int bit = (data[i] >> j) & 1; // extract the jth bit of the ith byte
            iter_par = (bit == 1) ? 0 : 1; // set iter_par to 0 if bit is 1, 1 otherwise
            par += iter_par;
        }
    }
    if ((par%2)){
        printf("Error!! Data corrupted\n");
    }
    else{
        printf("Receiver(Even Parity): %s\n",data);
        printf("Data is consistent\n");
    }
}

void tamperTwoDimensional(char* data){
    int random_num = rand()%(strlen(data));
    if (data[random_num] == '1'){
        data[random_num] = '0';
    }
    else{
        data[random_num] = '1';
    }
}

void receiverOddTwoDimensionalParity(char* binary){
    printf("Receiver(Odd 2-D): %s\n", binary);
    int stringLen = strlen(binary)%16;
    for(int i=0; i<stringLen; i++){
        int row_par = 0;
        for (int j=0; j<16; j++){
            if (binary[i*16+j] == '1'){
                row_par = !row_par;
            }
        }
        row_par = !row_par;
        if (binary[stringLen*16+i] != (row_par+'0')){
            printf("Error!! Data courrpted\n");
            return;
        }
    }
    for(int i=0; i<16; i++){
        int col_par = 0;
        for (int j=0; j<stringLen; j++){
            if (binary[i+j*16] == '1'){
                col_par = !col_par;
            }
        }
        col_par = !col_par;
        if (binary[stringLen*16+stringLen+i] != (col_par+'0')){
            printf("Error!! Data courrpted\n");
            return ;
        }
    }
    printf("Data is consistent\n");
    return;
}

void senderOddTwoDimensionalParity(char* data, char* binary){
    binary = (char*)malloc(sizeof(char)*((strlen(data)+1)*16+strlen(data)+1));
    for (int i=0; i<((strlen(data)+1)*16+strlen(data)); i++){
        binary[i]='0';
    }
    binary[((strlen(data)+1)*16+strlen(data))] = '\0';
    int chr;
    for(int i=0; i<strlen(data); i++){
        chr = (int)data[i];
        int j=15;
        int par = 0;
        while(chr>0){
            binary[16*i+j]=(chr%2)+'0';
            chr = chr/2;
            if (binary[16*i+j]=='1'){
                par = !par;
            }
            j--;
        }
        if (!par){
            binary[(strlen(data))*16+i] = '1';
        }
        else{
            binary[(strlen(data))*16+i] = '0';
        }
    }
    for(int i=0; i<16; i++){
        int par = 0;
        for(int j=0; j<strlen(data); j++){
            if (binary[j*16+i]=='1'){
                par = !par;
            }
        }
        if (!par){
            binary[(strlen(data))*16+strlen(data)+i] = '1';
        }
        else{
            binary[(strlen(data))*16+strlen(data)+i] = '0';
        }
    }
    printf("Sender(Odd 2-D): %s\n", binary);
    tamperTwoDimensional(binary);
    receiverOddTwoDimensionalParity(binary);
    return;
}


void receiverEvenTwoDimensionalParity(char* binary){
    printf("Receiver(Even 2-D): %s\n", binary);
    int stringLen = strlen(binary)%16;
    for(int i=0; i<stringLen; i++){
        int row_par = 0;
        for (int j=0; j<16; j++){
            if (binary[i*16+j] == '1'){
                row_par = !row_par;
            }
        }
        if (binary[stringLen*16+i] != (row_par+'0')){
            printf("Error!! Data courrpted\n");
            return;
        }
    }
    for(int i=0; i<16; i++){
        int col_par = 0;
        for (int j=0; j<stringLen; j++){
            if (binary[i+j*16] == '1'){
                col_par = !col_par;
            }
        }
        if (binary[stringLen*32+stringLen+i] != (col_par+'0')){
            printf("Error!! Data courrpted\n");
            return ;
        }
    }
    printf("Data is consistent\n");
    return;
}

void senderEvenTwoDimensionalParity(char* data, char* binary){
    binary = (char*)malloc(sizeof(char)*((strlen(data)+1)*16+strlen(data)+1));
    for (int i=0; i<((strlen(data)+1)*16+strlen(data)); i++){
        binary[i]='0';
    }
    binary[((strlen(data)+1)*16+strlen(data))] = '\0';
    int chr;
    for(int i=0; i<strlen(data); i++){
        chr = (int)data[i];
        int j=15;
        int par = 0;
        while(chr>0){
            binary[16*i+j]=(chr%2)+'0';
            chr = chr/2;
            if (binary[16*i+j]=='1'){
                par = !par;
            }
            j--;
        }
        if (par){
            binary[(strlen(data))*16+i] = '1';
        }
        else{
            binary[(strlen(data))*16+i] = '0';
        }
    }
    for(int i=0; i<16; i++){
        int par = 0;
        for(int j=0; j<strlen(data); j++){
            if (binary[j*16+i]=='1'){
                par = !par;
            }
        }
        if (par){
            binary[(strlen(data))*16+strlen(data)+i] = '1';
        }
        else{
            binary[(strlen(data))*16+strlen(data)+i] = '0';
        }
    }
    printf("Sender(Even 2-D): %s\n", binary);
    receiverEvenTwoDimensionalParity(binary);
    return;
}


void receiverCheckSum(char* data){
    int data_len = (strlen(data)/16)-1;
    printf("Receiver(CheckSum): %s\n", data);
    char* sum = (char*)calloc(17, sizeof(char));
    for (int i=0; i<16; i++){
        sum[i] = data[i];
    }
    sum[16] = '\0';
    char carry = '0';
    for (int i=1; i<(data_len+1); i++){
        for (int j=15; j>=0; j--){
            if (sum[j] == '0' && data[i*16+j] == '0' && carry == '0'){
                sum[j] = '0';
            }
            else if (sum[j] == '0' && data[i*16+j] == '1' && carry == '0'){
                sum[j] = '1';
            }
            else if (sum[j] == '1' && data[i*16+j] == '0' && carry == '0'){
                sum[j] = '1';
            }
            else if (sum[j] == '1' && data[i*16+j] == '1' && carry == '0'){
                sum[j] = '0';
                carry = '1';
            }
            else if (sum[j] == '0' && data[i*16+j] == '1' && carry == '1'){
                sum[j] = '0';
                carry = '1';
            }
            else if (sum[j] == '1' && data[i*16+j] == '0' && carry == '1'){
                sum[j] = '0';
                carry = '1';
            }
            else if (sum[j] == '1' && data[i*16+j] == '1' && carry == '1'){
                sum[j] = '1';
                carry = '1';
            }
            else if (sum[j] == '0' && data[i*16+j] == '0' && carry == '1'){
                sum[j] = '1';
                carry = '0';
            }
        }
        int j=15;
        while (carry == '1'){
            if (sum[j] == '0'){
                sum[j] = '1';
                carry = '0';
            }
            else if (sum[j] == '1'){
                sum[j] = '0';
                carry = '1';
            }
            if (j>0) j-=1;
            else j=15;
        }
    }
    for (int i=0; i<16; i++){
        if (sum[i] != '1'){
            printf("Data is corrupted\n");
            return ;
        }
    }
    printf("Data is consistent\n");
    return;
}

void senderCheckSum(char* data, char* binary){
    binary = (char*) malloc(sizeof(char)*((strlen(data)+1)*16+1));
    for (int i=0; i<(strlen(data))*16; i++){
        binary[i]='0';
    }
    for (int i=(strlen(data))*16; i<((strlen(data)+1)*16); i++){
        binary[i]='1';
    }
    binary[(strlen(data)+1)*16] = '\0';
    int sum = 0, chr;
    for(int i=0; i<strlen(data); i++){
        chr = (int)data[i];
        sum += chr;
        int j=15;
        while(chr>0){
            binary[16*i+j]=(chr%2)+'0';
            chr = chr/2;
            j--;
        }
    }
    int rem, j=strlen(binary)-1;
    while(sum>0){
        rem = sum%2;
        if (rem){
            binary[j] = '0';
        }
        else{
            binary[j] = '1';
        }
        sum = sum/2;
        j--;
    }
    printf("Sender(CheckSum): %s\n", binary);
    // tamperTwoDimensional(binary);
    receiverCheckSum(binary);
    return ;
}



int main(){
    char msg[] = "123";
    // senderOddParity(msg);
    // receiverOddParity(msg);
    // char msg1[] = "abcd";
    // senderEvenParity(msg1);
    // receiverEvenParity(msg1);
    // char msg2[] = "a";
    // char* binary;
    // senderOddTwoDimensionalParity(msg2,binary);
    // senderEvenTwoDimensionalParity(msg2,binary);
    char msg3[] = "a";
    char* binary1;
    senderCheckSum(msg3, binary1);
}
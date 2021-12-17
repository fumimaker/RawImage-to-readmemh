#include <stdio.h>

#define HEIGHT  96
#define WIDTH   96
#define DEPTH   3

int main(void){
    FILE *fp = NULL;
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen("kao_9696.raw", "rb");
    if(fp==NULL){
        printf("no file.\n");
        return -1;
    }

    fread(mem, sizeof(unsigned char), sizeof(mem)/sizeof(mem[0]), fp);
    for(int i=0; i<10; i++){
        printf("%02x ",mem[i]);
    }

    fclose(fp);
    
    return 0;
}
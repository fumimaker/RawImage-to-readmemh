#include <stdio.h>

#define HEIGHT  96
#define WIDTH   96
#define DEPTH   3

int main(void){
    FILE *fp = NULL;
    FILE *outfp = NULL;
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen("kao_9696.raw", "rb");
    outfp = fopen("testbin_image.txt", "w");

    if(fp==NULL||outfp==NULL){
        printf("no file.\n");
        return -1;
    }

    fread(mem, sizeof(unsigned char), sizeof(mem)/sizeof(mem[0]), fp);
    for(int i=0; i<HEIGHT*WIDTH; i++){
        if(i!=0){
            fprintf(outfp, "\n");
            printf("\n");
        }
        for(int j=0; j<DEPTH; j++){
            fprintf(outfp, "%02x", mem[j+i*DEPTH]);
            printf("%02x ", mem[j+i*DEPTH]);
        }
    }
    printf("\ndone.\n");

    fclose(fp);
    fclose(outfp);
    return 0;
}
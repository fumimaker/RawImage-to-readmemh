#include <stdio.h>

#define HEIGHT  96
#define WIDTH   96
#define DEPTH   3
static const unsigned char inputname[] = "./input/kao_9696.raw";
static const unsigned char outputname[] = "./output/testbin_image.txt";

int main(void){
    FILE *fp = NULL;
    FILE *outfp = NULL;
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen(inputname, "rb");
    outfp = fopen("output_image.txt", "w");

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
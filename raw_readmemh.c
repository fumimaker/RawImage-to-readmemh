#include <stdio.h>

// #define debug

#define HEIGHT  720
#define WIDTH   1280
#define DEPTH   3
//////////////////////////////////////////////////////////
// raw画像データをreadmemh変換用
// InputIF入力用データです
//////////////////////////////////////////////////////////
static const unsigned char inputname[] = "input/0x0B_.raw";
static const unsigned char outputname[] = "output/0x0B_readmemh.txt";

// static const unsigned char inputname[] = "renzoku.bin";
// static const unsigned char outputname[] = "output/renzoku_readmemh.txt";

int main(void){
    FILE *fp = NULL;
    FILE *outfp = NULL;
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen(inputname, "rb");
    outfp = fopen(outputname, "w");

    if(fp==NULL||outfp==NULL){
        printf("no file.\n");
        return -1;
    }

    fread(mem, sizeof(unsigned char), sizeof(mem)/sizeof(mem[0]), fp);
    for(int i=0; i<HEIGHT*WIDTH; i++){
        if(i!=0){
            fprintf(outfp, "\n");
            #ifdef debug
            printf("\n");
            #endif
        }
        for(int j=0; j<DEPTH; j++){
            fprintf(outfp, "%02x", mem[(2-j)+i*DEPTH]);
            #ifdef debug
            printf("%02x ", mem[j+i*DEPTH]);
            #endif
        }
    }
    printf("\ndone.\n");

    fclose(fp);
    fclose(outfp);
    return 0;
}
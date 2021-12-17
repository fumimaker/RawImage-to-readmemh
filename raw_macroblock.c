#include <stdio.h>

#define HEIGHT  16
#define WIDTH   16
#define DEPTH   3
static const unsigned char inputname[] = "renzoku.txt";
static const unsigned char outputname[] = "output_macroblock.txt";

int main(void){
    FILE *fp = NULL;
    FILE *outfp = NULL;
//unsigned char mem[HEIGHT * WIDTH * DEPTH];
    unsigned char mem[HEIGHT * WIDTH];

    fp = fopen(inputname, "rb");
    outfp = fopen(outputname, "w");

    if(fp==NULL||outfp==NULL){
        printf("no file.\n");
        return -1;
    }

    fread(mem, sizeof(unsigned char), sizeof(mem)/sizeof(mem[0]), fp);

        //マクロブロックの中身
    for(int block_y=0; block_y<HEIGHT/8; block_y++){
        for(int block_x=0; block_x<WIDTH/8; block_x++){

            printf("%d block_x, %d block_y\n",block_x, block_y);
            for(int y=0; y<8; y++){
                for(int x=0; x<8; x++){
                    int addr = (x+block_x*8) + (y*WIDTH + HEIGHT*8*block_y);
                    //fprintf(outfp, "%02x", mem[addr]);
                    printf("%02x ", mem[addr]);
                }
                printf("\n");
            }
        }
        
        printf("\n");printf("\n");
    }
    printf("\ndone.\n");

    fclose(fp);
    fclose(outfp);
    return 0;
}
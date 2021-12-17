#include <stdio.h>

#define HEIGHT  96
#define WIDTH   96
#define DEPTH   3
static const unsigned char inputname[] = "duchshund_square.raw";
static const unsigned char outputname[] = "output_macroblock.txt";

int main(void){
    FILE *fp = NULL;
    FILE *outfp = NULL;
//unsigned char mem[HEIGHT * WIDTH * DEPTH];
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen(inputname, "rb");
    outfp = fopen(outputname, "w");

    if (fp == NULL || outfp == NULL){
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
                    int addr = ((x+block_x*8) + (y*WIDTH + HEIGHT*8*block_y)) * DEPTH;

                    fprintf(outfp, "%02x", mem[addr + 2]);
                    fprintf(outfp, "%02x", mem[addr + 1]);
                    fprintf(outfp, "%02x", mem[addr + 0]);
                    printf("%02x", mem[addr + 2]);
                    printf("%02x", mem[addr + 1]);
                    printf("%02x", mem[addr + 0]);
                    // for(int i=0; i<3; i++){
                    //     fprintf(outfp, "%02x", mem[addr+i]);
                    //     printf("%02x", mem[addr+i]);
                    // }
                    printf(" ");
                    fprintf(outfp, "\n");
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\ndone.\n");

    fclose(fp);
    fclose(outfp);
    return 0;
}
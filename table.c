#include <stdio.h>

#define debug

#define HEIGHT 720  // 96
#define WIDTH 1280   // 96
#define DEPTH 3
// static const unsigned char inputname[] = "input/nekomaru640.raw";
// //"renzoku.txt"; static const unsigned char outputname[] =
// "output/output_nekomaru640.txt";
static const unsigned char inputname[] = "renzoku.txt";
static const unsigned char outputname[] = "renzoku_out.txt";
int main(void) {
    FILE *fp = NULL;
    FILE *outfp = NULL;
    // unsigned char mem[HEIGHT * WIDTH * DEPTH];
    unsigned char mem[HEIGHT * WIDTH * DEPTH];

    fp = fopen(inputname, "rb");
    outfp = fopen(outputname, "w");

    if (fp == NULL || outfp == NULL) {
        printf("no file.\n");
        return -1;
    }

    fread(mem, sizeof(unsigned char), sizeof(mem) / sizeof(mem[0]), fp);

    //マクロブロックの中身
    for (int block_y = 0; block_y < HEIGHT / 8; block_y++) {
        for (int block_x = 0; block_x < WIDTH / 8; block_x++) {
#ifdef debug
            printf("%d block_x, %d block_y\n", block_x, block_y);
#endif
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    int addr = ((x + block_x * 8) +
                                (block_y * WIDTH * 8 + WIDTH * y)) *
                               DEPTH;
                    fprintf(outfp, "%02x", mem[addr + 2]);
                    fprintf(outfp, "%02x", mem[addr + 1]);
                    fprintf(outfp, "%02x", mem[addr + 0]);
#ifdef debug
                    printf("%02x", mem[addr + 2]);
                    printf("%02x", mem[addr + 1]);
                    printf("%02x", mem[addr + 0]);
                    // for(int i=0; i<3; i++){
                    //     fprintf(outfp, "%02x", mem[addr+i]);
                    //     printf("%02x", mem[addr+i]);
                    // }
                    printf(" ");
#endif
                    fprintf(outfp, "\n");
                }
#ifdef debug
                printf("\n");
#endif
            }
#ifdef debug
            printf("\n");
#endif
        }
#ifdef debug
        printf("\n");
#endif
    }
    printf("%d X %d\n", WIDTH, HEIGHT);
    unsigned char str[256];
    sprintf(str, "output file = %s \n", outputname);
    printf("%s", str);
    printf("\ndone.\n");

    fclose(fp);
    fclose(outfp);
    return 0;
}
#include <stdio.h>

#define HEIGHT  72
#define WIDTH   128
#define DEPTH   3

static const unsigned char inputname[] = "outputraw.raw";  //"renzoku.txt";
static const unsigned char outputname[] = "output_text_to_raw.raw";

int main(void) {
	FILE *fp = NULL;
	FILE *outfp = NULL;

	unsigned char mem[HEIGHT * WIDTH * DEPTH];

	fp = fopen(inputname, "rb");
	outfp = fopen(outputname, "wb");

	if (fp == NULL || outfp == NULL) {
		printf("no file.\n");
		return -1;
	}

	//fread(mem, sizeof(unsigned char), sizeof(mem) / sizeof(mem[0]), fp);

    int x=0, y=0;
    unsigned char r=0, g=0, b=0;
    unsigned int image[HEIGHT][WIDTH];
    while (fscanf(fp, "%04x %04x %02hhx %02hhx %02hhx", &x, &y, &r, &g, &b)!=EOF){
        image[y][x] = (r << 16) | (g << 8) | (b << 0);
        printf("%06x %04x %04x %02x %02x %02x\n", image[y][x], x, y, r, g, b);

    }
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            fprintf(outfp, "%c", (image[i][j] & 0xFF0000) >> 16);
            fprintf(outfp, "%c", (image[i][j] & 0x00FF00) >> 8);
            fprintf(outfp, "%c", (image[i][j] & 0x0000FF) >> 0);
        }
    }
    fclose(fp);
    fclose(outfp);
}
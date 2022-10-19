#include <stdio.h>

#define HEIGHT  72
#define WIDTH   128
#define DEPTH   3

static const unsigned char inputname[] = "outputraw.raw";  //"renzoku.txt";
static const unsigned char outputname[] = "output_reordering.raw";

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
    while (fscanf(fp, "%04x %04x %02hhx %02hhx %02hhx", &x, &y, &r, &g, &b)!=EOF){
        printf("%04x %04x %02x %02x %02x\n", x, y, r, g, b);
    }
        fclose(fp);
        fclose(outfp);
}
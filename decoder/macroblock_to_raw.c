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

	fread(mem, sizeof(unsigned char), sizeof(mem) / sizeof(mem[0]), fp);

	for (int k = 0; k < HEIGHT / 8; k++){
		for (int i = 0; i < WIDTH / 8; i++) {
			for(int m=0; m<8; m++){
				int addr = ((i * 64 + k*8) + m)*DEPTH;
				//printf("%03d ", addr);
				fprintf(outfp, "%c", mem[addr + 2]);
				fprintf(outfp, "%c", mem[addr + 1]);
				fprintf(outfp, "%c", mem[addr + 0]);
			}
		}
		// printf("\n");
	}

	fclose(fp);
	fclose(outfp);
}
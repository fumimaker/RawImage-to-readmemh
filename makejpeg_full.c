#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
// #define debug
//////////////////////////////////////////////////////////
// エンコードbitstreamをヘッダと合成
////////////////////////////////////////////////////////////
static const unsigned char headername[]="./Q50header20230427.bin"; //1280*720サイズのヘッダ
#define numofframe 1000
#define numofjpeg 90
// int GetFileSize(const char* FileName[]) {
//     int fsize = 0;
//     FILE* fp = fopen(FileName, "rb");
//     /* ファイルサイズを調査 */
//     fseek(fp, 0, SEEK_END);
//     fgetpos(fp, &fsize);
//     fclose(fp);
//     return fsize;
// }

int main(void) {
    unsigned char mem[1000*1024], header[1024], buf[1000*1024];
    unsigned char eof[2]={0xFF, 0xD9};

    FILE *fp, *fp_header;

    struct stat sb;
    int sizeofheader, sizeofdata;

    fp_header = fopen(headername, "rb");
    if (fp_header == NULL) {
        printf("header no file.\n");
        return -1;
    }
    if (stat(headername, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    sizeofheader = sb.st_size;
    fread(header, sizeof(unsigned char), sizeofheader, fp_header);
    printf("sizeofheader:%d bytes\n", sizeofheader);


	for (int j=0; j<numofframe; j++){
		unsigned int total_sizeofdata = 0;
		memcpy(buf, header, sizeofheader);
		for(int i=0; i<numofjpeg; i++){
			char moji[32];
			sprintf(moji, "binout/%04d.bin", i);
			fp = fopen(moji, "rb");
			if (fp == NULL) {
				printf("%04d no file.\n", i);
				return -1;
			}

			if (stat(moji, &sb) == -1) {
				perror("stat");
				exit(EXIT_FAILURE);
			}
			sizeofdata = sb.st_size;
			total_sizeofdata += sizeofdata;
			fread(mem, sizeof(unsigned char), buf+sizeofdata, fp);
			memcpy(buf + sizeofheader, mem, sizeofdata);
			printf("file%d: filesize:%d bytes\n", i, sizeofdata+sizeofheader+2);
			fclose(fp);
		}
		sprintf(moji, "jpeg/%04d.jpg", i);
			FILE *fp_out = fopen(moji, "wb");
			fwrite(buf, sizeof(unsigned char), sizeofheader + sizeofdata + 2,
				fp_out);
		memcpy(buf + sizeofheader + sizeofdata, eof, 2);
		fclose(fp_out);
	}

    printf("\ndone.\n");
    fclose(fp_header);

    return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
// #define debug
//////////////////////////////////////////////////////////
// エンコードbitstreamをヘッダと合成
//////////////////////////////////////////////////////////
static const unsigned char inputname[] = "input/duchshund720.raw";
static const unsigned char outputname[] = "output/duchshund720_readmemh.txt";

static const unsigned char headername[]="headerout.bin";

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
    unsigned char mem[50*1024], header[1024], buf[50*1024];
    unsigned char eof[2]={0xFF, 0x09};

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

    for(int i=0; i<90; i++){
        char moji[32];
        sprintf(moji, "bitstream/%02d.bin", i);
        fp = fopen(moji, "rb");
        if (fp == NULL) {
            printf("%02d no file.\n", i);
            return -1;
        }

        if (stat(moji, &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        sizeofdata = sb.st_size;
        fread(mem, sizeof(unsigned char), sizeofdata, fp);

        // memcpy(buf, header, sizeofheader);
        // for (int k = 0; k < sizeofheader; k++) {
        //     printf("%02x ", buf[k]);
        //     if ((k + 1) % 0xF == 0) {
        //         printf("\n");
        //     }
        // }
        // printf("\n\n");

        
        memcpy(buf, header, sizeofheader);
        memcpy(buf + sizeofheader, mem, sizeofdata);
        memcpy(buf + sizeofheader + sizeofdata, eof, 2);

        sprintf(moji, "jpeg/%02d.jpg", i);
        FILE *fp_out = fopen(moji, "wb");
        fwrite(buf, sizeof(unsigned char), sizeofheader + sizeofdata + 2,
               fp_out);

        
        printf("file%d: filesize:%d bytes\n", i, sizeofdata+sizeofheader+2);
        
        fclose(fp);
        fclose(fp_out);
    }
    printf("\ndone.\n");
    fclose(fp_header);

    return 0;
}
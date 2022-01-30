#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
// #define debug
//////////////////////////////////////////////////////////
// エンコードbitstreamをヘッダと合成
//////////////////////////////////////////////////////////
static const unsigned char inputname[] = "input/duchshund720.raw";
static const unsigned char outputname[] = "output/duchshund720_readmemh.txt";

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
    unsigned char mem[50*1024];
    FILE *fp;
    char moji[32];

    // for(int i=0; i<90; i++){
    //     sprintf(moji, "%d.bin", i);
    //     fp[i] = fopen(moji, "rb");
    //     if (fp == NULL) {
    //         printf("%d no file.\n",i);
    //         return -1;
    //     }
    //     int filesize = GetFileSize(moji);
    //     fread(mem[i], sizeof(unsigned char), filesize, fp[i]);
    // }

    int i = 0;
    sprintf(moji, "%02d.bin", i);
    fp = fopen(moji, "rb");
    if (fp == NULL) {
        printf("%d no file.\n", i);
        return -1;
    }

    struct stat sb;
    if (stat(moji, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("filesize:%d\n", (int)sb.st_size);
    fread(mem, sizeof(unsigned char), sb.st_size, fp);

    for(int k=0; k<sb.st_size; k++){
        printf("%02x ", mem[k]);
        if((k+1)%0xF==0){
            printf("\n");
        }
    }
    

    printf("\ndone.\n");
    fclose(fp);
    for(int j=0; j<90; j++){
        
    }
    return 0;
}
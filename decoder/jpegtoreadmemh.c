#include <stdio.h>
#include <string.h>
//////////////////////////////////////////////////////////
// JPEGデータをreadmemh用に32bitで一行ずつテキストの16進数に変換する
// テストベンチ検証用データ準備
//////////////////////////////////////////////////////////

static const unsigned char inputname[] = "0001.jpg";
static const unsigned char outputname[] = "out_readmemh.txt";

#define memsize (500 * 1000) //500KByte

// #define debug

int main(void){
    unsigned char mem[memsize];
    FILE *infp = NULL;
    FILE *outfp = NULL;
    infp = fopen(inputname, "rb");
    outfp = fopen(outputname, "w");

    if (infp == NULL || outfp == NULL) {
        printf("no file.\n");
        return -1;
    }

    int flg = 1;
    while (flg)
    {
        unsigned char buf[4];
        memset(buf, 0, 4);
        int read_len = fread(buf, 1, 4, infp);
        if(read_len < 4){
            if(feof(infp)){
                #ifdef debug
                printf("len=%d eof detected\n", read_len);
                #endif
                flg = 0;
            } else {
                #ifdef debug
                printf("len=%d else\n", read_len);
                #endif
            }
        }
        int *data = buf;
        #ifdef debug
        printf("0x%08x\n",*data);
        #endif
        fprintf(outfp, "%08x\n", *data);
    }

    fclose(infp);
    fclose(outfp);

    //fread(mem, sizeof((unsigned char), sizeof(mem)/sizeof(mem[0], infp)));

}
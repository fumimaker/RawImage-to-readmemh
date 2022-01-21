#include <stdio.h>
#define sizeofdata 1280*720
int main(){
    FILE *outfp = NULL;
    outfp = fopen("renzoku.txt", "wb");
    unsigned char data[sizeofdata*3];
    unsigned char cnt=0;
    for(int i=0; i<sizeofdata; i++){
        data[i * 3 + 0] = (unsigned char)(i & 0xFF);
        data[i * 3 + 1] = (unsigned char)((i >> 8) & 0xFF);
        data[i * 3 + 2] = (unsigned char)((i >> 16) & 0xFF);
        cnt++;
    }
    fwrite(&data, sizeof(data), 1, outfp);
    fclose(outfp);

    return 0;
}
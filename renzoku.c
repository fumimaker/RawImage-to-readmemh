#include <stdio.h>
#define sizeofdata 1280*720
unsigned int cnt = 0;//0x0e0fff+1;

int main(){
    FILE *outfp = NULL;
    outfp = fopen("renzoku.bin", "wb");
    unsigned char data[sizeofdata*3];

    for(int i=0; i<sizeofdata; i++){
        data[i * 3 + 0] = (unsigned char)(cnt & 0xFF);
        data[i * 3 + 1] = (unsigned char)((cnt >> 8) & 0xFF);
        data[i * 3 + 2] = (unsigned char)((cnt >> 16) & 0xFF);
        cnt++;
    }
    fwrite(&data, sizeof(data), 1, outfp);
    fclose(outfp);

    return 0;
}
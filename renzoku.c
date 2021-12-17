#include <stdio.h>

int main(){
    FILE *outfp = NULL;
    outfp = fopen("renzoku.txt", "wb");
    unsigned char data[256];
    for(int i=0; i<256; i++){
        data[i] = i;
    }
    fwrite(&data, sizeof(data), 1, outfp);
    fclose(outfp);

    return 0;
}
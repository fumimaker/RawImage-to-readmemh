#include <stdio.h>

int main(){
    FILE *outfp = NULL;
    outfp = fopen("renzoku.txt", "wb");
    unsigned char data[256*3];
    for(int i=0; i<256; i++){
        for(int j=0; j<3; j++){
            data[i*3+j] = i;
        }
    }
    fwrite(&data, sizeof(data), 1, outfp);
    fclose(outfp);

    return 0;
}
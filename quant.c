#include <stdio.h>
#include <stdint.h>

#define QUALITY 49

const uint8_t DefaultQuantLuminance[8 * 8] =
    {16, 11, 10, 16, 24, 40, 51, 61,
     12, 12, 14, 19, 26, 58, 60, 55,
     14, 13, 16, 24, 40, 57, 69, 56,
     14, 17, 22, 29, 51, 87, 80, 62,
     18, 22, 37, 56, 68, 109, 103, 77,
     24, 35, 55, 64, 81, 104, 113, 92,
     49, 64, 78, 87, 103, 121, 120, 101,
     72, 92, 95, 98, 112, 100, 103, 99};
const uint8_t DefaultQuantChrominance[8 * 8] =
    {17, 18, 24, 47, 99, 99, 99, 99,
     18, 21, 26, 66, 99, 99, 99, 99,
     24, 26, 56, 99, 99, 99, 99, 99,
     47, 66, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99};
const uint8_t ZigZagInv[8 * 8] =
    {0, 1, 8, 16, 9, 2, 3, 10,        // ZigZag[] =  0, 1, 5, 6,14,15,27,28,
     17, 24, 32, 25, 18, 11, 4, 5,    //             2, 4, 7,13,16,26,29,42,
     12, 19, 26, 33, 40, 48, 41, 34,  //             3, 8,12,17,25,30,41,43,
     27, 20, 13, 6, 7, 14, 21, 28,    //             9,11,18,24,31,40,44,53,
     35, 42, 49, 56, 57, 50, 43, 36,  //            10,19,23,32,39,45,52,54,
     29, 22, 15, 23, 30, 37, 44, 51,  //            20,22,33,38,46,51,55,60,
     58, 59, 52, 45, 38, 31, 39, 46,  //            21,34,37,47,50,56,59,61,
     53, 60, 61, 54, 47, 55, 62, 63}; //            35,36,48,49,57,58,62,63

uint8_t quantLuminance[8 * 8];
uint8_t quantChrominance[8 * 8];

uint8_t clamp(int, int, int);

uint8_t clamp(int num, int min, int max){
    if (num <= min){
        return (uint8_t)min;
    }
    if (num >= max){
        return (uint8_t)max;
    }
    return (uint8_t)num;
}

int main(void){
    printf("Hello, World!\n");
    // uint8_t quality=QUALITY;
    //quality = quality < 50 ? 5000 / quality : 200 - quality * 2;
    for (int i = 0; i < 8 * 8; i++) {
        float lum;
        float chr;
        // uint8_t lum = (DefaultQuantLuminance[i] * quality + 50) / 100;
        // uint8_t chr = (DefaultQuantChrominance[i] * quality + 50) / 100;
        if (QUALITY < 50) {
			lum = (int)DefaultQuantLuminance[i] * 50.0 / QUALITY;
			chr = (int)DefaultQuantChrominance[i] * 50.0 / QUALITY;
            // quantLuminance[i] = clamp((int)DefaultQuantLuminance[i] * 50 / QUALITY, 1, 255);
            // quantChrominance[i] = clamp((int)DefaultQuantChrominance[i] * 50 / QUALITY, 1, 255);
        } else {
            // quantLuminance[i] = clamp(
                // (100 - QUALITY) / 50.0 * DefaultQuantLuminance[i], 1, 255);
            // quantChrominance[i] = clamp(
                // (100 - QUALITY) / 50.0 * DefaultQuantChrominance[i], 1, 255);
            lum = (int)DefaultQuantLuminance[i] * (100 - QUALITY) / 50.0;
            chr = (int)DefaultQuantChrominance[i] * (100 - QUALITY) / 50.0;
        }
        quantLuminance[i] = clamp((uint8_t) lum, 1, 255);
        quantChrominance[i] = clamp((uint8_t) chr, 1, 255);
    }
    printf("============Y Value============\n");
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printf("parameter Q%d_%d = 8'h%02x;", i+1, j+1, quantLuminance[i * 8 + j]);
            printf("\n");
        }
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //printf("%02x ",quantLuminance[i * 8 + j]);
			printf("%4d",quantLuminance[i * 8 + j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("============CbCr Value============\n");
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            //printf("%x ", quantChrominance[i*8+j]);
            printf("parameter Q%d_%d = 8'h%02x;", i+1, j+1, quantChrominance[i * 8 + j]);
            printf("\n");
        }
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // printf("%02x ", quantChrominance[i * 8 + j]);
			printf("%4d", quantChrominance[i * 8 + j]);
        }
        printf("\n");
    }

    printf("\n");

    printf("Target Quality=%d, end.\n", QUALITY);
    return 0;
}
#include <stdio.h>
#include <stdint.h>

int quality = 1;
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

int clamp(int, int, int);

int clamp(int num, int min, int max){
    if (num <= min){
        return min;
    }
    if (num >= max){
        return max;
    }
    return num;
}

int main(void){
    printf("Hello, World!\n");

    quality = quality < 50 ? 5000 / quality : 200 - quality * 2;
    for (int i = 0; i < 8 * 8; i++)
    {
        uint8_t lum = (DefaultQuantLuminance[ZigZagInv[i]] * quality + 50) / 100;
        uint8_t chr = (DefaultQuantChrominance[ZigZagInv[i]] * quality + 50) / 100;
        quantLuminance[i] = clamp(lum, 1, 255);
        quantChrominance[i] = clamp(chr, 1, 255);
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printf("%d ", quantLuminance[i*8+j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            printf("%d ", quantChrominance[i*8+j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");

    printf("end.\n");
    return 0;
}
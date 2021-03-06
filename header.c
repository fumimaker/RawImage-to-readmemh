#include <stdio.h>
#include <stdint.h>

#define HEIGHT 720//720
#define WIDTH  1280//1280
#define QUALITY 30


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


uint8_t HeaderJfif[2 + 2 + 16] = {0xFF, 0xD8, 0xFF, 0xE0, 0, 16, 'J',
'F', 'I', 'F', 0, 1, 1, 0, 0, 1, 0, 1, 0, 0};

uint8_t quantLuminance[8 * 8];
uint8_t quantChrominance[8 * 8];

const unsigned char EOI []={0xFF,0xD9};
uint8_t Spectral[3] = {0, 0x3f, 0};


const char outputname[] = "Q30headerout.bin";
FILE *outfp;

unsigned char DHT_Table[432] = {
    0xFF, 0xC4, 0x00, 0x1F, 0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xC4, 0x00,
    0xB5, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05,
    0x04, 0x04, 0x00, 0x00, 0x01, 0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11,
    0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71,
    0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52,
    0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53,
    0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83,
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
    0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
    0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8,
    0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA,
    0xFF, 0xC4, 0x00, 0x1F, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xC4, 0x00,
    0xB5, 0x11, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05,
    0x04, 0x04, 0x00, 0x00, 0x01, 0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11,
    0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71,
    0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52,
    0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18,
    0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53,
    0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83,
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
    0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
    0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8,
    0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA};

uint8_t clamp(int, int, int);

void writeMarker(uint8_t, uint16_t);
void writeData(uint8_t);

void writeMarker(uint8_t id, uint16_t length){
    writeData(0xFF);
    writeData(id);
    writeData((uint8_t)(length >> 8));
    writeData((uint8_t)(length&0xFF));
}

void writeData(uint8_t data){
    fprintf(outfp, "%c", data);
}

void writeArray(uint8_t *data, uint16_t length){
    printf("???????????????%d", length);
    uint16_t i;
    for(i = 0; i < length; i++){
        writeData(data[i]);
    }
    printf(" ?????????????????????%d\n", i);
}

uint8_t clamp(int num, int min, int max) {
    if (num <= min) {
        return min;
    }
    if (num >= max) {
        return max;
    }
    return num;
}

int main(void) {
    outfp = fopen(outputname, "w");
    if (outfp == NULL) {
        printf("no file.\n");
        return -1;
    }
    uint8_t quality = QUALITY;
    quality = quality < 50 ? 5000 / quality : 200 - quality * 2;
    for (int i = 0; i < 8 * 8; i++) {
        uint8_t lum = (DefaultQuantLuminance[i] * quality + 50) / 100;
        uint8_t chr = (DefaultQuantChrominance[i] * quality + 50) / 100;
        quantLuminance[i] = clamp(lum, 1, 255);
        quantChrominance[i] = clamp(chr, 1, 255);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%02x ", quantLuminance[i * 8 + j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%02x ", quantChrominance[i * 8 + j]);
        }
        printf("\n");
    }

    printf("\n");

    writeArray(HeaderJfif, sizeof(HeaderJfif));

    writeMarker(0xDB, 64 + 3);
    writeData(0);
    writeArray(quantLuminance, sizeof(quantLuminance));
    writeMarker(0xDB, 64 + 3);
    writeData(1);
    writeArray(quantChrominance, sizeof(quantChrominance));

    writeMarker(0xC0, 2 + 6 + 3 * 3);
    writeData(8);
    writeData(HEIGHT >> 8);
    writeData(HEIGHT & 0xFF);
    writeData(WIDTH >> 8);
    writeData(WIDTH & 0xFF);
    writeData(3);
    for (int i = 1; i <= 3; i++) {
        writeData(i);
        writeData(0x11);
        if (i == 1) {
            writeData(0x00);
        } else {
            writeData(0x01);
        }
    }

    writeArray(DHT_Table, sizeof(DHT_Table));

    writeMarker(0xDA, 2 + 1 + 2 * 3 + 3);
    writeData(3);
    for (size_t i = 1; i <= 3; i++) {
        writeData(i);
        if (i == 1) {
            writeData(0x00);
        } else {
            writeData(0x11);
        }
    }
    writeArray(Spectral, sizeof(Spectral));

    printf("\nHEIGHT:%d, WIDTH:%d\n", HEIGHT, WIDTH);
    printf("quality:%d\n", QUALITY);
    printf("output end.\n\n");

    unsigned char str[256];
    sprintf(str, "output file = %s \n", outputname);
    printf("%s", str);

    fclose(outfp);
    return 0;
}
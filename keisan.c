#include <stdio.h>
#include <stdint.h>
uint8_t clamp(int num, int min, int max) {
    if (num <= min) {
        return (uint8_t)min;
    }
    if (num >= max) {
        return (uint8_t)max;
    }
    return (uint8_t)num;
}

int main() {
    for (int i = 0; i < 1280*8; i++){
        if((i)%10==0){
            printf("%d true\n",i);
        }
    }
    uint32_t data = 0x7d4fe688;
    uint32_t cnt = 0x1e;

    uint32_t masked_data = data & (1 << cnt) - 1;
    printf("%x\n",masked_data);

    int addr = 0;
    for (int block_x = 0; block_x < 160; block_x++) {
        for (int macro_y = 0; macro_y < 8; macro_y++) {
            for (int macro_x=0; macro_x < 8; macro_x++){
                addr = ((macro_x + block_x*8) + (1280*macro_y));
                printf("%04x ", addr);
            }
            printf("\n");
        }
        printf("\n");
    }

    for(int i=4; i<0x45; i++){
        printf("%d, %d\n", (i - 4) % 8, (i - 4) >> 3);
    }

    uint64_t data_in = 0x112345678;
    uint32_t data32 = data_in & 0xFFFFFFFF;
    uint32_t last = (data_in & 0x100000000) > 0 ? 1 : 0;
    printf("data:%x last:%x\n", data32, last);

    int QUALITY = 95;
    float a = clamp(((100 - QUALITY) / 50.0 * 50), 1, 255);
    float b = clamp((float)((100 - QUALITY) / 50.0 * 50) + 0.5, 1, 255);
    printf("%f %f", a, b);

    return 0;
}



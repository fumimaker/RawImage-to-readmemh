#include <stdio.h>
#include <stdint.h>
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
    return 0;
}



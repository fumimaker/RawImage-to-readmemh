#include "stdio.h"

int main() {
    for (int i = 0; i < 1280*720; i++){
        if((i+1)%1280==0){
            printf("%d true\n",i);
        }
    }
    return 0;
}
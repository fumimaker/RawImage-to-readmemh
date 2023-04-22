#include <stdio.h>

int main (void) {
	for (int y=1; y<=8; y++){
		for(int x=1; x<=8; x++){
			printf("parameter QQ%d_%d	= (Q%d_%d==8'h01)	? (4096/Q%d_%d) : (4096/Q%d_%d)+1;\n", y,x,y,x,y,x,y,x);
		}
	}
}
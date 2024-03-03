#include <stdio.h>
#include <stdlib.h>

// 標準の輝度量子化テーブル
int luminance_quant_table[8][8] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68, 109, 103, 77},
    {24, 35, 55, 64, 81, 104, 113, 92},
    {49, 64, 78, 87, 103, 121, 120, 101},
    {72, 92, 95, 98, 112, 100, 103, 99}
};

// 標準の色差量子化テーブル
int chrominance_quant_table[8][8] = {
    {17, 18, 24, 47, 99, 99, 99, 99},
    {18, 21, 26, 66, 99, 99, 99, 99},
    {24, 26, 56, 99, 99, 99, 99, 99},
    {47, 66, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99},
    {99, 99, 99, 99, 99, 99, 99, 99}
};

// 量子化テーブルを調整する関数
void adjust_quant_table(int quant_table[8][8], int quality) {
    int i, j;
    float scale_factor;

    if (quality < 50)
        scale_factor = 5000.0 / quality;
    else
        scale_factor = 200.0 - 2 * quality;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            int temp = (int)((quant_table[i][j] * scale_factor + 50) / 100);
            // 量子化係数は1から255の範囲に制限
            if (temp <= 0) temp = 1;
            if (temp > 255) temp = 255;
            quant_table[i][j] = temp;
        }
    }
}

// テーブルの表示関数
void print_quant_table(int quant_table[8][8], char* table_name) {
    printf("Adjusted %s Quantization Table:\n", table_name);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%4d", quant_table[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int quality;
    printf("Enter the quality factor (1-100): ");
    scanf("%d", &quality);

    if (quality < 1 || quality > 100) {
        printf("Quality factor must be between 1 and 100.\n");
        return 1;
    }

    adjust_quant_table(luminance_quant_table, quality);
    adjust_quant_table(chrominance_quant_table, quality);

    // 輝度量子化テーブルと色差量子化テーブルの両方を表示
    print_quant_table(luminance_quant_table, "Luminance");
    print_quant_table(chrominance_quant_table, "Chrominance");

    return 0;
}

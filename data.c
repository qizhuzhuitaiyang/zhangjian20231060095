#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_data(int n, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        exit(1);
    }
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int weight = rand() % 100 + 1; // 1~100
        double value = (rand() % 901 + 100) + ((double)(rand() % 100) / 100.0);
        fprintf(fp, "%d %.2f\n", weight, value);
    }
    fclose(fp);
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 20, 30, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 40000, 80000, 160000, 320000};
    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        char filename[50];
        sprintf(filename, "data_%d.txt", sizes[i]);
        generate_data(sizes[i], filename);
        printf("Generated file: %s\n", filename);
    }
    return 0;
}

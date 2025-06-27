#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_N 100000
#define MAX_C 1000000

typedef struct {
    int w;
    double v;
    double ratio;
} Item;

Item items[MAX_N];
int n;
int C;

// 通用读入
void load_data(char* filename) {
    FILE* fp = fopen(filename, "r");
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %lf", &items[i].w, &items[i].v);
        items[i].ratio = items[i].v / items[i].w;
    }
    fclose(fp);
}

// 蛮力法
double brute_force() {
    double max_value = 0;
    long long total = 1LL << n;
    for (long long i = 0; i < total; i++) {
        int total_weight = 0;
        double total_value = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1LL << j)) {
                total_weight += items[j].w;
                total_value += items[j].v;
            }
        }
        if (total_weight <= C && total_value > max_value)
            max_value = total_value;
    }
    return max_value;
}

// 动态规划法
double dp() {
    double *dp_arr = (double*)calloc(C + 1, sizeof(double));
    for (int i = 0; i < n; i++) {
        for (int j = C; j >= items[i].w; j--) {
            if (dp_arr[j] < dp_arr[j - items[i].w] + items[i].v)
                dp_arr[j] = dp_arr[j - items[i].w] + items[i].v;
        }
    }
    double res = dp_arr[C];
    free(dp_arr);
    return res;
}

// 贪心法
int cmp(const void *a, const void *b) {
    double r1 = ((Item*)a)->ratio;
    double r2 = ((Item*)b)->ratio;
    return (r2 > r1) - (r2 < r1);
}

double greedy() {
    qsort(items, n, sizeof(Item), cmp);
    int total_weight = 0;
    double total_value = 0;
    for (int i = 0; i < n; i++) {
        if (total_weight + items[i].w <= C) {
            total_weight += items[i].w;
            total_value += items[i].v;
        }
    }
    return total_value;
}

// 回溯法
double best = 0;
void dfs(int i, int cw, double cv) {
    if (cw > C) return;
    if (i == n) {
        if (cv > best) best = cv;
        return;
    }
    dfs(i + 1, cw + items[i].w, cv + items[i].v);
    dfs(i + 1, cw, cv);
}

double backtrack() {
    best = 0;
    dfs(0, 0, 0);
    return best;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("用法: %s [算法] [数据文件] [容量C] [输出CSV]\n", argv[0]);
        return 1;
    }

    char* algo = argv[1];
    load_data(argv[2]);
    C = atoi(argv[3]);
    FILE* fout = fopen(argv[4], "a");

    double result = 0;
    clock_t start = clock();

    if (strcmp(algo, "brute") == 0) {
        if (n > 30) { printf("brute n太大\n"); return 1; }
        result = brute_force();
    }
    else if (strcmp(algo, "dp") == 0) {
        result = dp();
    }
    else if (strcmp(algo, "greedy") == 0) {
        result = greedy();
    }
    else if (strcmp(algo, "backtrack") == 0) {
        if (n > 30) { printf("backtrack n太大\n"); return 1; }
        result = backtrack();
    } else {
        printf("未知算法\n"); return 1;
    }

    clock_t end = clock();
    double time_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

    fprintf(fout, "%s,%d,%d,%.2f,%.2f\n", algo, n, C, result, time_ms);
    fclose(fout);
    return 0;
}
    
#include <cstdlib>
#include <ctime>
#include <cstdio>

int main() {
    srand(time(0)); // 为rand()函数设置种子
    int w = rand() % 10 + 2; // 随机生成操作个数，至少为2以保证有重置矩阵操作
    printf("%d\n", w);

    // 第一个操作一定是重置矩阵
    int n = rand() % 10 + 1, m = rand() % 10 + 1; // 随机生成行数和列数
    printf("1\n%d %d\n", n, m);
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < m; ++k) {
            printf("%d ", rand() % 100); // 随机生成矩阵元素
        }
        printf("\n");
    }

    for (int i = 1; i < w; ++i) { // 对于剩余的操作
        int op = rand() % 5 + 1; // 随机生成操作类型
        if (op == 1) { // 重置矩阵
            int n = rand() % 10 + 1, m = rand() % 10 + 1; // 随机生成行数和列数
            printf("1\n%d %d\n", n, m);
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    printf("%d ", rand() % 100); // 随机生成矩阵元素
                }
                printf("\n");
            }
        }
        else if (op == 2 || op == 3) { // 矩阵乘法或加法
            int n = rand() % 10 + 1, m = rand() % 10 + 1, t = rand() % (n * m) + 1; // 随机生成行数、列数和非零元素个数
            printf("%d\n%d %d\n%d\n", op, n, m, t);
            for (int j = 0; j < t; ++j) {
                int x = rand() % n + 1, y = rand() % m + 1, v = rand() % 100; // 随机生成非零元素的位置和值
                printf("%d %d %d\n", x, y, v);
            }
        }
        else if (op == 4 || op == 5) { // 输出操作或转置操作
            printf("%d\n", op);
        }
    }
    return 0;
}

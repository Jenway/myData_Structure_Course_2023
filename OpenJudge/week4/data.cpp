#include <cstdlib>
#include <ctime>
#include <cstdio>

int main() {
    srand(time(0)); // Ϊrand()������������
    int w = rand() % 10 + 2; // ������ɲ�������������Ϊ2�Ա�֤�����þ������
    printf("%d\n", w);

    // ��һ������һ�������þ���
    int n = rand() % 10 + 1, m = rand() % 10 + 1; // �����������������
    printf("1\n%d %d\n", n, m);
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < m; ++k) {
            printf("%d ", rand() % 100); // ������ɾ���Ԫ��
        }
        printf("\n");
    }

    for (int i = 1; i < w; ++i) { // ����ʣ��Ĳ���
        int op = rand() % 5 + 1; // ������ɲ�������
        if (op == 1) { // ���þ���
            int n = rand() % 10 + 1, m = rand() % 10 + 1; // �����������������
            printf("1\n%d %d\n", n, m);
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    printf("%d ", rand() % 100); // ������ɾ���Ԫ��
                }
                printf("\n");
            }
        }
        else if (op == 2 || op == 3) { // ����˷���ӷ�
            int n = rand() % 10 + 1, m = rand() % 10 + 1, t = rand() % (n * m) + 1; // ������������������ͷ���Ԫ�ظ���
            printf("%d\n%d %d\n%d\n", op, n, m, t);
            for (int j = 0; j < t; ++j) {
                int x = rand() % n + 1, y = rand() % m + 1, v = rand() % 100; // ������ɷ���Ԫ�ص�λ�ú�ֵ
                printf("%d %d %d\n", x, y, v);
            }
        }
        else if (op == 4 || op == 5) { // ���������ת�ò���
            printf("%d\n", op);
        }
    }
    return 0;
}

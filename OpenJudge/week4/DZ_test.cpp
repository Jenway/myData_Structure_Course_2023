#include <cstdio>
#include <cstdlib>
#include <ctime>


int main()
{
    for (int i = 1; i <= 10000; ++i) { // 进行10000次对拍
        system("data.exe > in.txt"); // 运行数据生成器并将输出重定向到in.txt
        system("problem5.exe < in.txt > out1.txt"); // 运行正确的程序并将输出重定向到out1.txt
        system("DZ_solution_problem5.exe < in.txt > out2.txt"); // 运行你的程序并将输出重定向到out2.txt
        if (system("fc out1.txt out2.txt")) { // 比较两个输出文件
            printf("Wrong Answer on test %d\n", i);
            system("type in.txt"); // 打印输入文件
            break;
        }
    }
    return 0;
}

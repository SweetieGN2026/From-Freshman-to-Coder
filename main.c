#include <stdio.h>
double fact(int n)
{
    if(n == 1)
        return 1;
    return fact(n-1) * n;
}
double sum(int n)
{
    if(n == 1)
        return 1;
    return sum(n-1) + fact(n);
}
int main()
{
    printf("%.0f\n", sum(20));
    return 0;
}//阶乘  递归模式
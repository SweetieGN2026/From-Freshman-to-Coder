#include <stdio.h>
//n代表是第几个  a代表前一个  b代表当前
double fast(int n, double a, double b) {
    if (n == 1)
        return a;
    return fast(n-1, b, a + b);//已经算了一次 这个规律前提是 斐波那契
}
double sum(int n, double s) {
    if (n == 0)
        return s;
    return sum(n-1, s + fast(n, 2.0, 3.0/2.0));//同理  s代表和  s + fast(n, 2.0, 3.0/2.0）这个是  前n-1和与第n项
}

int main() {
    printf("%.30f\n", sum(200, 0.0));
    return 0;
}
//plus
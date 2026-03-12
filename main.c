#include <stdio.h>
int main() {
    int a, n;
    long long sum = 0, numbers = 0;
    printf("输入数字 和项数：");
    scanf("%d %d", &a, &n);
    for (int i = 0; i < n; i++) {
        numbers = numbers * 10 + a;
        sum += numbers;
    }
    printf("s = %lld\n", sum);
    return 0;
}
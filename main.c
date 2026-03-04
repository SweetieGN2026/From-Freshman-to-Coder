#include <stdio.h>
void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void sort_three(int *a, int *b, int *c) {
    if (*a > *b) swap(a, b);
    if (*a > *c) swap(a, c);
    if (*b > *c) swap(b, c);
}//因为默认位置是abc  则输出也是对应位置xyz
int main() {
    int x, y, z;
    printf("请输入三个整数：");
    scanf("%d %d %d", &x, &y, &z);
    sort_three(&x, &y, &z);
    printf("从小到大：%d %d %d\n", x, y, z);
    return 0;
}
//比较大小  指针
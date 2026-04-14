#include <stdio.h>


#define MAXN 10005
int a[MAXN];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int ans = 0;
    for (int L = 0; L < n; L++) {
        int min_val = a[L];  //其实直接写一个很大的数字也可以 但是遍历循环更安全
        for (int R = L; R < n; R++) {
            if (a[R] < min_val) {
                min_val = a[R];
            }

            int len = R - L + 1;
            int now = len * min_val;

            if (now > ans) {
                ans = now;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
/*给定一个长度为 n 的序列 Ai。你要选一段连续区间 [L,R]，计算：(R−L+1)×min(AL,AL+1,…,AR)求这个值的最大值。*/
/*枚举每一个左端点 L
从 L 开始，R 不断向右扩展
一边扩展，一边维护当前区间的最小值
每扩展一步，计算 长度 × 最小值
全程记录最大的结果*/
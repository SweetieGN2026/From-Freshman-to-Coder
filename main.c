#include <stdio.h>
#define MAX 1005

int books[MAX];
int n, q;//书与读者
int mach(int book,int len,int code) {
    int   mod=1;
    for (int i = 1; i <= len; i++) {
        mod *=10;
    }
    return book % mod == code;;
}
int main() {
    scanf("%d %d",&n,&q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &books[i]);
    }

    while (q--) {
        int len;int code;
        int minNum = 99999;

        scanf("%d %d",&len,&code);
        for (int i = 0; i < n; i++) {
            if (mach(books[i], len, code)) {
                if (minNum >books[i]) {
                    minNum = books[i];
                }
            }
        }
        if (minNum == 99999) {
            printf("-1\n");
        }
        else {
            printf("%d\n", minNum);
        }
    }
    return 0;

}
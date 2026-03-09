#include <stdio.h>
#include <math.h>
int main() {
    int n, i;
    int goal;
    printf("素数有：\n");
    int cont=0;
    for (n = 101; n <= 200; n++) {
        int root = sqrt(n);//数学方法  很方便 不需要一直循环
        goal = 1;
        for (i = 2; i <= root; i++) {
            if (n % i == 0) {
                goal = 0;
                break;
            }
        }
        if (goal == 1) {
            cont++;
            printf("%d  ",n);

        }
    }
    printf("\n");
    printf("%d  ",cont);
    return 0;
}
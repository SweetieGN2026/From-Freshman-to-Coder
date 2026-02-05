#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char *guess[] = {"", "石头", "剪刀", "布"};
    int player, computer;
    srand((unsigned int)time(NULL)); // 随机数种子，保证电脑出拳不重复
    computer = rand() % 3 + 1;       // 简单的数学逻辑 如果有四种可能就除以4
    printf("石头剪刀布：1=石头 2=剪刀 3=布\n请出拳：");
    scanf("%d", &player);
    printf("你出：%s  电脑出：%s\n", guess[player], guess[computer]);
    if (player == computer) {
        printf("平局！\n");
    } else if ((player==1&&computer==2) || (player==2&&computer==3) || (player==3&&computer==1)) {
        printf("你赢了！\n");
    } else {
        printf("你输了！\n");
    }
    return 0;
}
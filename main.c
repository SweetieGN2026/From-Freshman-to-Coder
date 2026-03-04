#include <stdio.h>
int main() {
    int year, month,day;
    int days = 0;
    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    printf("请输入年 月 日：");
    scanf("%d %d %d", &year, &month, &day);
    int runyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (runyear!=0) {
        month_days[1] = 29;
    }
    for (int i = 0; i < month - 1; i++) {
        days += month_days[i];
    }
    days += day;
    printf("这一天是 %d年的第 %d 天\n",year, days);
    return 0;
}
//算时间的  但是没有考虑 随便数字
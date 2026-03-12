#include <stdio.h>
#include <ctype.h>//数据库
int main() {
    char c;
    int letters = 0, spaces = 0, numbers = 0, others = 0;

    printf("请输入一行字符：\n");
    while ((c = getchar()) != '\n' && c != EOF) {//输入的内容不仅仅是 换行 还有终止
        if (isalpha(c)) {
            letters++;
        } else if (c == ' ') {
            spaces++;
        } else if (isdigit(c)) {
            numbers++;
        } else {
            others++;
        }
    }
    printf("英文：%d\n", letters);
    printf("空格：%d\n", spaces);
    printf("数字：%d\n", numbers);
    printf("其他字符：%d\n", others);

    return 0;
}
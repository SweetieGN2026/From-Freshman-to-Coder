#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    char str1[100];
    scanf("%s", str);
    int len = strlen(str);
    int idx = 0;
    int i=0;
    while (i < len) {
        char c = str[i];
        int number = 0;
        while (i < len && str[i] == c) {
            number++;
            i++;
        }
        str1[idx++] = c;
        if (number > 1) {
            str1[idx++] =number+'0';
        }

    }
    str1[idx] = '\0';
    if (strlen(str1)< len) {
        printf("%s", str1);
    }
    else
        printf("no");
    return 0;
}/*实现一个算法来压缩一个字符串。压缩的要求如下：

需要判断压缩能不能节省空间，仅在压缩后字符串比原字符串长度更短时进行压缩。

压缩的格式是将连续相同字符替换为字符 + 数字形式，例如 "AAABCCDDDD" 变为 "A3BC2D4"。*/
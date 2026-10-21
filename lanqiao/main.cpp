#include <iostream>
using namespace std;
const int N=15;
int  dx[]={1,0,-1,0};
int  dy[]={0,1,0,-1};
int arr[N][N];
int main() {
    int n;
    cin>>n;
    int x=1,y=1;
    int num=1;
    int pos=0;
    while(num<=n*n) {
        arr[x][y]=num;
        int a=x+dx[pos],b=y+dy[pos];
        if (a<1 || b<1 || a>n || b>n||arr[a][b]) {
            pos=(pos+1)%4;
            a=x+dx[pos],b=y+dy[pos];
        }
        x=a,y=b;
        num++;
    }
    for(int i=1;i<=4;i++) {
        for(int j=1;j<=4;j++) {
            printf("%3d ",arr[i][j]);
        }
        cout<<endl;
    }
    return 0;
}


/*
【题目名称】螺旋矩阵（练习版）

题目描述
给定一个正整数 n，生成一个 n 阶顺时针螺旋方阵。
方阵从左上角(1,1)位置开始，数字从 1 开始，沿着顺时针方向一圈一圈向内填充。

输入格式
一行一个整数 n （ 1 ≤ n ≤ 10 ）

输出格式
输出 n 行，每行 n 个整数。
每个数字占3个字符宽度，数字之间空格分隔。

样例输入
4

样例输出
  1   2   3   4
 12  13  14   5
 11  16  15   6
 10   9   8   7
 */

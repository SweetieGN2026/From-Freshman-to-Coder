#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 5

typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
} Queue;
void initQueue(Queue *Q) {//初始化
    Q->front = 0;
    Q->rear = 0;
}
int isEmpty(Queue *Q) {//大部分 英文都是该部分意思
    return Q->front == Q->rear;
}


int isFull(Queue *Q) {
    return (Q->rear + 1) % MAXSIZE == Q->front;
}
int enqueue(Queue *Q, ElemType e) {
    if (isFull(Q)) {
        printf("队列已满 ");
        return 0;
    }
    Q->data[Q->rear] = e;       //入队是只能在rear
    Q->rear = (Q->rear + 1) % MAXSIZE; //循环
    return 1;//只是成功的标志
}
int dequeue(Queue *Q, ElemType *e) {
    if (isEmpty(Q)) {
        printf("队列为空\n");
        return 0;
    }
    *e = Q->data[Q->front];           //火车
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}
void printQueue(Queue *Q) {
    if (isEmpty(Q)) {
        printf("队列为空\n");
        return;
    }
    printf("队列内容: ");
    int i = Q->front;
    while (i != Q->rear) {
        printf("%d ", Q->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
}

// 主函数：测试
int main() {
    Queue q;
    initQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    printQueue(&q);
    // 尝试再入
    enqueue(&q, 50);

    ElemType x;
    dequeue(&q, &x); printf("出队: %d\n", x);
    dequeue(&q, &x); printf("出队: %d\n", x);

    printQueue(&q);
    // 再入队
    enqueue(&q, 60);
    enqueue(&q, 70); //循环链表的好处体现  不需要再次往前走

    printQueue(&q);
    return 0;
}
//“逊哥带你学计算机”    我跟着他学习
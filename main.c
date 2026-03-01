#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* prev;//首尾  不必多言
    struct Node* next;
} Node;
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return node;
}
void pushBack(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {//空就没有意义了
        *head = newNode;//新的变量储存
        return;
    }
    Node* cur = *head;//临时指针  让其一直 在头 然后移动
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;
    newNode->prev = cur;
}

void printList(Node* head) {
    Node* cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
int main() {
    Node* head = NULL;
    pushBack(&head, 1);
    pushBack(&head, 2);
    pushBack(&head, 3);
    printf("双向链表: ");
    printList(head); // 输出: 1 2 3
    return 0;
}
//尾插法
//“逊哥带你学计算机”    我跟着他学习
#include <stdio.h>
#include <stdlib.h>//调用标准库 相当于固定搭配
struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;
void reOrderList(ListNode *head) {//折段问题
    if (!head || !head->next) return;//判断是不是空
    ListNode *fast = head;
    ListNode *slow = head;
    while ((fast->next != NULL) && (fast->next->next != NULL)) {  // fast的下一个和下下个都不为空
        fast = fast->next->next;
        slow = slow->next;
    }
    // 分割链表
    ListNode *secondHalf = slow->next;
    slow->next = NULL;
    ListNode *prev = NULL;
    ListNode *current = secondHalf;
    while (current != NULL) {  // 当current不为NULL时继续循环  不是交换只是改变方向
        ListNode *nextTemp = current->next;
        current->next = prev;
        prev = current;
        current = nextTemp;
    }
    // prev现在指向反转后的头节点
    ListNode *first = head;
    ListNode *second = prev;
    while (second != NULL) {  // 当second不为NULL时继续循环
        ListNode *temp1 = first->next;
        ListNode *temp2 = second->next;
        first->next = second;
        second->next = temp1;
        first = temp1;
        second = temp2;
    }
}
void printList(ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));//开辟空间  基本操作  强制转换统一单位
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}
int main() {
    printf("原链表: ");//主要看你们
    ListNode *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);
    printList(head);
    reOrderList(head);
    printf("重排后: ");
    printList(head);

    return 0;
}
//代码跟着b站博主一起敲 “逊哥带你学计算机”
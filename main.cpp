#include<iostream>
#include<cstdio>   // printf函数头文件，补上消除警告
using namespace std;

// 数据元素类型定义
typedef int ElemType;
#define MaxSize 100
#define MAX_SIZE 100
#define SIZE 100

//==================== 普通二叉树定义 ====================
// 二叉链表结点结构
typedef  struct BiTNode {
    ElemType  data;                // 数据域
    struct BiTNode *lchild,*rchild;// 左、右孩子指针
}BiTNode,*BiTree;                 // BiTree等价 BiTNode*，代表根指针

// 访问结点操作：遍历中输出结点数据
void visit(BiTNode *p) {
    printf("%d ", p->data);
}

// 递归先序遍历：根 → 左子树 → 右子树
void  PreOrder(BiTree t) {
    if (t!=NULL) {         // 递归出口：空结点直接返回
        visit (t);         // 访问根结点
        PreOrder (t->lchild);  // 递归遍历左子树
        PreOrder(t->rchild);  // 递归遍历右子树
    }
}

// 递归中序遍历：左子树 → 根 → 右子树
void InOrder(BiTree t) {
    if (t!=NULL) {
        InOrder(t->lchild);
        visit(t);
        InOrder(t->rchild);
    }
}

// 递归后序遍历：左子树 → 右子树 → 根
void PostOrder (BiTree t) {
    if (t!=NULL) {
        PostOrder(t->lchild);
        PostOrder(t->rchild);
        visit (t);
    }
}

//==================== 顺序栈（存储二叉树结点指针） ====================
typedef struct {
    BiTNode* data[MaxSize];  // 栈数组，存放结点指针
    int top;                 // 栈顶下标，初始为-1代表空栈
} SqStack;

// 初始化栈
void InitStack(SqStack &S) {
    S.top = -1;
}

// 判断栈是否为空
bool IsEmpty(SqStack S) {
    if (S.top == -1)
        return true ;
    else
        return false;
}

// 入栈操作
bool Push(SqStack &S, BiTNode *p) {
    if (S.top == MaxSize - 1) // 判断栈满
        return false;
    S.data[++S.top] = p;      // 先top自增，存入元素
    return true;
}

// 出栈操作，弹出元素存入p
bool Pop(SqStack &S, BiTNode *&p) {
    if (IsEmpty(S)) return false;
    p = S.data[S.top--];      // 取出栈顶，top自减
    return true;
}

//==================== 二叉树 中序遍历【非递归实现】王道标准模板 ====================
void InOrder2(BiTree t) {
    SqStack S;
    InitStack(S);
    BiTree p=t;  // p遍历指针，初始指向根结点
    // 循环条件：p不为空 或者 栈不为空
    while (p!=NULL||IsEmpty(S)!=true) {
        if (p!=NULL) {
            Push(S,p);     // 当前结点入栈
            p=p->lchild;   // 不断向左深入
        }
        else{
            Pop(S,p);      // 左走到尽头，弹出栈结点
            visit(p);      // 访问结点
            p=p->rchild;   // 转向右子树
        }
    }
}

//==================== 中序线索二叉树 ====================
// 线索二叉树结点
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild ,*rchild;
    int ltag,rtag;
    // tag=0：指针指向真实孩子
    // tag=1：指针为线索（前驱/后继）
}ThreadNode,*ThreadTree;

// 递归完成二叉树中序线索化
// t：当前处理结点，pre：上一个访问的结点（前驱）
void InThread(ThreadTree &t,ThreadTree &pre) {
    if (t!=NULL) {
        InThread(t->lchild,pre); // 先线索化左子树

        // 当前结点左孩子为空，左指针作为前驱线索
        if (t->lchild==NULL) {
            t->lchild=pre;
            t->ltag=1;
        }
        // 前驱结点右孩子为空，右指针作为后继线索指向当前t
        if (pre!=NULL&&pre->rchild==NULL) {
            pre->rchild=t;
            pre->rtag=1;
        }

        pre=t; // 更新前驱为当前结点
        InThread(t->rchild,pre); // 线索化右子树
    }
}

// 创建中序线索二叉树入口函数
void CreateThread(ThreadTree t) {
    ThreadTree pre=NULL;
    if (t!=NULL) {
        InThread(t,pre);
        pre->rchild=NULL; // 中序最后一个结点无后继
        pre->rtag=1;
    }
}

// 查找中序线索二叉树的第一个结点（最左下结点）
ThreadTree FirstNode(ThreadTree t) {
    while (t->ltag!=1) { // 只要左指针是真实孩子，持续往左
        t=t->lchild;
    }
    return t;
}

//==================== 树的双亲表示法 ====================
typedef  struct {
    ElemType data;
    int parent;    // 父结点数组下标，-1代表根结点
}PTNode;

typedef struct {
    PTNode data[MAX_SIZE]; // 存放所有结点数组
    int n;                 // 当前树实际结点数量
}PTree;

//==================== 并查集实现 ====================
int US[SIZE]; // 并查集数组
/*
约定：
US[x] < 0：x是集合根，绝对值 = 集合结点数量
US[x] >= 0：US[x]代表x的父结点下标
*/

// 初始化并查集：每个元素自成集合
void Initial( int US[]){
    for (int i=0;i<SIZE;i++)
        US[i]=-1;
}

// Find：基础查找，无路径压缩，找到x所在集合根
int Find (int s[],int x) {
    while (s[x]>=0) { // 不断向上寻找父节点
        x=s[x];
    }
    return x;
}

// Union简单合并：直接将root1挂载到root2下（未优化，容易退化）
void Union (int s[],int root1,int root2) {
    if (root1==root2) // 同一集合无需合并
        return ;
    s[root1]=root2;
}

// Union2 加权合并（按集合大小合并，王道标准）
// 小树合并到大树，减少树高度
void Union2 (int s[],int root1,int root2) {
    if (root1==root2)
        return ;
    // root1集合更大
    if (s[root1]<s[root2]) {
        s[root1]+=s[root2]; // 更新集合大小
        s[root2]=root1;
    }
    else {
        s[root2]+=s[root1];
        s[root1]=root2;
    }
}

// Find2：【注意！原版代码路径压缩逻辑存在缺陷，保留你写法并标注】
// 迭代尝试路径压缩，该实现不完整，考场优先使用标准迭代/递归路径压缩
int Find2 (int s[],int x) {
    int root=x;
    // 第一步：查找根结点
    while (s[root]>=0) {
        root=s[root];
    }
    // 将沿途结点直接指向根（路径压缩）
    if (s[x]!=root) {
        int t=s[x];
        s[x]=root;
        x=t;
    }
    return root;
}

/*
手写代码范围：131 ~ 206
代码手写默写；注释辅助理解，考试答题无需抄写注释
【复习提醒】
1. 线索二叉树不要写错 ltag / rtag
2. 栈操作 ++top / top-- 区分清楚
3. 并查集区分普通合并、加权合并；区分有无路径压缩
4. 非递归中序遍历为408高频代码，务必熟练默写
*/
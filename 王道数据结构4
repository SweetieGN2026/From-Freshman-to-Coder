#include <stdio.h>

#define MaxVertexNum 100   //图最大顶点数
#define MaxSize 100        //队列最大容量
#define INF 9999999        //无穷大，代表两点之间没有边

typedef int EdgeType;       //边权的数据类型
typedef char VertexType;    //顶点存储的数据类型
typedef int ElemType;       //队列、栈存放元素类型，存放顶点下标

//==================== 邻接矩阵 MGraph 王道标准 ====================
/**
 * MGraph：邻接矩阵存储的图结构
 * vex[]：保存顶点数据；edge[][]：邻接矩阵，edge[i][j]代表i到j边的权
 * vexnum：当前顶点数量；arcnum：当前边/弧数量
 */
typedef struct {
    VertexType vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

//==================== 邻接表 Graph 王道标准 ====================
//边结点：保存邻接点下标，以及指向下一条边的指针
typedef struct ArcNode {
    int adjvex;                 //邻接顶点的数组下标
    struct ArcNode *nextarc;    //指向同顶点下一条边结点
} ArcNode;

//顶点结点：存放顶点数据，指向第一条边
typedef struct VNode {
    VertexType data;            //顶点本身的数据
    ArcNode *firstarc;          //指向该顶点第一条边结点
} VNode, AdjList[MaxVertexNum];

/**
 * Graph：邻接表整体图结构
 * vertices[] 顶点数组；vexnum顶点数；arcnum边数
 */
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} Graph;

//==================== 十字链表 OLGraph【有向图专用存储】====================
/**
 * ArcBox：十字链表的弧结点，专门存储有向图的一条弧 <tailvex,headvex>
 * tailvex：弧尾下标；headvex：弧头下标
 * tlink：指向同一个弧尾的下一条弧；hlink：指向同一个弧头的下一条弧
 */
typedef struct ArcBox {
    int tailvex;
    int headvex;
    struct ArcBox *tlink;
    struct ArcBox *hlink;
} ArcBox;

//顶点结点，firstin第一条入弧，firstout第一条出弧
typedef struct VexNode {
    VertexType data;
    ArcBox *firstin;
    ArcBox *firstout;
} VexNode;

typedef struct {
    VexNode xlist[MaxVertexNum];
    int vexnum, arcnum;
} OLGraph;

//==================== 邻接多重表 AMLGraph【无向图专用存储】====================
/**
 * EdgeBox：邻接多重表边结点，无向边(ivex,jvex)
 * ilink：依附ivex的下一条边；jlink：依附jvex的下一条边
 */
typedef struct EdgeBox {
    int ivex;
    int jvex;
    struct EdgeBox *ilink;
    struct EdgeBox *jlink;
} EdgeBox;

typedef struct VexNode_Multi {
    VertexType data;
    EdgeBox *firstedge; //顶点关联的第一条边
} VexNode_Multi;

typedef struct {
    VexNode_Multi xlist[MaxVertexNum];
    int vexnum, arcnum;
} AMLGraph;

bool visited[MaxVertexNum]; //全局访问标记数组，标记顶点是否已经被遍历过
int dist[MaxVertexNum];     //全局距离数组，BFS最短路径使用

//访问顶点，打印顶点下标，遍历算法的访问函数
void visit(int v) {
    printf("%d ", v);
}

//==================== 循环队列【王道原版，引用&】 ====================
/**
 * SqQueue：循环队列，用于BFS遍历
 * data[]队列存储数组；front队头下标；rear队尾下标
 * 牺牲一个存储单元区分队满和队空：(rear+1)%MaxSize == front代表队满
 */
typedef struct {
    ElemType data[MaxSize];
    int front;
    int rear;
} SqQueue;

//初始化循环队列，队头队尾全部置0
void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

//判断队列是否为空，front等于rear代表空
bool IsEmpty(SqQueue &Q) {
    return Q.front == Q.rear;
}

//入队；x为入队元素；返回true入队成功，false队列满
bool EnQueue(SqQueue &Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize; //队尾向后移动，取模实现循环
    return true;
}

//出队；x接收队头元素；true出队成功，false队列为空
bool DeQueue(SqQueue &Q, ElemType &x) {
    if (IsEmpty(Q))
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize; //队头向后移动，取模循环
    return true;
}

//==================== 邻接表：BFS 单个连通分量 ====================
/**
 * BFS：从顶点i出发广度优先遍历，**只遍历i所在连通分量**
 * 注意：不会重置visited数组，外层调用函数负责清空visited
 */
void BFS(Graph G, int i) {
    visit(i);               //访问起点i
    SqQueue Q;
    InitQueue(Q);
    visited[i] = true;      //标记i已经访问
    EnQueue(Q, i);          //起点入队列

    //队列不为空，持续取出顶点，处理它所有邻接点
    while (!IsEmpty(Q)) {
        int v;
        DeQueue(Q, v);      //队头顶点出队
        ArcNode *p = G.vertices[v].firstarc; //取v的第一条边
        //遍历v所有邻接边
        for (; p != NULL; p = p->nextarc) {
            int w = p->adjvex; //w是v的邻接点
            if (!visited[w]) { //邻接点没有访问过
                visit(w);
                visited[w] = true;
                EnQueue(Q, w); //邻接点入队
            }
        }
    }
}

//==================== 邻接表 BFS遍历总入口，处理非连通图 ====================
/**
 * BFSTraverse：完整BFS遍历整张图，处理非连通图
 * 1.重置全部visited为false
 * 2.循环所有顶点，如果没访问，调用BFS，遍历一个连通分量
 */
void BFSTraverse(Graph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;

    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i])
            BFS(G, i);
    }
}

//==================== 邻接矩阵版 BFS 单个连通分量 ====================
/**
 * BFS2：邻接矩阵版本BFS，从i出发遍历单个连通分量
 * 邻接矩阵没有边结点指针，直接循环所有顶点找邻接点
 */
void BFS2(MGraph G, int i) {
    visit(i);
    visited[i] = true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, i);

    while (!IsEmpty(Q)) {
        int v;
        DeQueue(Q, v);
        int w;
        //遍历全部顶点，G.edge[v][w]==1说明v、w之间存在边
        for (w = 0; w < G.vexnum; w++) {
            if (G.edge[v][w] == 1 && !visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

//==================== 邻接表 DFS递归，单个连通分量 ====================
/**
 * DFS：深度优先递归遍历；从i出发，只遍历i所在连通分量
 */
void DFS(Graph G, int i) {
    visit(i);
    visited[i] = true;
    ArcNode *p = G.vertices[i].firstarc;
    //遍历i全部邻接点
    for (; p != NULL; p = p->nextarc) {
        int j = p->adjvex;
        if (!visited[j]) {
            DFS(G, j); //递归访问邻接点
        }
    }
}

//==================== 邻接表 DFS总入口，处理非连通图 ====================
/**
 * DFSTraverse_AL：邻接表完整DFS遍历整张图
 * 重置visited，循环所有顶点，非连通图多个连通分量全部访问
 */
void DFSTraverse_AL(Graph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;

    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i])
            DFS(G, i);
    }
}

//==================== 邻接矩阵 DFS递归 ====================
/**
 * DFS_M：邻接矩阵版本DFS递归；i起点，遍历单个连通分量
 */
void DFS_M(MGraph G, int i) {
    visit(i);
    visited[i] = true;
    int j;
    for (j = 0; j < G.vexnum; j++) {
        if (G.edge[i][j] == 1 && !visited[j]) {
            DFS_M(G, j);
        }
    }
}

//==================== 邻接矩阵 DFS总入口 ====================
void DFSTraverse_M(MGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = false;

    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i])
            DFS_M(G, i);
    }
}

//==================== BFS求无权图单源最短路径【仅无权图可用】 ====================
/**
 * BFS_MIN_Distance：无权图，起点u到各个顶点最短路径
 * dist[]：dist[w]保存u到w最短路径边数；只有无权图BFS能求最短路径
 */
void BFS_MIN_Distance(Graph g, int u) {
    int i;
    //初始化距离无穷大，访问标记全部false
    for (i = 0; i < g.vexnum; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[u] = 0;        //起点到自己距离0
    visited[u] = true;
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, u);

    while (!IsEmpty(Q)) {
        int v;
        DeQueue(Q, v);
        ArcNode *p = g.vertices[v].firstarc;
        for (; p != NULL; p = p->nextarc) {
            int w = p->adjvex;
            if (!visited[w]) {
                visited[w] = true;
                dist[w] = dist[v] + 1; //无权图，距离+1
                EnQueue(Q, w);
            }
        }
    }
}

//==================== 顺序栈，Kahn拓扑排序使用 ====================
/**
 * SqStack：顺序栈，top=-1代表栈空；栈用来存放入度为0顶点
 */
typedef struct{
    int data[MaxVertexNum];
    int top;
}SqStack;

//栈初始化，top置-1代表空栈
void InitStack(SqStack &S){
    S.top = -1;
}

//判断栈是否为空
bool IsEmpty(SqStack &S){
    return S.top == -1;
}

//入栈：先top自增，再存入元素
void Push(SqStack &S, int x){
    S.data[++S.top] = x;
}

//出栈：x接收弹出值；返回false代表栈空无法弹出
bool Pop(SqStack &S, int &x){
    if(IsEmpty(S))
        return false;
    x = S.data[S.top--];
    return true;
}

/**
 * TopSort：Kahn算法拓扑排序（邻接表）
 * @param G 输入图
 * @param topo[] 输出拓扑序列数组
 * @return true：无环；false：图存在回路
 * count：统计成功输出顶点数量；count == G.vexnum说明全部顶点输出，无环
 */
bool TopSort(Graph &G, int topo[])
{
    int indegree[MaxVertexNum]={0}; //indegree[]保存每个顶点入度，初始全部0
    SqStack S;
    InitStack(S);
    int count = 0;
    ArcNode *p;
    int i,v,w;

    //1.遍历整张图，统计每一个顶点的入度
    for(i=0;i<G.vexnum;i++){
        p = G.vertices[i].firstarc;
        for(;p;p=p->nextarc){
            w = p->adjvex;
            indegree[w]++; //i指向w，w的入度+1
        }
    }

    //2.所有入度等于0的顶点，压入栈
    for(i=0;i<G.vexnum;i++){
        if(indegree[i]==0) Push(S,i);
    }

    //3.Kahn主循环：栈不为空，不断取出入度为0顶点
    while(!IsEmpty(S))
    {
        Pop(S,v);               //弹出一个入度为0顶点v
        topo[count++] = v;      //存入拓扑序列，计数+1

        //遍历v所有出边，邻接点w入度减1
        p = G.vertices[v].firstarc;
        for(; p; p=p->nextarc)
        {
            w = p->adjvex;
            indegree[w]--;
            //w入度变为0，压入栈
            if(indegree[w]==0) Push(S,w);
        }
    }
    //count等于总顶点数：全部顶点输出，无环；否则有环
    return count==G.vexnum;
}
/*
手写代码范围：132 ~ 275
【复习提醒】
1. 循环队列：队满判断条件 (rear+1)%MaxSize==front，不要写错
2. 顺序栈分清 ++top（入栈）、top--（出栈），顺序写反直接全错
3. BFS求最短路径：**只适用于无权图**，带权图不能用BFS
4. Kahn拓扑排序：count == G.vexnum 判断图是否存在环；逆拓扑可直接反转拓扑序列数组
5. 邻接表遍历边：for(p=G.vertices[i].firstarc;p;p=p->nextarc)，p为NULL循环结束
*/

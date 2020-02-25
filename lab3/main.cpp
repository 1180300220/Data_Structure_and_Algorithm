#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;


int Edge[20][20];
int visited[20];
queue<int> vertex_matrix;
queue<int> vertex_list;
stack<int> dfs1;
stack<int> dfs2;

typedef struct node{
    int v;
    struct node* next;
}node;

typedef struct graph{
    node head_list[20];
    int num_v,num_e;
}graph;
graph G;


//初始化
void init(){
    printf("-------------------\n");
    memset(Edge,0,400*sizeof(int));
    memset(visited,0,20*sizeof(int));
    printf("请输入顶点数和边数：\n");
    scanf("%d %d",&G.num_v,&G.num_e);
    return ;
}

//添加双向边
void add_Edge(int a,int b){
    //Undirected graph
    Edge[a][b] = 1;
    Edge[b][a] = 1;
    return;
}

//打印矩阵
void show_Matrix(){
    printf("-------------------\n");
    printf("邻接矩阵的内容为：\n");
    for(int i = 0;i < G.num_v;i++){
        for(int j = 0;j < G.num_v;j++){
            if(Edge[i][j] == 0) printf("_ ");
            else printf("%d ",Edge[i][j]);
        }
        printf("\n");
    }
    printf("-------------------\n");
    return;
}

//打印邻接表内容
void show_list(){
    printf("-------------------\n");
    printf("邻接表的内容为：\n");
    for(int i = 0;i < 20;i++){
        printf("start[%d]:%d\t",i,G.head_list[i].v);
        node* tmp = G.head_list[i].next;
        if(tmp == NULL){
            printf("本行无邻接节点\n");
            continue;
        }else{
            while(tmp != NULL){
                printf("%d\t",tmp->v);
                tmp = tmp->next;
            }
        }
        printf("\n");
    }
    printf("-------------------\n");
    return ;
}

//建立矩阵
//  输入的ab建立边关系，调用add_Edge();
void build_matrix(){
    int a,b;
    printf("-------------------\n");
    printf("请输入相连的两个节点（起点编号为0）(-1 -1输入结束）：\n");
    scanf("%d %d",&a,&b);
    if(a == -1 && b == -1){
        return ;
    }else{
        add_Edge(a,b);
        build_matrix();
    }
}

//查询邻接表中某一节点所在行号
int show_No(int x){
    for(int i = 0;i < 20;i++){
        if(G.head_list[i].v == x){
            return i;
        }
    }
    printf("error:无此节点.\n");
    return -1;
}

//将邻接矩阵转换为邻接表：
//   遍历矩阵，将值为1的h位置的横纵坐标作为边的两个顶点输入矩阵。
void trans_matrix_to_list(){
    int k = 0;
    int flag = 0;
    for(int i = 0;i < 20;i++){
        flag = 0;
        for(int j = 0;j < 20;j++){
            if(Edge[i][j] == 1){
                if(flag == 0){
                    G.head_list[k].v = i;
                    flag = 1;
                }
                node* tmp = new node;
                tmp->v = j;
                tmp->next = G.head_list[k].next;
                G.head_list[k].next = tmp;
            }
        }
        k++;
    }
    return ;
}

//建立邻接表
//  将与每一行的行头部的值相连的节点都添加到这一行。
//  双向边，需要添加两次。
void build_list(){
    printf("-------------------\n");
    printf("请依次输入顶点编号：\n");
    for(int i = 0;i < G.num_v;i++){
        int tmp;
        scanf("%d",&tmp);
        G.head_list[i].v = tmp;
        G.head_list[i].next = NULL;
    }
    printf("-------------------\n");
    printf("请依次输入边关系（起点 终点）：\n");
    for(int i = 0;i < G.num_e;i++){
        int start,end;
        scanf("%d %d",&start,&end);
        
        node *tmp1 = new node;
        tmp1->v = end;
        tmp1->next = G.head_list[show_No(start)].next;
        G.head_list[show_No(start)].next = tmp1;
        
        node *tmp2 = new node;
        tmp2->v = start;
        tmp2->next = G.head_list[show_No(end)].next;
        G.head_list[show_No(end)].next = tmp2;
    }
    return ;
}

//将链表转换为矩阵
//  遍历邻接表，将每一行的值，以行首为起点，该值为终点输入矩阵
void trans_list_to_matrix(){
    node* tmp;
    for(int i = 0;i < 20;i++){
        int start = G.head_list[i].v;
        tmp = G.head_list[i].next;
        while(tmp != NULL){
            Edge[start][tmp->v] = 1;
            tmp = tmp->next;
        }
    }
    return ;
}


//递归方法dfs搜索矩阵
//  从第一行开始，对于找到的第一条边，将其输出，再将其终点作为起点重新查找。如果以某个值为起点的所有边都被访问过了，就返回到上一级。直到所有边都被访问过
void dfs_matrix_rec(int start){
    if(start == 0){
        printf("-------------------\n");
        printf("邻接矩阵下,dfs(递归算法)的结果为：\n");
        printf("0\t");
        visited[0] = 1;
    }
    for(int i = 0;i < 20;i++){
        if(Edge[start][i] == 1 && visited[i] == 0){
            printf("%d\t",i);
            visited[i] = 1;
            dfs_matrix_rec(i);
        }
    }
    if(start == 0){
        printf("\n-------------------\n");
    }
    return;
}

//非递归dfs搜索矩阵
//  建立一个栈，将起点0推入栈中。之后将栈顶元素弹出，将与此元素所有的边都压入栈中。之后重复操作，直至所有点都被遍历过。
void dfs_matrix_no_rec(){
    memset(visited, 0, 20*sizeof(int));
    printf("-------------------\n");
    printf("邻接矩阵下,dfs(非递归算法)的结果为：\n");
    dfs1.push(0);
    
    while(!dfs1.empty()){
        int tmp = dfs1.top();
        if(visited[tmp] == 1){
            dfs1.pop();
            continue;
        }
        printf("%d\t",tmp);
        visited[tmp] = 1;
        dfs1.pop();
        for(int i = 0;i < 20 ;i++){
            if(Edge[tmp][i] == 1 && visited [i] == 0){
                dfs1.push(i);
            }
        }
    }
    printf("\n-------------------\n");
    return ;
}

//bfs搜索矩阵
//  建立一个队列。从第一行开始，将每一条没有被访问过的边的终点压入队列中。
//  当队列非空时，将队列首元素弹出，对此元素递归使用bfs。
//  直至所有节点都被访问过。
void bfs_matrix(int start){
    if(start == 0){
        printf("-------------------\n");
        printf("邻接矩阵下bfs的结果为：\n");
        printf("0\t");
        memset(visited, 0, 20*sizeof(int));
        visited[0] = 1;
    }
    for(int i = 0;i < 20;i++){
        if(Edge[start][i] == 1 && visited[i] == 0){
            printf("%d\t",i);
            visited[i] = 1;
            vertex_matrix.push(i);
        }
    }
    if(!vertex_matrix.empty()){
        int tmp = vertex_matrix.front();
        vertex_matrix.pop();
        bfs_matrix(tmp);
    }else{
        return;
    }
    if(start == 0)  printf("\n-------------------\n");
    return;
}

//递归dfs搜索链表
//  与矩阵类似，链表中的每一行与矩阵中的每一行相同，只不过没有值为0的边，递归方法与上一个相同。
void dfs_list(int start){
    if(start == 0){
        printf("-------------------\n");
        printf("邻接表下,dfs(递归算法)的结果为：\n");
        printf("0\t");
        memset(visited, 0, 20*sizeof(int));
        visited[0] = 1;
    }
    node* tmp ;
    tmp = G.head_list[show_No(start)].next;
    while(tmp != NULL){
        if(visited[tmp->v] == 1){
            tmp = tmp->next;
            continue;
        }
        printf("%d\t",tmp->v);
        visited[tmp->v] = 1;
        dfs_list(tmp->v);
        
    }
    if(start == 0)  printf("\n-------------------\n");
    return ;
}

//非递归dfs搜索邻接表
//  与搜索矩阵相私，也需要一个栈，将起点放入，当栈非空时，将栈顶元素弹出，之后将与栈顶元素相连的所有元素压入栈。
//  重复操作直所有节点都被访问。
void dfs_list_no_rec(){
    memset(visited, 0, 20*sizeof(int));
    printf("-------------------\n");
    printf("邻接表下,dfs(非递归算法)的结果为：\n");
    dfs2.push(0);
    
    while(!dfs2.empty()){
        int tmp1 = dfs2.top();
        if(visited[tmp1] == 1){
            dfs2.pop();
            continue;
        }
        printf("%d\t",tmp1);
        visited[tmp1] = 1;
        dfs2.pop();
        node* tmp = G.head_list[show_No(tmp1)].next;
        while(tmp != NULL){
            if(visited[tmp->v] == 0){
                dfs2.push(tmp->v);
                tmp = tmp->next;
            }else{
                tmp = tmp->next;
                continue;
            }
        }
    }
    printf("\n-------------------\n");
    return ;
}

//bfs搜索链表
//  与矩阵类似。

void bfs_list(int start){
    node* tmp;
    int tmp1;
    if(start == 0){
        printf("-------------------\n");
        printf("邻接表下bfs的结果为：\n");
        printf("0\t");
        memset(visited, 0, 20*sizeof(int));
        visited[0] = 1;
    }
    tmp = G.head_list[show_No(start)].next;
    while(tmp != NULL){
        if(visited[tmp->v] == 1){
            tmp = tmp->next;
            continue;
        }
        vertex_list.push(tmp->v);
        printf("%d\t",tmp->v);
        visited[tmp->v] = 1;
        tmp = tmp->next;
    }
    if(!vertex_list.empty()){
        tmp1 = vertex_list.front();
        vertex_list.pop();
        bfs_list(tmp1);
    }else{
        return ;
    }
    if(start == 0)  printf("\n-------------------\n");
    return ;
}


int main(){
    int choice;
    init();
    printf("-------------------\n");
    printf("请选择构建方式：\n1.邻接矩阵\n2.邻接链表\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            build_matrix();
            trans_matrix_to_list();
            break;
        case 2:
            build_list();
            trans_list_to_matrix();
    }
    show_Matrix();
    show_list();
    dfs_matrix_rec(0);
    dfs_matrix_no_rec();
    bfs_matrix(0);
    dfs_list(0);
    dfs_list_no_rec();
    bfs_list(0);
    return 0;
}

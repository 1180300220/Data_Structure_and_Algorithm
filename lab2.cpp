//
//  main.cpp
//  DS&A_lab2
//
//  Created by Hans on 2019/11/21.
//  Copyright © 2019 Hans. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;
#define MAX 1024
char nodes[MAX];
int cnt;
int flag;



typedef struct tree_node * P_tree;
typedef struct tree_node{
    char c;
    P_tree l_child;
    P_tree r_child;
}B_tree;
P_tree tree1;
queue<P_tree> q_tmp;

//初始化，建立初始节点
void init(){
    cnt = 0;
    tree1 = (P_tree)malloc(sizeof(B_tree));
    flag = 1;
}

//建立子节点
void push_son(B_tree** tmp_tree){
    char tmp_node = nodes[cnt++];
    //如果字符为*，表示空节点。
    if(tmp_node == '*'){
        *tmp_tree = NULL;
    }else{
        *tmp_tree = (P_tree)malloc(sizeof(B_tree));
        (*tmp_tree)->c = tmp_node;
        push_son(&((*tmp_tree)->l_child));
        push_son(&((*tmp_tree)->r_child));
    }
    return ;
}

//打印先根遍历结果
//先打印值，之后对两个子节点进行递归
void show_preorder_rec(P_tree tmp_tree){
    if(tmp_tree != NULL){
        printf("%c ",tmp_tree->c);
        show_preorder_rec(tmp_tree->l_child);
        show_preorder_rec(tmp_tree->r_child);
    }
}

//打印中根遍历结果
//  先对左子节点进行递归，在打印值，在对右子节点进行递归
void show_inorder_rec(P_tree tmp_tree){
    if(tmp_tree != NULL){
        show_inorder_rec(tmp_tree->l_child);
        printf("%c ",tmp_tree->c);
        show_inorder_rec(tmp_tree->r_child);
    }
}

//打印后根遍历结果
//  先对左子节点进行递归，在对右子节点进行递归，最后打印值
void show_postorder_rec(P_tree tmp_tree){
    if(tmp_tree != NULL){
        show_postorder_rec(tmp_tree->l_child);
        show_postorder_rec(tmp_tree->r_child);
        printf("%c ",tmp_tree->c);
    }
}

//先根遍历（无递归）
//建立一个栈，将所在节点压入栈，之后打印此节点的值。
//如果所在节点的左子节点不空，将左子节点转换为当前节点，然后重复上述操作
//如果左子节点为空，则从栈中弹出一个元素，将当前节点转换为该元素的右节点。重复操作
void show_preorder_no_rec(P_tree tmp_tree){
    stack<P_tree> s_tmp;
    P_tree tmp;
    tmp = tmp_tree;
    while((tmp!=NULL) || !s_tmp.empty()){
        if(tmp != NULL){
            s_tmp.push(tmp);
            printf("%c ",tmp->c);
            tmp = tmp->l_child;
        }else{
            tmp = s_tmp.top();
            s_tmp.pop();
            tmp = tmp->r_child;
        }
    }
}

//中根遍历（非递归）
//与先根遍历类似，只需要调整打印位置即可。
void show_inorder_no_rec(P_tree tmp_tree){
    stack<P_tree> s_tmp;
    P_tree tmp;
    tmp = tmp_tree;
    while((tmp != NULL) || !s_tmp.empty()){
        if(tmp != NULL){
            s_tmp.push(tmp);
            tmp = tmp->l_child;
        }else{
            tmp = s_tmp.top();
            s_tmp.pop();
            printf("%c ",tmp->c);
            tmp = tmp->r_child;
        }
    }
    
}

//后根遍历（非递归）
//与先根遍历类似，只需要调整输出位置即可。
void show_postorder_no_rec(P_tree tmp_tree){
    stack<P_tree> s_tmp;
    P_tree tmp;
    P_tree flg = NULL;
    tmp = tmp_tree;
    
    while((tmp != NULL) || !s_tmp.empty()){
        if(tmp != NULL){
            s_tmp.push(tmp);
            tmp = tmp->l_child;
        }else{
            tmp = s_tmp.top();
            if((tmp->r_child == NULL) || (tmp == flg)){
                printf("%c ",tmp->c);
                s_tmp.pop();
                //tmp = s_tmp.top();
                //flg = tmp;
                tmp = NULL;
            }else{
                flg = tmp;
                tmp = tmp->r_child;
            }
        }
    }
}

//逐层输出
//建立一个队列，将树的根节点推入。
//当队列不空时，将队列首元素推出，打印，之后分别将其左右子节点推入队列。
void show_level(P_tree tmp_tree){
    q_tmp.push(tmp_tree);
    P_tree tmp;
    while(!q_tmp.empty()){
        tmp = q_tmp.front();
        q_tmp.pop();
        printf("%c ",tmp->c);
        if(tmp->l_child!=NULL)  q_tmp.push(tmp->l_child);
        if(tmp->r_child!=NULL)  q_tmp.push(tmp->r_child);
    }
    return;
}

//判断是否是完全二叉树
//遍历所有节点，如果所有的节点的左右子节点都同时存在或不存在，则是完全二叉树
void if_complete(P_tree tmp_tree){
    if(tmp_tree == NULL){
        flag = 0;
        printf("The tree is empty!\n");
    }else{
        if((tmp_tree->l_child != NULL) && (tmp_tree->r_child != NULL)){
            if_complete(tmp_tree->l_child);
            if_complete(tmp_tree->r_child);
        }else if((tmp_tree->l_child == NULL) && (tmp_tree->r_child == NULL)){
            return;
        }else{
            flag = -1;
        }
    }
}

int main(int argc, const char * argv[]) {
    init();
    
    printf("请按照前根遍历的顺序输入节点内容，空节点请输入'*':(注：所有叶节点都必须有两个空子节点\n");
    gets(nodes);
    push_son(&tree1);
    printf("------------------\n输入的字符串为：\n");
    puts(nodes);
    printf("------------------\n");
    printf("递归实现：\n");
    printf("前根遍历的结果为：\n");
    show_preorder_rec(tree1);
    printf("\n");
    printf("----------\n");
    printf("中根遍历的结果为：\n");
    show_inorder_rec(tree1);
    printf("\n");
    printf("----------\n");
    printf("后根遍历的结果为：\n");
    show_postorder_rec(tree1);
    printf("\n");
    printf("-----------------\n");
    printf("非递归实现：\n");
    printf("前根遍历的结果为：\n");
    show_preorder_no_rec(tree1);
    printf("\n");
    printf("----------\n");
    printf("中根遍历的结果为：\n");
    show_inorder_no_rec(tree1);
    printf("\n");
    printf("----------\n");
    printf("后根遍历的结果为：\n");
    show_postorder_no_rec(tree1);
    printf("\n");
    printf("-----------------\n");
    printf("按层遍历的结果为：\n");
    show_level(tree1);
    printf("\n-----------------\n");
    //To check if the tree is a complete_binary_tree
    printf("是否是完全二叉树：\n");
    if_complete(tree1);
    if(flag == -1){
        printf("此树不是完全二叉树\n");
    }else if(flag == 1){
        printf("此树是完全二叉树\n");
    }
    
    return 0;
}

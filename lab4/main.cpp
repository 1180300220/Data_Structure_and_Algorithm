#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//定义节点：
//  key：节点内值
//  left：指向左子节点的指针
//  right：指向右子节点的指针
//  height：此节点高度
typedef struct node
{
    int key;
    node* left;
    node* right;
    int height;
}node;

//定义树tree
node* tree;

//创建一棵新树
node* create(int key)
{
    //开辟一块空间
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 0;
    //返回根节点。
    return tmp;
}

//计算高度
//  直接返回对应节点中的height值
int get_height(node* tmp)
{
    if(tmp == NULL){
        return 0;
    }else{
        return tmp->height;
    }
}

//搜索最大值：
//  不停的从根节点向右寻找，直到找到整个树的最右侧节点。
node* get_max(node* root){
    if(root == NULL)    return NULL;
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

//按值搜索：
//  从根节点开始，将当前节点的值与要搜索的值进行对比
//  如果节点的值大于要搜索的值，则到左子树寻找
//  否则去右子树寻找。
void search(node* root,int num){
    //如果当前节点就是要查找的节点，就打印信息
    if(num == root->key){
        //左右子树都不为空：
        if((root->left != NULL) && (root->right != NULL)){
            printf("此节点高度为%d。左子节点为%d,右子节点为%d.\n",root->height,root->left->key,root->right->key);
        }
        //左子树为空，右子树不为空
        else if((root->left == NULL) && (root->right != NULL)){
            printf("此节点高度为%d，无左子节点，右子节点为%d.\n",root->height,root->right->key);
        }
        //左子树不为空，右子树为空
        else if((root->left != NULL) && (root->right == NULL)){
            printf("此节点高度为%d，左子节点为%d，无右子节点.\n",root->height,root->left->key);
        }
        //左右子树都为空
        else{
            printf("此节点高度为%d,无子节点。\n",root->height);
        }
    }
    //如果要查找的数值大于当前节点的数值，则到其右子树查找。
    else if(num > root->key){
        search(root->right, num);
    }
    //如果要查找的数值小于当前节点的数值，则到其左子树查找。
    else if(num < root->key){
        search(root->left,num);
    }
}

//查找最小值：
//  如果当前节点左子树不为空，就到其左子树中查找，直到找到最左侧的节点。
node* get_min(node* root){
    if(root == NULL)    return NULL;
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

//比较：
//  返回较大值。
int Max(int a,int b){return a>b?a:b;}

//LL：
//  首先定义一个新的节点指针son，指向当前节点root的左子节点；
//  之后将root的左子树变为son的右子树；
//  再将son的右子树变为root；
//  最后更新高度
node* LL(node* root)
{
    node* son;
    son = root->left;
    root->left = son->right;
    son->right = root;

    root->height = Max(get_height(root->right),get_height(root->left))+1;
    son->height = Max(get_height(son->left),get_height(son->right))+1;

    return son;
}

//RR：
//  首先定义一个新的节点指针son，指向当前节点root的右子节点；
//  之后将root的右子树变为son的左子树；
//  再将son的左子树变为root；
//  最后更新高度
node* RR(node* root)
{
    node* son;
    son = root->right;
    root->right = son->left;
    son->left = root;

    root->height = Max(get_height(root->left),get_height(root->right))+1;
    son->height = Max(get_height(son->right),get_height(root->left))+1;

    return son;
}

//LR：
//  这种情况需要先对当前节点的左节点执行一次RR，构成符合LL的情况
//  之后对当前节点执行LL。
node* LR(node* root)
{
    root->left = RR(root->left);
    return LL(root);
}


//RL：
//  RL与LR完全对称。
node* RL(node* root)
{
    root->right = LL(root->right);
    return RR(root);
}

//插入节点：
//  首先查找节点的位置，按照普通二叉树的方式正常插入。之后在进行调整。
//  如果插入了左子树的左节点，则进行LL旋转
//  如果插入了右子树的右节点，则进行RR旋转
//  如果插入了左子树的右节点，则进行LR旋转
//  如果插入了右子树的左节点，则进行RL旋转

node* insert_node(node** root_tmp,int num)
{
    node* root = *root_tmp;
    if(root == NULL){
        root = create(num);
        if(root == NULL)    printf("NULL");
    }
    else if(num < root->key){
        root->left = insert_node(&(root->left),num);
        if(get_height(root->left) - get_height(root->right) == 2){
            if(num < root->left->key)   root = LL(root);
            else if(num > root->right->key) root = LR(root);
        }
    }else if(num > root->key){
        root->right = insert_node(&(root->right),num);
        if(get_height(root->right)-get_height(root->left) == 2){
            if(num > root->right->key)  root = RR(root);
            else if(num < root->right->key) root = LL(root);
        }
    }else if(num == root->key){
        printf("The node has been exist./n");
    }

    root->height = Max(get_height(root->right),get_height(root->left))+1;

    return root;
}

//删除节点
//  与插入节点类似，先找到要删除的节点所在的位置，之后将此节点的左子树中的最大值放到此节点。
//  这样可以保证二叉树的结构是完整的。
//  之后，为保证树仍符合avl树的构成规则，进行进一步调整；
//  比较当前节点的左右子节点的高度。如果不同，一定是右节点的高度大于左节点的高度。
node* delete_node(int num,node** root_tmp)
{
    node* root = *root_tmp;
    //如果当前节点为空节点，返回NULL
    if(root == NULL) return NULL;
    //如果待查询的值小于当前节点值，则去左子树中继续查找。
    if(num < root->key){
        root->left = delete_node(num,&(root->left));
        //删除之后调整高度。
        if(get_height(root->right) - get_height(root->left) == 2){
            //分情况对右节点的两个子节点的高度进行讨论。
            //如果右节点的右子节点的高度小于左子节点的高度，则需要对右节点进行RL
            if(get_height(root->right->left) > get_height(root->right->right)){
                root->right = RL(root->right);
            }
            //如果有节点的右子节点的高度大于左子节点的高度，则需要对右节点进行RR
            else if(get_height(root->right->left) < get_height(root->right->right)){
                root->right = RR(root->right);
            }
        }
    }
    //如果待查询的值大于当前节点值，则去右子树中继续查找。
    else if(num > root->key){
        root->right = delete_node(num,&(root->right));
        //删除之后调整高度。
        if(get_height(root->left) - get_height(root->right) == 2){
            //分情况对左节点的两个子节点的高度进行讨论。
            //如果左节点的右子节点的高度小于左子节点的高度，则需要对右节点进行LL
            if(get_height(root->left->left) > get_height(root->left->right)){
                root->left = LL(root->left);
            }
            //如果左节点的右子节点的高度大于左子节点的高度，则需要对右节点进行LR
            else if(get_height(root->left->left) < get_height(root->left->right)){
                root->left = LR(root->left);
            }
        }
    }else{
        //如果待查询的值就是此节点的值
        //左右节点都不为空
        if((root->right) && (root->left)){
            //如果左节点的高度大于右节点，则将左子树的最大值直接移到此处。
            if(get_height((root->left)) > get_height((root->right))) {
                node *max = get_max(root->left);
                int tmp = max->key;
                root->left = delete_node(max->key, &(root->left));
                root->key = tmp;
            }else{
                //反之，则将右子树的最小值挪到此处
                node* min = get_min(root->right);
                int tmp = min->key;
                root->right = delete_node(min->key,&(root->right));
                root->key = tmp;
            }
        }
        else{
            //如果有节点为空，则将不空的那个节点补到原位置。
            node* tmp = root;
            //如果左节点不为空
            if(root->left != NULL){
                root = root ->left;
            }
            //如果左节点为空
            else{
                root = root->right;
            }
            free(tmp);
        }
    }
    return root;
}

//先根遍历树，输出结果。
void preorder(node* tree){
    if(tree != NULL){
        printf("%d\t",tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }else{
        printf("*\t");
    }
}

//中根遍历树，输出结果。此结果即为排好序的结果。
void midorder(node* tree){
    if(tree!=NULL){
        midorder(tree->left);
        printf("%d\t",tree->key);
        midorder(tree->right);
    }
}

int main(){
    L1:
    printf("----------------\n");
    printf("1. 插入节点\n");
    printf("2. 删除节点\n");
    printf("3. 显示树结构（先根顺序）\n");
    printf("4. 排序。\n");
    printf("5. 查找节点\n");
    printf("0. 退出程序\n");
    printf("输入序号:\n");
    
    int op;
    scanf("%d",&op);
    //根据用户进行的操作进行选择。
    //通过goto进行多次操作输入。
    switch (op){
        case 1:
            //插入节点
            printf("输入节点个数:\n");
            int number,key;
            scanf("%d",&number);
            printf("输入节点数值:\n");
            for(int i = 0;i < number;i++){
                scanf("%d",&key);
                tree = insert_node(&tree,key);
            }
            goto L1;
            break;
        case 2:
            //删除节点
            printf("输入要删除的节点的值：\n");
            int num;
            scanf("%d",&num);
            delete_node(num,&tree);
            goto L1;
            break;
        case 3:
            //展示树结构：
            printf("树结构如下（先根顺序）：\n");
            preorder(tree);
            printf("\n");
            goto L1;
            break;
        case 4:
            //排序：
            printf("从小到大顺序：\n");
            midorder(tree);
            printf("\n");
            goto L1;
        case 5:
            //查找节点
            printf("请输入要查找的节点：\n");
            int key1;
            scanf("%d",&key1);
            search(tree, key1);
            goto L1;
        case 0:
            return 0;
    }
    return 0;
}

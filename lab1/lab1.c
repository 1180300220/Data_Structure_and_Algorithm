
/*
 test temp:
 #3+(4+5)#
 #3+4*6#
 #4*(5+3)#
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mid_exp[50];
char back_exp[50];
int mid_cnt;
int back_cnt;
char tmp;

//运算符号链表节点
typedef struct node *P;
struct node{
    char a;
    P next;
};

//整数链表节点
typedef struct node1 *P_num;
struct node1{
    int num;
    P_num next;
};

//浮点数链表节点
typedef struct node2 *P_float;
struct node2{
    float num;
    P_float next;
};


P s0;
P_num s1;
P_float s2;

//调整顺序所需栈
P newstack(){
    P s_tmp;
    s_tmp = (P)malloc(sizeof(struct node));
    s_tmp->next = NULL;
    return s_tmp;
}
//运算整数时的整数栈
P_num newstack_num(){
    P_num s_tmp;
    s_tmp = (P_num)malloc(sizeof(struct node1));
    s_tmp->next = NULL;
    return s_tmp;
}
//运算符点数时的符点数栈
P_float newstack_float(){
    P_float s_tmp;
    s_tmp = (P_float)malloc(sizeof(struct node2));
    s_tmp->next = NULL;
    return s_tmp;
}

void init(){
    mid_cnt = 1;
    back_cnt = 1;
    back_exp[0] = '#';
    back_exp[back_cnt++] = ' ';
}

//推入运算符号
void push(P s,char x){
    P s_tmp;
    s_tmp = (P)malloc(sizeof(struct node));
    s_tmp->a = x;
    s_tmp->next = s->next;
    s->next = s_tmp;
}

//推入整数
void push_num(P_num s,int x){
    P_num s_tmp;
    s_tmp = (P_num)malloc(sizeof(struct node1));
    s_tmp->num = x;
    s_tmp->next = s->next;
    s->next = s_tmp;
}

//推入符点数
void push_float(P_float s,float x){
    P_float s_tmp;
    s_tmp = (P_float)malloc(sizeof(struct node2));
    s_tmp->num = x;
    s_tmp->next = s->next;
    s->next = s_tmp;
}

//弹出运算符号
char pop(P s){
    if(s->next == NULL){
        return -1;
    }else{
        char result;
        result = s->next->a;
        P tmp = s->next;
        s->next = s->next->next;
        free(tmp);
        return result;
    }
}

//弹出栈顶整数
int pop_num(P_num s){
    if(s->next == NULL){
        return -1;
    }else{
        int result;
        result = s->next->num;
        P_num tmp = s->next;
        s->next = s->next->next;
        free(tmp);
        return result;
    }
}

//弹出栈顶符点数
float pop_float(P_float s){
    if(s->next == NULL){
        return -1;
    }else{
        float result;
        result = s->next->num;
        P_float tmp = s->next;
        s->next = s->next->next;
        free(tmp);
        return result;
    }
}

//打印中缀表达式
void print_mid_expression(){
    printf("# ");
    int cnt = 1;
    while(mid_exp[cnt] != '#'){
        printf("%c ",mid_exp[cnt++]);
    }
    printf("#\n");
}

//打印栈中内容
void print_stack(P s){
    printf("栈中内容：");
    P s_tmp = s->next;
    if(s->next == NULL){
        printf("栈空\n");
    }else{
        printf("%c ",s_tmp->a);
        while(s_tmp->next != NULL){
            s_tmp = s_tmp->next;
            printf("%c ",s_tmp->a);
        }
        printf("\n");
    }
}

//打印整数栈中内容
void print_num_stack(P_num s){
    printf("栈中内容：");
    P_num s_tmp = s->next;
    if(s1->next == NULL){
        printf("栈空\n");
    }else{
        while(s_tmp != NULL){
            printf("%d ",s_tmp->num);
            s_tmp = s_tmp->next;
        }
        printf("\n");
    }
}

//打印符点数栈中内容
void print_float_stack(P_float s){
    printf("栈中内容：");
    P_float s_tmp = s->next;
    if(s2->next == NULL){
        printf("栈空\n");
    }else{
        while(s_tmp != NULL){
            printf("%f ",s_tmp->num);
            s_tmp = s_tmp->next;
        }
        printf("\n");
    }
}


//得到后缀表达式
void get_back_expression(){
    //检查格式是否正确
    while(mid_exp[mid_cnt] != '#'){
        //printf("mid_exp[mid_cnt] != # \n");
        //右括号的情况
        if(mid_exp[mid_cnt] == ')'){
            printf("case ')'\n");
            while(s0->next->a != '('){
                tmp = pop(s0);
                back_exp[back_cnt++] = tmp;
                back_exp[back_cnt++] = ' ';
                print_stack(s0);
            }
            pop(s0);
            print_stack(s0);
        }
        //+或-的情况
        else if(mid_exp[mid_cnt] == '+' || mid_exp[mid_cnt] == '-'){
            printf("case + - \n");
            if(s0->next!=NULL){
                if(s0->next->a == '+' || s0->next->a == '-' || s0->next->a == '('){
                    push(s0,mid_exp[mid_cnt]);
                    print_stack(s0);
                }
                else if(s0->next->a == '*' || s0->next->a == '/' || s0->next->a == '%'){
                    tmp = pop(s0);
                    back_exp[back_cnt++] = tmp;
                    back_exp[back_cnt++] = ' ';
                    print_stack(s0);
                    push(s0,mid_exp[mid_cnt]);
                }
            }
            else{
                push(s0,mid_exp[mid_cnt]);
                print_stack(s0);
            }
        }
        //*或/或（的情况
        else if(mid_exp[mid_cnt] == '*' || mid_exp[mid_cnt] == '/' || mid_exp[mid_cnt] == '(' || mid_exp[mid_cnt] == '%'){
            printf("case * / ( % \n");
            push(s0,mid_exp[mid_cnt]);
            print_stack(s0);
        }
        //数字的情况
        else if((mid_exp[mid_cnt]>= 48 && mid_exp[mid_cnt] <= 57) || mid_exp[mid_cnt] == '.'){
            printf("case number\n");
            back_exp[back_cnt++] = mid_exp[mid_cnt++];
            while((mid_exp[mid_cnt]>= 48 && mid_exp[mid_cnt] <= 57) || mid_exp[mid_cnt] == '.'){
                back_exp[back_cnt++] = mid_exp[mid_cnt++];
            }
            back_exp[back_cnt++] = ' ';
            mid_cnt--;
        }
        mid_cnt++;
    }
    // 弹出最后一个运算符
    while(s0->next != NULL){
        tmp = pop(s0);
        back_exp[back_cnt++] = tmp;
        back_exp[back_cnt++] = ' ';
        print_stack(s0);
    }
}


//打印后缀表达式
void print_back_expression(){
    back_exp[back_cnt] = '#';
    for(int i = 0;i <= (int)strlen(back_exp);i++){
        printf("%c",back_exp[i]);
    }
    printf("\n");
}

//计算后缀表达式（整数）
void cal_back_expression(){
    int tmp,tmp1,tmp2;
    back_cnt = 2;
    while(back_exp[back_cnt] != '#'){
        if(back_exp[back_cnt] >= 48 && back_exp[back_cnt] <= 57){
            tmp = back_exp[back_cnt++] - 48;
            while(back_exp[back_cnt] >= 48 && back_exp[back_cnt] <= 57)
            {
                tmp = tmp * 10 + back_exp[back_cnt++] - 48;
            }
            push_num(s1,tmp);
            print_num_stack(s1);
            back_cnt++;
        }
        else{
            tmp1 = pop_num(s1);
            print_num_stack(s1);
            tmp2 = pop_num(s1);
            print_num_stack(s1);
            if(back_exp[back_cnt] == '+'){
                push_num(s1, tmp1+tmp2);
            }else if(back_exp[back_cnt] == '-'){
                push_num(s1,tmp1-tmp2);
            }else if(back_exp[back_cnt] == '*'){
                push_num(s1, tmp1 * tmp2);
            }else if(back_exp[back_cnt] == '/'){
                push_num(s1, tmp2/tmp1);
            }else if(back_exp[back_cnt] == '%'){
                push_num(s1, tmp2%tmp1);
            }
            print_num_stack(s1);
            back_cnt += 2;
        }
    }
    printf("the result is %d\n",s1->next->num);
}

//计算符点数后缀表达式
void cal_back_expression_float(){
    float tmp,tmp1,tmp2;
    char tmp_float[50] = {0};
    back_cnt = 2;
    while(back_exp[back_cnt] != '#'){
        if((back_exp[back_cnt] >= 48 && back_exp[back_cnt] <= 57) || back_exp[back_cnt] == '.'){
            int tmp_float_cnt = 0;
            for(int b = 0;b<=20;b++){
                tmp_float[b] = 0;
            }
            tmp_float[tmp_float_cnt++] = back_exp[back_cnt++];
            while((back_exp[back_cnt] >= 48 && back_exp[back_cnt] <= 57) || back_exp[back_cnt] == '.')
            {
                tmp_float[tmp_float_cnt++] = back_exp[back_cnt++];
            }
            tmp = atof(tmp_float);
//            printf("tmp = %f\n",tmp);
            push_float(s2, tmp);
            print_float_stack(s2);
            back_cnt++;
        }
        else{
            tmp1 = pop_float(s2);
            print_float_stack(s2);
            tmp2 = pop_float(s2);
            print_float_stack(s2);
            if(back_exp[back_cnt] == '+'){
                push_float(s2, tmp1+tmp2);
            }else if(back_exp[back_cnt] == '-'){
                push_float(s2,tmp1-tmp2);
            }else if(back_exp[back_cnt] == '*'){
                push_float(s2, tmp1 * tmp2);
            }else if(back_exp[back_cnt] == '/'){
                push_float(s2, tmp2/tmp1);
            }
            print_float_stack(s2);
            back_cnt += 2;
        }
    }
    printf("the result is %.4f\n",s2->next->num);
}


int main()
{
    init();
    printf("请输入计算类型（序号）：\n1.整数运算（可进行取模画运算）\n2.浮点数运算：\n");
    int op_case ;
    scanf("%d",&op_case);
    printf("请输入前缀表达式：\n");
    getchar();
    gets(mid_exp);
    s0 = newstack();
    s1 = newstack_num();
    s2 = newstack_float();
    printf("中缀表达式为：");
    print_mid_expression();
    get_back_expression();
    printf("后缀表达式为：");
    print_back_expression();
    if(op_case == 1){
        cal_back_expression();
        return 0;
    }
    cal_back_expression_float();
    return 0;
}



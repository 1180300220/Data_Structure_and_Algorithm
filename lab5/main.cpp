//
//  main.cpp
//  D_lab5
//
//  Created by HanCui on 2019/12/28.
//  Copyright © 2019 Han. All rights reserved.
//


//  test data:
//  7
//  1 91 82 7 63 47 56
//  9
//  1 87 56 982 456 23 98 32 90

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int length,op,N;
clock_t sta,fin;
int a[100000000];
int b[100000000];


void init()
{
    op = 0;
    length = 0;
    memset(a,0,sizeof(int));
    memset(b,0,sizeof(int));
}

//用户界面，读入用户选项
void start()
{
    printf("------------------\n");
    printf("选择排序模式:\n");
    printf("1.直接插入排序（Straight insertion sort）\n");
    printf("2.折半插入排序（Binary Insertion sort）\n");
    printf("3.冒泡排序（bubble sort）\n");
    printf("4.快速排序（quick sort）\n");
    printf("5.选择排序（Selection sort）\n");
    printf("6.堆排序（heap sort）\n");
    printf("7.基数排序（Radix sort）\n");
    printf("0.退出程序\n");
    scanf("%d",&op);
    if(op == 0)     return;
//    printf("请输入要排序的数字个数：\n");
//    scanf("%d",&length);
//    printf("请输入数据规模：\n");
//    scanf("%d",&N);
    N = 1000;
    //printf("请依次输入要排序的字：\n");
    //调用rand()生成随机数
    for(int i = 0;i < length;i++){
        a[i] = rand()%N;
    }
    printf("\n");
//    for(int i = 0;i <length ;i++){
//        printf("%d\t",a[i]);
//    }
}

//打印结果：
void show_result()
{
//    printf("\n----------\n");
    //printf("排序结果为：\n");
//    for(int i = 0;i < length;i++){
//        printf("%d\t",a[i]);
//    }
    printf("所耗时间为%lfms\n",(double)(fin-sta)/CLOCKS_PER_SEC);
    printf("---------------\n");
    return ;
}

//直接插入排序：
//  对于第i个元素，到第0个至第i-1个已经排好序的元素队列中找到合适的位置j，
//  将第i个元素的值先保存，然后将第j-1至i-1个元素后移一个位置，再将刚才
//  存好的第i个元素值写入i位置。
//
void stra_ins_sort()
{
    int i,j,k;
    for(i = 1;i < length;i++){
        for(j = i-1;j >= 0;j--){
            //找到合适位置，退出循环
            if(a[j] < a[i])  break;
        }
        if(j != i-1){
            //暂存第i个元素
            int tmp = a[i];
            //后移所有元素
            for(k = i-1;k > j;k--){
                a[k+1] = a[k];
            }
            a[k+1] = tmp;
        }
    }
    return;
}


//折半插入排序：
//  与直接插入排序相同，但是查找合适位置的方式做了变化：
//  由原来的遍历查找，变为二分查找。
void bin_ins_sort()
{
    int i,j,left,right,tmp;
    for(i = 1;i < length;i++)
    {
        left = 0;
        right = i-1;
        tmp = a[i];
        //二分查找合适位置：
        while(left <= right){
            int mid = (left + right)/2;
            if(a[mid] > tmp)    right = mid-1;
            else    left = mid + 1;
        }
        //后移所有元素
        for(j = i;j > left;j--){
            a[j] = a[j-1];
        }
        a[left] = tmp;
    }
}

//冒泡排序：
//  逐次遍历第0至length-1个元素，将不满足大小关系的相邻的两个元素交换
//  整个数组的顺序将从后往前逐渐排好。
void bubble()
{
    int i,j;
    //第i次遍历
    for(i = 0;i < length-1;i++){
        //从第一个(a[0])开始，直到a[length-1-i]结束，调整相邻两个元素的位置
        for(j = 0;j < length-1-i;j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
    return;
}


//快速排序：
//  将排序问题二分，选择一个基准值，将所有比基准值小的数字放在基准值前边，比基准值大的数字放在基准值后边
//  这样，数列就被分为：比基准值小的数列 + 基准值 + 比基准值大的数列
//  再用同样的方法，对前后两个数列进行排序，递归执行。
void quick_sort(int* a,int left,int right){
    if(left > right)    return ;
    
    int l = left,r = right,key = a[l];
    while(l < r){
        //寻找右侧比基准值key小的值，将其放到左侧
        while(l < r && a[r] >= key)  r--;
        a[l] = a[r];
        //寻找左侧比基准值key小的值，将其放到右侧
        while(l < r && a[l] <= key)  l++;
        a[r] = a[l];
    }
    a[l] = key;
    //对前后两个数列递归执行排序
    quick_sort(a,left,l-1);
    quick_sort(a, l+1, right);
}

//选择排序：
// 从未排序的数组中选出一个最小值，放在当前未排序数组的开头，
// 然后从将此值从数组中去掉，对剩余数字组成的数组重复操作
void sel_sort(){
    for(int i = 0; i < length-1; i++){
        //min不是最小值，是最小值的下标
        int min = i;
        //寻找最小值，将其下标存入min
        for(int j = i+1; j < length; j++){
            if(a[min] > a[j])   min = j;
        }
        //如果最小值不在数组开头，将其与开头元素调换位置。
        if(min != i){
            int tmp = a[min];
            a[min] = a[i];
            a[i] = tmp;
        }
    }
    return;
}
           
//堆排序：
//  用未排序的数字维护一个小顶堆，每次弹出堆顶元素，这个元素是当前所有未排序的元素中最小的元素
//  将每次弹出的元素逐一放入结果数组，所有元素被处理后得到的数组就是排序结果。
void judge(int i,int len)
{
    int son,tmp;
    for(tmp = a[i];2*i+1 < len;i = son){
        son = 2*i+1;
        if(son != len-1 && a[son+1] > a[son]){
            son++;
        }
        if(tmp < a[son]){
            a[i] = a[son];
        }else{
            break;
        }
    }
    a[i] = tmp;
    return;
}
void heap_sort(){
    int i;
    for(i = length/2;i >= 0;i--)
    {
        judge(i,length);
    }
    for(i = length - 1;i > 0;--i){
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        judge(0,i);
    }
}

//基数排序：
//  从最低有效位开始，按照该位的数值分类。然后按数值从小到大依次将所有数放回数组
//  最低有效位结束后，处理最低有效位的上一位，以此类推至所有位都被处理过，最后一次被放回后得到的数组就是排好序的数组。
void radix_sort(){
    int i,m = a[0],exp = 1;
    
    for(i = 1;i < length;i++){
        if(a[i] > m)    m = a[i];
    }
    
    while(m / exp > 0){
        int bucket[10] = {0};
        
        for (i = 0;i < length;i++){
            bucket[(a[i]/exp) % 10]++;
        }
        
        for(i = 1;i < 10;i++){
            bucket[i] += bucket[i-1];
        }
        
        for(i = length-1;i >= 0;i--){
            b[--bucket[(a[i] / exp) % 10]] = a[i];
        }
        for(i = 0;i < length;i++){
            a[i] = b[i];
        }
        exp *= 10;
    }
}

void do_sort(){
    switch (op) {
        case 1:
            //直接插入排序
            for(int num = 1;num <= 150;num *= 2){
                length = 1024*num;
                sta = clock();
                printf("length = %d\n",length);
//                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                stra_ins_sort();
                fin = clock();
                show_result();
            }
            break;
        case 2:
            //折半插入排序
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                            bin_ins_sort();
                            fin = clock();
                            show_result();
                        }
            break;
        case 3:
            //冒泡排序
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                            bubble();
                            fin = clock();
                            show_result();
                        }
            
            break;
        case 4:
            //快排
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                            quick_sort(a,0,length);
                            fin = clock();
                            show_result();
                        }
            break;
        case 5:
            //选择排序
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                            sel_sort();
                            fin = clock();
                            show_result();
                        }
            break;
        case 6:
            //堆排序
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                heap_sort();
                            fin = clock();
                            show_result();
                        }            break;
        case 7:
            //基数排序
            for(int num = 1;num <= 150;num *= 2){
                            length = 1024*num;
                            sta = clock();
                            printf("length = %d\n",length);
            //                printf("start = %lf\n",(double)sta/CLOCKS_PER_SEC);
                            radix_sort();
                            fin = clock();
                            show_result();
                        }
            break;
        case 0:
            //退出程序
            return ;
        default:
            break;
    }
}
int main(int argc, const char * argv[]) {
    //初始化
    init();
    //开始界面
    start();
    //执行排序，输出结果。
    do_sort();
    
    return 0;
}

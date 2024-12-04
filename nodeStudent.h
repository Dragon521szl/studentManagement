#ifndef _nodeStudent_H_
#define _nodeStudent_H_

//本头文件用于封装链表
#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include <string.h>

//定义学生信息结构体

//student对象
typedef struct student{
    long long int id;
    char name[20];
    char classNum[50];
    char sex[10];
}student;

//node
typedef struct node
{
    student* stu;
    struct node* next;
}node;

#endif
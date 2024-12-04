#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include <string.h>
#include "nodeStudent.h"

int LENGTH=4;

//mergelist
node* mergeList(node* left,node* right){
    node* head=(node*)malloc(sizeof(node));
    node* tmp=head;
    //skip head
    while(left!=NULL&&right!=NULL){
        if(strcmp(left->stu->name,right->stu->name)<0){
            tmp->next=left;
            left=left->next;
        }else{
            tmp->next=right;
            right=right->next;
        }
        tmp=tmp->next;
    }
    if(left!=NULL){
        tmp->next=left;
    }else if(right!=NULL){
        tmp->next=right;
    }

    return head->next;
}


node* sortByName(node* head){  //排序（按照姓名）
    if(head->next==NULL||head==NULL){return head;}

    node* slow=head;
    node* fast=head;
    node* sign=NULL;

    //快慢指针找到中间节点
    while(fast->next!=NULL&&fast->next->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
        sign=slow;
    }
    //切断
    node* mid=slow->next;
    slow->next=NULL;
    //归并排序左右列表
    node* leftlist=sortByName(head);
    node* rightlist=sortByName(mid);

    //合并
    return mergeList(leftlist,rightlist);
}

void menu(void)
{
    /*
    void menu();        //呈现菜单
    void loadData();    //1.加载数据
    void saveData();    //2.保存到文件
    void add();         //3.添加
    void search();      //4.查找
    void update();      //5.修改
    void delete();      //6.删除
    void showALL();     //7.显示
    void clearALL();    //8.清空
    void sortByName();  //9.排序（按照姓名）
    void exitSystem();  //exit
    */
    printf( L_PURPLE "\t\t|+---------------------------------------------+|\n");
    printf( L_PURPLE "\t\t||" L_BLACK "**************" YELLOW "学生信息管理系统" L_BLACK "***************" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t|+---------------------------------------------+|\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "1.加载文件数据" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "2.保存到文件中" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "3.添加学生信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "4.查找学生信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "5.修改学生信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "6.删除学生信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "7.显示所有信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "8.清空所有信息" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "9.按照姓名排序" L_BLACK "~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t||" L_BLACK "~~~~~~~~~~~~~~~" L_GREEN "0.exit" L_BLACK "~~~~~~~~~~~~~~~~~~~~~~~~" L_PURPLE "||\n");
    printf( L_PURPLE "\t\t|+---------------------------------------------+|\n" L_BLUE);
} 

void loadData(node *head){    //加载数据

    FILE* file = NULL;
    file = fopen("information.csv", "r");
    if (file != NULL){
        printf(GREEN "打开文件成功！！\n" NONE);
    }else{
        printf(L_RED "失败！！\n" L_BLUE);
        return;
    }

    char line[1024];
    //fgets函数可以逐行读取
    int times=0;
    while(fgets(line,sizeof(line),file)){
        if(times==0){
            times++;
            continue;
        }
        //每一行是一个学生,包含四个数据
        char *token = strtok(line,",");
        long long int id = atoll(token);
        token = strtok(NULL, ",");
        char name[20];
        strncpy(name, token , sizeof(name)-1);
        name[sizeof(name)-1]='\0';
        //printf(GREEN "%s",name);
        token = strtok(NULL, ",");
        char classNum[50];
        strncpy(classNum, token , sizeof(classNum)-1);
        classNum[sizeof(classNum)-1]='\0';
        //printf(GREEN "\n%s\n",classNum);
        token = strtok(NULL, ",");
        char sex[50];
        strncpy(sex, token , sizeof(sex)-1);
        sex[sizeof(sex)-1]='\0';
        //用这四个数据构建新的节点Node
        addStu(head,id,name,classNum,sex);
        printf("data+1\n");

        times++;
        printf("finished\n");
    }

    fclose(file);

    printf("写入完成,已经写入%d个数据",times-1,L_BLUE);
}

void saveData(node* head){    //保存到文件
    FILE* file = fopen("studentList.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(-1);
    }

    node* tmp = head->next;
    while (tmp != NULL) {
        fprintf(file, "%lld\t", tmp->stu->id); // 写入数据
        fprintf(file, "%s\t", tmp->stu->name);
        fprintf(file, "%s\t", tmp->stu->classNum);
        fprintf(file, "%s\n", tmp->stu->sex);
        tmp = tmp->next;
    }

    fclose(file); // 关闭文件
    printf(GREEN "已完成保存,请查看!\n" NONE);
}

void addStu(node* head,long long int id,char NAME[],char CLASSNUM[],char SEX[]){         //添加学生数据
    //先要找到最后一个
    node *tmp=head;
    while(tmp->next!=NULL){
        tmp=tmp->next;
        //结束以后，tmp->next==NULL;
        //tmp就是最后一个节点
    }

    //new一个node
    node *Node=(node*)malloc(sizeof(node));
    //new一个student，并且赋值
    student *Student=(student*)malloc(sizeof(student));
    Student->id=id;
    strncpy(Student->name, NAME, sizeof(Student->name) - 1);
    Student->name[sizeof(Student->name) - 1] = '\0';
    printf(YELLOW "\n%s\n",Student->name);
    strncpy(Student->classNum,CLASSNUM,sizeof(Student->classNum)-1);
    Student->classNum[sizeof(Student->classNum) - 1] = '\0';
    //printf(YELLOW "\n%s\n",Student->classNum);
    //printf(L_PURPLE "\n%s\n",CLASSNUM);
    strncpy(Student->sex,SEX,sizeof(Student->sex)-1);
    Student->sex[sizeof(Student->sex) - 1] = '\0';
    //完成node
    Node->stu=Student;
    Node->next=NULL;

    //让原来最后一个节点的next指向Node
    tmp->next=Node;

    printf(GREEN "已完成输入\n" );
    //free(Node);
}

void search(node* head , long long int id_goal){      //查找
    node *tmp=head->next;
    if(tmp==NULL){
        printf(L_RED "NULL ERROR\n");
        return;
    }
    while(tmp!=NULL){
        if(tmp->stu->id==id_goal){
            printf(GREEN "%s\n",tmp->stu->name);
            return;
        }
        tmp=tmp->next;
    }
    printf(L_RED "NOT EXIST\n");
    return;
}

void update(node* head,char name_goal[]){      //修改联系人
    node *tmp=head->next;
    if(tmp==NULL){
        printf(L_RED "NULL ERROR\n");
        return;
    }
    while(tmp!=NULL){
        if(strcmp(name_goal,tmp->stu->name)){
            //修改
            printf(L_BLUE "请输入caseCode:\n");
            printf(WHITE "1--id\t2--name\t3--classNum\t4--sex");
            int caseCode=0;
            scanf("%d",&caseCode);
            switch(caseCode){
                case 1:
                    printf(L_BLUE "请输入new_id\n" WHITE);
                    long long int new_id;
                    scanf("%lld",&new_id);
                    tmp->stu->id=new_id;
                    break;
                case 2:
                    printf(L_BLUE "请输入new_name\n" WHITE);
                    char new_name[20];
                    scanf("%s",new_name);
                    strncpy(tmp->stu->name,new_name,sizeof(tmp->stu->name)-1);
                    break;
                case 3:
                    printf(L_BLUE "请输入new_classNum\n" WHITE);
                    char new_classNum[50];
                    scanf("%s",new_classNum);
                    strncpy(tmp->stu->classNum,new_classNum,sizeof(tmp->stu->classNum)-1);
                    break;
                case 4:
                    printf(L_BLUE "请输入new_sex\n" WHITE);
                    char new_sex[50];
                    scanf("%s",new_sex);
                    strncpy(tmp->stu->sex,new_sex,sizeof(tmp->stu->sex)-1);
                    break;
                default:
                    printf(L_RED "来捣乱的\n");
                    return;
            }
            printf(GREEN "已修改\n");
            return;
        }
        tmp=tmp->next;
    }
    printf(L_RED "NOT EXIST\n");
    return;
}

void delete(node* head,char name_goal[]){      //删除联系人
    node *tmp=head->next;
    node *beforePos=head;
    if(tmp==NULL){
        printf(L_RED "NULL ERROR\n");
        return;
    }
    while(tmp!=NULL){
        if(strcmp(name_goal,tmp->stu->name)==0){
            //删除
            beforePos->next=tmp->next;
            tmp->next=NULL;
            printf(GREEN "已删除\n");
            return;
        }
        tmp=tmp->next;
        beforePos=beforePos->next;
    }
    printf(L_RED "NOT EXIST\n");
    return;
}

void showALL(node* head){     //展示所有学生数据
    node* tmp=head->next;
    //id	name	classNum	sex
    printf(YELLOW "\t\tID\t\t" L_BLACK "|" );
    printf(YELLOW "\t\tname\t\t" L_BLACK "|" );
    printf(YELLOW "\t\tclassNum\t\t" L_BLACK "|");
    printf(YELLOW "\t\tsex\n" NONE);
    //只要tmp->next不是NULL,就说明此处需要打印
    //打印后移动到下一个节点
    if(tmp==NULL){
        printf(L_RED "error null\n");
        return;
    }
    while(tmp->next!=NULL){
        // for(int i=0;i<LENGTH;++i)
        printf(WHITE "\t\t%lld\t\t" , tmp->stu->id , L_BLACK "|" );
        printf(WHITE "\t\t%s\t\t" , tmp->stu->name , L_BLACK "|" );
        printf(WHITE "\t\t%s\t\t" , tmp->stu->classNum ,L_BLACK "|" );
        printf(WHITE "\t\t\t%s" ,tmp->stu->sex );
        printf("\n\n");
        tmp=tmp->next;
    }
    printf(WHITE "\t\t%lld\t\t" , tmp->stu->id , L_BLACK "|" );
    printf(WHITE "\t\t%s\t\t" , tmp->stu->name , L_BLACK "|" );
    printf(WHITE "\t\t%s\t\t" , tmp->stu->classNum ,L_BLACK "|" );
    printf(WHITE "\t\t\t%s\n" ,tmp->stu->sex , NONE);
	printf("\n" L_BLUE);
}

void clearALL(node* head){    //清空所有
    head->next=NULL;
    printf(L_RED "ALL CLEAR\n");
}

void exitSystem(void){  //退出程序
    printf(L_RED "\nexit system successfully\n" NONE);
}

#endif
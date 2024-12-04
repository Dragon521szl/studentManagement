#include "nodeStudent.h"
#include "function.h"
#include "color.h"

//声明功能
void menu(void);        //呈现菜单
void loadData(node* head);    //加载数据
void saveData(node* head);    //保存到文件
void addStu(node* head,long long int id,char NAME[],char CLASSNUM[],char SEX[]);         //添加联系人
void search(node* head , long long int id_goal);      //查找
void update(node* head,char name_goal[]);      //修改联系人
void delete(node* head,char name_goal[]);      //删除联系人
void showALL(node* head);     //展示所有联系人
void clearALL(node* head);    //清空所有联系人
node* sortByName(node* head);  //排序（按照姓名）
void exitSystem(void);  //exit

//指示变量
int n;

int main(){

    //initList
    node *head=(node*)malloc(sizeof(node));
    head->next=NULL;
    //strncpy(head->stu->name,"a",sizeof(head->stu->name)-1);

    //first time
    menu();
    printf(L_BLUE "choose function:\n");
    scanf("%d",&n);

    //in loop
    while (n)
    {
        //try catch   
        while(n>9||n<0){
            printf(L_RED "\n %d NOT FOUND\n",n);
            printf(RED "\nchoose another function:\n" L_BLUE);
            scanf("%d",&n);
        }

        //执行对应function
        switch (n)
        {
        case 1:
            //提示
            printf(L_BLUE "注意:请保证在当前文件夹下有information.csv文件(y/N)\n" WHITE);
            while(getchar()!='\n');
            char isok_file;
            scanf("%c",&isok_file);
            if(isok_file=='y'){
                loadData(head);
            }else if(isok_file=='N'){
                printf(GREEN "操作取消\n" WHITE);
            }else{
                printf(RED "无效操作\n" WHITE);
            }
            break;
        case 2:
            // printf(L_BLUE "请输入文件名:\n");
            // char fileName[100];
            saveData(head);
            break;
        case 3:
            long long int id_tmp;
            char NAME_tmp[50];
            char CLASSNUM_tmp[20];
            char SEX_tmp[50];
            printf(L_BLUE "请输入学生信息:id name classnumber sex\n" WHITE);
            //scanf(WHITE "%lld %s %s %s\n",&id_tmp,NAME_tmp,CLASSNUM_tmp,SEX_tmp);
            scanf("%lld",&id_tmp);
            scanf("%s",NAME_tmp);
            scanf("%s",CLASSNUM_tmp);
            scanf("%s",SEX_tmp);
            NAME_tmp[sizeof(NAME_tmp)-1]='\0';
            CLASSNUM_tmp[sizeof(CLASSNUM_tmp)-1]='\0';
            SEX_tmp[sizeof(SEX_tmp)-1]='\0';
            printf(GREEN "!!收到!!\n");
            addStu(head,id_tmp,NAME_tmp,CLASSNUM_tmp,SEX_tmp); 
            break;
        case 4:
            printf(L_BLUE "请输入学号:\n" WHITE);
            long long int id_goal=0;
            scanf("%lld",&id_goal);
            search(head,id_goal);
            break;
        case 5:            
            printf(L_BLUE "请输入要修改学生的姓名:\n" WHITE);
            char name_goal_update[50];
            scanf("%s",name_goal_update);
            update(head,name_goal_update);
            break;
        case 6:
            printf(L_BLUE "请输入要删除学生的姓名:\n" WHITE);
            char name_goal_delete[50];
            scanf("%s",name_goal_delete);
            delete(head,name_goal_delete);
            break;
        case 7:
            showALL(head);
            break;
        case 8:
            printf(RED "WARNING:这个操作将删错所有数据(y/N)\n" WHITE);
            while(getchar()!='\n');
            char isok_claerall;
            scanf("%c",&isok_claerall);
            if(isok_claerall=='y'){
                clearALL(head);
            }else if(isok_claerall=='N'){
                printf(GREEN "操作取消\n");
            }else{
                printf(RED "无效操作\n");
            }
            break;
        case 9: 
            //下面这段返回的的是第一个,而不是head          
            //head=sortByName(head->next);
            head->next=sortByName(head->next);
            printf(GREEN "!!已完成排序!!\n");
            break;
        default :
            continue;
        }

        //完成当前任务，执行下一个
        printf(L_BLUE "\nchoose function:\n" WHITE);
        scanf("%d",&n);    
    }

    free(head);
    exitSystem();
    return 0;    
}

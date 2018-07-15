#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Student

{
    char Num[20];
    char Name[20];
    char sex[10];
    float Score[5];
    float sum;
    float Average;
    struct Student *next;
};


void passwd();

struct Student *ReadInfo();

struct Student *Insert(struct Student *head);

struct Student *Modify(struct Student *head);
struct Student *SearchByNum(char id[],struct Student *head);
struct Student *SearchByName(char name[],struct Student *head);
float Avg(struct Student *p);
float Sum(struct Student *p);

struct Student *Delete(struct Student *head);

void SelectByName(struct Student *head);
void DisplaySingle(struct Student *p);

struct Student *Sort(struct Student *head);
struct Student *SortById(struct Student *head);
struct Student *SortBySum(struct Student *head);
void Display(struct Student *head);

void DisplayBy(struct Student *head);
void DisplayByAver(struct Student *head);
void DisplayByHighScore(struct Student *head);
void DisplayByLowScore(struct Student *head);

void WriteInfo(struct Student *head);


int main()
{
    int model, i=0;
    struct Student *head;
    
    passwd();
    printf("\n------ 欢迎来到学生成绩管理系统------\n");
    head=ReadInfo();
    while (1)
    {
        if (i > 0) {
            printf("-----------欢迎回来！------------\n");
        }
        printf("\t1. 录入学生成绩\n");
        printf("\t2. 修改学生成绩\n");
        printf("\t3. 删除学生成绩\n");
        printf("\t4. 按姓名查询学生成绩\n");
        printf("\t5. 成绩排序\n");
        printf("\t6. 按不同方式显示学生成绩\n");
        printf("\t7. 退出\n");
        printf("--------------------------\n");
        printf("请选择模式(1-6):");
        scanf("%d",&model);
        switch(model) {
            case 1:
                head=Insert(head);
                break;
            case 2:
                head=Modify(head);
                break;
            case 3:
                head=Delete(head);
                break;
            case 4:
                SelectByName(head);
                break;
            case 5:
                head=Sort(head);
                break;
            case 6:
                DisplayBy(head);
                break;
            case 7:
                return 0;
                break;
            case 8:
                Display(head);
                break;
            default:
                printf("请输入正确的模式号！\n");
        }
        WriteInfo(head);
        i++;
    }
}


void passwd()
{
    char Id[10];
    char id[10]="su";
    char Key[10]="1234";
    char key[10];
    
    printf("请输入用户名：");
    scanf("%s", Id);
    while (strcmp(Id, id) != 0) {
        printf("无此用户，请重新登录！\n");
        printf("请输入用户名：");
        scanf("%s", Id);
    }
    printf("请输入密码：");
    scanf("%s", key);
    while (strcmp(key, Key)) {
        printf("密码错误，请重新输入！\n");
        printf("请输入密码：");
        scanf("%s", key);
    }
}



struct Student *ReadInfo()
{
    FILE *fp;
    struct Student *head,*p1,*p2;
    
    if ((fp=fopen("Database.txt","rb"))==NULL) {
        printf("(您还没写入学生信息!)\n");
        return NULL;
    }
    else {
        head=p2=p1=(struct Student *)malloc(sizeof(struct Student));
        fread(p1,sizeof(struct Student),1,fp);
        while(!feof(fp))
        {
            p1=(struct Student *)malloc(sizeof(struct Student));
            fread(p1,sizeof(struct Student),1,fp);
            p2->next=p1;
            if (feof(fp)) {
                break;
            }
            p2=p1;
        }
    }
    p2->next=NULL;
    fclose(fp);
    return head;
}


struct Student *Insert(struct Student *head)
{
    struct Student *p,*p1,*p2;
    int i;
    
    for (p=head; p!=NULL; p=p->next) {
    }
    p2=p1=(struct Student *)malloc(sizeof(struct Student));
    printf("请输入学号:");
    scanf("%s",p1->Num);
    printf("请输入姓名:");
    scanf("%s",p1->Name);
    printf("请输入性别:");
    scanf("%s",p1->sex);
    for (i = 0; i < 5; i++) {
        printf("请输入成绩%d:",i+1);
        scanf("%f",&p1->Score[i]);
    }
    p1->Average=Avg(p1);
    p1->sum=Sum(p1);
    if (head==NULL) {
        head=p1;
    }
    else{
        p=p1;
    }
    printf("是否继续?(y/n)");
    getchar();
    if (getchar() == 'n') {
        p1->next=NULL;
    }
    else {
        while(1) {
            p1=(struct Student *)malloc(sizeof(struct Student));
            printf("请输入学号:");
            scanf("%s",p1->Num);
            printf("请输入姓名:");
            scanf("%s",p1->Name);
            printf("请输入性别:");
            scanf("%s",p1->sex);
            for (i = 0; i < 5; i++) {
                printf("请输入成绩%d:",i+1);
                scanf("%f",&p1->Score[i]);
            }
            p1->Average=Avg(p1);
            p1->sum=Sum(p1);
            p2->next=p1;
            p2=p1;
            printf("是否继续?(y/n)");
            getchar();
            if (getchar() =='n')
            {
                p1->next=NULL;
                break;
            }
        }
    }
    return head;
}



struct Student *Modify(struct Student *head)
{
    struct Student *p;
    int model;
    
    printf("1.按学号修改\n");
    printf("2.按姓名修改\n");
    scanf("%d", &model);
    while (model != 1 && model != 2) {
        printf("请输入正确的模式号！\n");
        printf("1.按学号修改\n");
        printf("2.按姓名修改\n");
        scanf("%d", &model);
    }
    
    while(model == 1) {
        int i;
        char id[20];
        printf("请输入要修改的学生的学号:");
        scanf("%s",id);
        p=SearchByNum(id,head);
        if (p==NULL) {
            printf("学生不存在!\n");
        }
        else {
            printf("你要修改的学生信息为:\n");
            DisplaySingle(p);
            printf("-- 请输入新值--\n");
            printf("请输入学号:");
            scanf("%s",p->Num);
            printf("请输入姓名:");
            scanf("%s",p->Name);
            printf("请输入性别:");
            scanf("%s",p->sex);
            for (i = 0; i < 5; i++) {
                printf("请输入成绩:");
                scanf("%f",&p->Score[i]);
            }
            p->Average=Avg(p);
            p->sum=Sum(p);
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar()=='n') {
            break;
        }
    }
    
    while(model == 2) {
        int i;
        char name[20];
        printf("请输入要修改的学生的姓名:");
        scanf("%s", name);
        p=SearchByName(name,head);
        if (p==NULL) {
            printf("学生不存在!\n");
        }
        else {
            printf("你要修改的学生信息为:\n");
            DisplaySingle(p);
            printf("-- 请输入新值--\n");
            printf("请输入学号:");
            scanf("%s",p->Num);
            printf("请输入姓名:");
            scanf("%s",p->Name);
            printf("请输入性别:");
            scanf("%s",p->sex);
            for (i = 0; i < 5; i++) {
                printf("请输入成绩:");
                scanf("%f",&p->Score[i]);
            }
            p->Average=Avg(p);
            p->sum=Sum(p);
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar()=='n') {
            break;
        }
    }
    
    return head;
}



float Avg(struct Student *p)
{
    return (p->Score[0]+p->Score[1]+p->Score[2]+p->Score[3]+p->Score[4])/5;
    
}



float Sum(struct Student *p)
{
    return (p->Score[0]+p->Score[1]+p->Score[2]+p->Score[3]+p->Score[4]);
}


struct Student *Delete(struct Student *head)
{
    int model;
    struct Student *p,*p1;
    
    printf("1.按学号删除\n");
    printf("2.按姓名删除\n");
    scanf("%d", &model);
    while (model != 1 && model != 2) {
        printf("请输入正确的模式号！\n");
        printf("1.按学号删除\n");
        printf("2.按姓名删除\n");
        scanf("%d", &model);
    }
    
    while(model == 1) {
        char id[20];
        printf("请输入要删除的学生的学号:");
        scanf("%s",id);
        p=SearchByNum(id,head);
        if (p==NULL) {
            printf("学生不存在!\n");
        }
        else {
            printf("你要删除的学生信息为:\n");
            DisplaySingle(p);
            printf("是否真的要删除?(y/n)");
            getchar();
            if (getchar()=='y') {
                if (p==head) {
                    head=head->next;
                }
                else {
                    for (p1=head;p1->next!=p;p1=p1->next){
                    }
                    p1->next=p->next;
                }
            }
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar()=='n') {
            break;
        }
    }
    while(model == 2) {
        char name[20];
        printf("请输入要删除的学生的姓名:");
        scanf("%s",name);
        p=SearchByName(name,head);
        if (p==NULL) {
            printf("学生不存在!\n");
        }
        else {
            printf("你要删除的学生信息为:\n");
            DisplaySingle(p);
            printf("是否真的要删除?(y/n)");
            getchar();
            if (getchar()=='y') {
                if (p==head) {
                    head=NULL;
                }
                else {
                    for (p1=head;p1->next!=p;p1=p1->next){
                    }
                    p1->next=p->next;
                }
            }
        }
        printf("是否继续?(y/n)");
        getchar();
        if (getchar()=='n') {
            break;
        }
    }
    return head;
}


void SelectByName(struct Student *head)
{
    struct Student *p;
    
    while(1) {
        char name[20];
        printf("请输入要查询的学生的姓名:");
        scanf("%s",name);
        getchar();
        p=SearchByName(name,head);
        if (p==NULL) {
            printf("学生不存在!\n");
        }
        else {
            printf("你要查询的学生信息为:\n");
            DisplaySingle(p);
        }
        printf("是否继续?(y/n)");
        if (getchar()=='n') {
            break;
        }
    }
}


struct Student *SearchByNum(char id[],struct Student *head)
{
    struct Student *p1;
    
    for (p1=head;p1!=NULL;p1=p1->next) {
        if (strcmp(p1->Num,id)==0) {
            return p1;
        }
    }
    return NULL;
}


struct Student *SearchByName(char name[],struct Student *head)
{
    struct Student *p1;
    
    p1=head;
    for (p1=head; p1!=NULL; p1=p1->next) {
        if (strcmp(p1->Name,name)==0) {
            return p1;
        }
    }
    return NULL;
}


void DisplaySingle(struct Student *p)
{
    printf("%10s%10s%12s%10s%10s%10s%10s%12s%15s%12s\n","学号","姓名","性别","成绩","成绩","成绩","成绩","成绩","平均成绩","总成绩");
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("%8s%8s%8s%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f\n",p->Num,p->Name,p->sex,
           p->Score[0],p->Score[1],p->Score[2],p->Score[3],p->Score[4],p->Average,p->sum);
}


struct Student *Sort(struct Student *head)
{
    int model;
    
    printf("1.按学号排序\n");
    printf("2.按总成绩排序\n");
    scanf("%d", &model);
    switch (model) {
        case 1:
            head=SortById(head);
            Display(head);
            break;
        case 2:
            head=SortBySum(head);
            Display(head);
            break;
        default:
            printf("请输入正确的模式！\n");
            break;
    }
    return head;
}


struct Student *SortById(struct Student *head)
{
    struct Student *p1,*p2,*Next;
    struct Student tmp;
    if (head==NULL) {
        printf("没有学生信息！\n");
    }
    else {
        for (p1=head;p1->next!=NULL;p1=p1->next) {
            for (p2=p1->next;p2!=NULL;p2=p2->next) {
                if (strcmp(p1->Num,p2->Num)>0) {
                    tmp=*p2;
                    *p2=*p1;
                    *p1=tmp;
                    Next=p2->next;
                    p2->next=p1->next;
                    p1->next=Next;
                }
            }
        }
    }
    return head;
}


struct Student *SortBySum(struct Student *head)
{
    struct Student *p1,*p2,*Next;
    struct Student tmp;
    if (head==NULL) {
        printf("没有学生信息！\n");
    }
    else {
        for (p1=head;p1->next!=NULL;p1=p1->next) {
            for (p2=p1->next;p2!=NULL;p2=p2->next) {
                if (p1->sum<p2->sum) {
                    tmp=*p2;
                    *p2=*p1;
                    *p1=tmp;
                    Next=p2->next;
                    p2->next=p1->next;
                    p1->next=Next;
                }
            }
        }
    }
    return head;
}


void Display(struct Student *head)
{
    struct Student *p1;
    p1=head;
    printf("%10s%10s%12s%10s%10s%10s%10s%12s%15s%12s\n","学号","姓名","性别","成绩","成绩","成绩","成绩","成绩","平均成绩","总成绩");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (p1=head; p1!=NULL; p1=p1->next) {
        printf("%8s%8s%8s%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f\n",p1->Num,p1->Name,p1->sex,p1->Score[0],
               p1->Score[1],p1->Score[2],p1->Score[3],p1->Score[4],p1->Average,p1->sum);
        
    }
    printf("\n");
}

void DisplayBy(struct Student *head)
{
    int model;
    
    printf("1.显示每门课程中低于平均分的学生信息\n");
    printf("2.显示成绩在90分以上的学生信息\n");
    printf("3.每门科目中不及格的学生信息\n");
    scanf("%d", &model);
    switch (model) {
        case 1:
            DisplayByAver(head);
            break;
        case 2:
            DisplayByHighScore(head);
            break;
        case 3:
            DisplayByLowScore(head);
            break;
        default:
            break;
    }
}


void DisplayByAver(struct Student *head)
{
    struct Student *p1;
    int i,j,num=0;
    int flag1 = 0;
    int flag2 = 0;
    float aver[5];
    float sum[5]={0,0,0,0,0};
    
    for (i = 0; i < 5; i++) {
        for (p1=head; p1!=NULL; p1=p1->next) {
            sum[i] = sum[i] + p1->Score[i];
            num++;
        }
        aver[i] = sum[i] / num;
        p1=head;
    }
    printf("各科平均分：\n");
    for (i=0; i<5; i++) {
        printf("Score%d: %.2f ", i+1, aver[i]);
    }
    printf("\n");
    printf("----------------------------\n");
    printf("以下同学单门课程低于平均分：\n");
    p1=head;
    for (p1=head; p1!=NULL; p1=p1->next) {
        if (p1->Score[0] < aver[0] ||
            p1->Score[1] < aver[1] ||
            p1->Score[2] < aver[2] ||
            p1->Score[3] < aver[3] ||
            p1->Score[4] < aver[4] ) {
            printf("%s %s ", p1->Num, p1->Name);
            flag1 = 1;
            flag2 = 1;
        }
        else{
            flag1 = 0;
        }
        for (j=0; j<5; j++) {
            if (p1->Score[j] < aver[j]) {
                printf("Score%d: %.2f ", j+1, p1->Score[j]);
            }
        }
        if (flag1 == 1) {
            printf("\n");
        }
    }
    if (flag2 == 0) {
        printf("无学生信息!\n");
    }
}


void DisplayByHighScore(struct Student *head)
{
    int i;
    int flag1 = 0;
    int flag2 = 0;
    struct Student *p1;
    p1=head;
    printf("----------------------------\n");
    printf("以下同学单门课程在90分以上：\n");
    for (p1=head; p1!=NULL; p1=p1->next) {
        if (p1->Score[0] >= 90 ||
            p1->Score[1] >= 90 ||
            p1->Score[2] >= 90 ||
            p1->Score[3] >= 90 ||
            p1->Score[4] >= 90 ) {
            printf("%s %s ", p1->Num, p1->Name);
            flag2 = 1;
            flag1 = 1;
        }
        else{
            flag1 = 0;
        }
        for (i=0; i<5; i++) {
            if (p1->Score[i]>=90) {
               printf("Score%d: %.2f ", i+1,p1->Score[i]);
            }
        }
        if (flag1 == 1) {
            printf("\n");
        }
    }
    if (flag2 == 0) {
        printf("无学生信息!\n");
    }
}


void DisplayByLowScore(struct Student *head)
{
    struct Student *p1;
    p1=head;
    int i;
    int flag1 = 0;
    int flag2 = 0;
    printf("----------------------------\n");
    printf("以下同学单门课程不及格：\n");
    for (p1=head; p1!=NULL; p1=p1->next) {
        if (p1->Score[0] < 60 ||
            p1->Score[1] < 60 ||
            p1->Score[2] < 60 ||
            p1->Score[3] < 60 ||
            p1->Score[4] < 60 ) {
            printf("%s %s ", p1->Num, p1->Name);
            flag1 = 1;
            flag2 = 1;
        }
        else {
            flag1 = 0;
        }
        for (i=0; i<5; i++) {
            if (p1->Score[i]<60) {
                printf("Score%d: %.2f ", i+1, p1->Score[i]);
            }
        }
        if (flag1 == 1) {
            printf("\n");
        }
    }
    if (flag2 == 0) {
        printf("无学生信息!\n");
    }
}


void WriteInfo(struct Student *head)
{
    FILE *fp;
    struct Student *p1;
    p1=head;
    if ((fp=fopen("Database.txt","wb"))==NULL) {
        printf("不能打开文件!\n");
        return;
    }
    for (p1=head; p1!=NULL; p1=p1->next) {
        if (fwrite(p1,sizeof(struct Student),1,fp)!=1) {
            printf("写入文件错误!\n");
        }
    }
    fclose(fp);
}



#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;          //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{                //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
	int is_init;               //在多表操作中用到，值为1表示该表已经初始化，值为0表示还未初始化 
}SqList;

/*-----page 19 on textbook ---------*/
status compare(int, int);
void visit(ElemType *a, int len);
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
status LocateElem(SqList L, ElemType e, int (*func) (int, int));       //需要调用函数compare进行查找，使用函数指针 
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);
status NextElem(SqList L, ElemType cur, ElemType &next_e);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L, void (*func_2) (ElemType *, int));       //需要调用函数visit进行访问，使用函数指针
status WriteFile(SqList L);
status ReadFile(SqList &L);
/*--------------------------------------------*/
int main(void){
	SqList L[100];                  //定义线性表类型的结构数组，固定长度为100，即可以操作100个表
	for(int i=0; i<100; i++){       //将每一个元素的is_init初始化为0
		L[i].is_init = 0;
	} 
	
	int op = 1, count = 0;  //count表示第几次操作，初始为0时（即第一次输入）必须为1，否则无法创建线性表
    int num, num_2;         //num为将要进行操作的表编号，num_2是为了便于后面再次输入的临时变量 
    printf("请输入要操作的线性表编号：\n");
	scanf("%d", &num);
	while(op){
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure\n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList    8. PriorElem\n");
        printf("    	  3. ClearList      9. NextElem \n");
        printf("    	  4. ListEmpty     10. ListInsert\n");
        printf("    	  5. ListLength    11. ListDelete\n");
        printf("    	  6. GetElem       12. ListTraverse\n");
        printf("          13. WriteFile    14. ReadFile\n");
        printf("          15. Choose\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("\t请选择你的操作[0~15]:");
        scanf("%d", &op);
        while(L[num].is_init == 0 && op != 1){
        	printf("\n线性表未创建！\n");
        	scanf("%d",&op);
		}

        switch(op){
            case 1:
            	InitList(L[num]);
            	L[num].is_init = 1;           //作为该线性表已经初始化的标记 
             	getchar();getchar();
             	break;
            case 2:
             	DestroyList(L[num]);
				printf("\n\t线性表已销毁\n");
				count = 0;                    //此后需要重新创建线性表，所以count置为0，再输入大于1的数即为非法值 
             	getchar();getchar();
             	break;
            case 3:
             	ClearList(L[num]);            //将表清空 
                getchar();getchar();
             	break;
            case 4:
             	ListEmpty(L[num]);            //判断表是否为空 
             	getchar();getchar();
             	break;
            case 5:
             	ListLength(L[num]);          //求表长 
              	getchar();getchar();
             	break;
            case 6:                          //根据元素下标查找元素的值 
             	printf("\n\t请输入查找元素下标：\n");
             	int i, e;
             	scanf("%d", &i);
             	GetElem(L[num], i, e);
             	getchar();getchar();
             	break;
            case 7:                          //根据元素的值查找元素下标 
             	printf("\n\t请输入要查找元素的值：\n");
             	int e_2;
             	scanf("%d", &e_2);
				LocateElem(L[num], e_2, compare); 
             	getchar();getchar();
             	break;
            case 8:                          //根据元素的值查找前驱 
             	printf("\n\t请输入要查找的元素，将显示它前一个元素的值：\n");
             	int cur, pre_e;
				scanf("%d", &cur);
				PriorElem(L[num], cur, pre_e);
             	getchar();getchar();
             	break;
            case 9:                          //根据元素的值查找后继 
             	printf("\n\t请输入要查找的元素，将显示它后一个元素的值：\n");
             	int cur_2, next_e;
				scanf("%d", &cur_2);
				NextElem(L[num], cur_2, next_e);
             	getchar();getchar();
             	break;
            case 10:                         //插入元素 
             	printf("\n\t请输入要插入的位置和新元素的值：\n");
             	int pos, val;
             	scanf("%d %d", &pos, &val);
             	ListInsert(L[num], pos, val);
             	getchar();getchar();
             	break;
            case 11:                         //删除元素 
             	printf("\n\t请输入要删除的元素位置：\n");
             	int pos_2, e_3;
             	scanf("%d", &pos_2);
             	ListDelete(L[num], pos_2, e_3);
             	getchar();getchar();
             	break;
            case 12:                         //线性表的遍历 
		        if(!ListTraverse(L[num], visit))
		        	printf("线性表为空表");
             	getchar();getchar();
             	break;
            case 13:                         //将一个线性表写入文件 
            	WriteFile(L[num]);
            	break;
            case 14:                         //从已有文件中读取线性表 
            	ReadFile(L[num]);
            	break;
            case 15:                         //切换至另一线性表进行操作 
            	printf("\t请输入想要切换的线性表编号：\n");
            	scanf("%d", &num_2);
            	num = num_2;
				break;
            case 0:                          //输入0终止程序 
             	break;
        }//end of switch
      }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()


status compare(int x1, int x2){
	if(x1 == x2)
		return TRUE;
	else
		return FALSE;
}


void visit(ElemType *a, int len){
	int i;
	for(i=0; i<len; i++){
		printf("%d ", a[i]);
	}
}

/*--------page 23 on textbook --------------------*/
status InitList(SqList &L){    //初始化，函数序号为1 
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem){
    	printf("\t分配空间失败，线性表初始化失败");
    	exit(OVERFLOW);
	}
	
	L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    printf("\t线性表创建成功");
	return OK;
}


status DestroyList(SqList &L){  //销毁，函数序号为2 
	L.is_init = 0;
	free(L.elem);
	return OK;
}


status ClearList(SqList &L){    //清空，函数序号为3 
	if(L.length == 0){
		printf("\t线性表已经为空，无需清空");
		return FALSE; 
	}
	
	int i;
	for(i=0; i<L.length; i++){
		L.elem[i] = 0;
	}
	L.length = 0;
	printf("\t线性表已清空");
	return OK;
}


status ListEmpty(SqList L){   //判断是否为空，函数序号为4 
	if(L.length == 0){
		printf("\t线性表为空");
		return TRUE; 
	}
	
	else{
		printf("\t线性表不为空");
		return FALSE;
	}
}


int ListLength(SqList L){      //求表长，函数序号为5 
	printf("\t线性表的长度为%d", L.length);
	return L.length;
}


status GetElem(SqList L,int i,ElemType &e){  //查找元素值，函数序号为6 
	if(i<1 || i>L.length){
		printf("\t输入下标不合法");
		return ERROR;
	}
		
	e = L.elem[i-1];
	printf("\t第%d个元素为%d", i, e);
	return OK;
}


status LocateElem(SqList L, ElemType e, int (*func) (int x1, int x2)){   //查找下标，函数序号为7 
	int j;
	for(j=0; j<L.length; j++){
		if(func(L.elem[j], e)){
			printf("\t该元素的位置在第%d个",j+1);
			return j+1;
		}
	}
	
	if(j == L.length){
		printf("\t该元素不在线性表中");
		return FALSE;
	}
}


status PriorElem(SqList L, ElemType cur, ElemType &pre_e){   //查找前驱，函数序号为8 
	int i;
	for(i=0; i<L.length; i++){
		if(L.elem[i] == cur)
			break;
	}
	
	if(i == 0){
		printf("该元素为首元素，不存在后继");
		return ERROR;
	}
	else if(i > L.length - 1){
		printf("该元素不在表中");
		return ERROR;
	}
	
	pre_e = L.elem[i-1];
	printf("\t元素%d之前的元素为%d", cur, pre_e);
	return OK;
}


status NextElem(SqList L,ElemType cur,ElemType &next_e){   //查找后继，函数序号为9 
	int i;
	for(i=0; i<L.length; i++){
		if(L.elem[i] == cur)
			break;
	}
	
	if(i == L.length - 1){
		printf("该元素为尾元素，不存在后继");
		return ERROR;
	}
	else if(i > L.length - 1){
		printf("该元素不在表中");
		return ERROR;
	}
	
	next_e = L.elem[i+1];
	printf("\t元素%d之后的元素为%d", cur, next_e);
	return OK;
}


status ListInsert(SqList &L,int i,ElemType e){            //插入，函数序号为10 
	if(i<1 || i>L.length+1){
		printf("\t输入下标不合法");
		return ERROR;
	}
		
	if(L.length >= L.listsize){                           //需要判断线性表是否满，如果是，则要多分配一些空间 
		ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase){
			printf("\t溢出，分配失败");
			exit(OVERFLOW);
		}
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	
	ElemType *q = &(L.elem[i-1]);
	ElemType *p = &(L.elem[L.length-1]);
	for(; p>=q; p--)                                      //必须从最后一个元素开始操作 
		*(p+1) = *p;                                      //在插入位置之后的每一个元素向后移动
	*q = e;
	L.length ++;
	printf("\t插入成功"); 
	return OK;
}


status ListDelete(SqList &L, int i, ElemType &e){   //删除，函数序号为11 
	if(i<1 || i>L.length){
		printf("\t输入下标不合法");
		return ERROR;
	}
	
	ElemType *p = &(L.elem[i-1]);
	e = *p;
	ElemType *q = L.elem + L.length - 1;
	q = L.elem + L.length - 1;
	for(++p; p<=q; ++p)                             //必须删除元素的后继开始操作 
		*(p-1) = *p;                                //在删除位置之后的每一个元素向前移动 
	L.length --;
	printf("\t删除成功"); 
	return OK;
}


status ListTraverse(SqList L, void (*func_2) (int *a, int len)){  //函数序号为12 
    int i;
    printf("\n---------------all elements ------------------\n");
    func_2(L.elem, L.length);
    printf("\n------------------ end -----------------------\n");
    return L.length;
}


status WriteFile(SqList L){               //写入文件，函数序号为13 
	FILE *fp; 
	printf("请输入文件名：");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"wb"))==NULL)
	{
		printf("打开文件时出错\n ");
		return ERROR;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	printf("已成功写入文件\n");
	fclose(fp);
	return OK;
}


status ReadFile(SqList &L){                //读取文件，函数序号为14 
	FILE *fp;
	L.length = 0;
	printf("请输入想要读取的文件名：\n");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"rb"))==NULL)
		{
			printf("打开文件时错误\n ");
			system("pause");
			return ERROR;
		}
	while(fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
	L.length ++;
	printf("读取成功\n");
	fclose(fp);
	return OK; 
}


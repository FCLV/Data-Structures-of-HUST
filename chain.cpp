#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;          //数据元素类型定义
typedef struct node{           //节点定义
	ElemType data;
	struct node *next;
}LNode;

status compare(int, int);
status visit(ElemType *a);
LNode* InitList(LNode *Ins, int);
status DestroyList(LNode *Ins, int);
status ClearList(LNode *L);
status ListEmpty(LNode *L);
status ListLength(LNode *L);
status GetElem(LNode *L, int i, ElemType &e);
status LocateElem(LNode *L, ElemType e, int (*func) (int, int));       //需要调用函数compare进行查找，使用函数指针 
status PriorElem(LNode *L, ElemType cur, ElemType &pre_e);
status NextElem(LNode *L, ElemType cur, ElemType &next_e);
status ListInsert(LNode *L, int i, ElemType e);
status ListDelete(LNode *L, int i, ElemType &e);
status ListTraverse(LNode *L);       //需要调用函数visit进行访问，使用函数指针
status WriteFile(LNode *L);
status ReadFile(LNode *L);

int main(void){
	LNode Instructor[101];          //定义节点类型的数组，固定长度为100，即可以操作100个表，每一个元素都是头指针
	for(int i=0; i<101; i++){       //先将每一个以后要指向表头的指针指向NULL 
		Instructor[i].next = InitList(Instructor, i); 
		Instructor[i].data = 0;     //为0表示未初始化，为1表示已经初始化 
		
}
	
	int op = 1;
    int num, num_2;                 //num为将要进行操作的表编号，num_2是为了选15号时再次输入的临时变量 
    printf("请输入要操作的线性表编号：\n");
	scanf("%d", &num);
	
	Begin:                          //从多表操作切换过来 
	LNode *L = Instructor[num].next;
	while(op){
        system("cls");
		printf("\n\n");
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
        while(!Instructor[num].data && op != 1){
        	printf("\n线性表未创建！\n");
        	scanf("%d",&op);
		}
		
	        switch(op){
	            case 1:
	            	if(L)
						printf("\t%d号表创建成功\n", num);
					Instructor[num].data = 1;
					getchar();getchar();
					break;
				case 2:
	             	DestroyList(Instructor, num);
					printf("\n\t线性表已销毁\n");
	             	getchar();getchar();
	             	break;
	            case 3:
	             	ClearList(L);            //将表清空 
	                getchar();getchar();
	             	break;
	            case 4:
	             	ListEmpty(L);            //判断表是否为空 
	             	getchar();getchar();
	             	break;
	            case 5:
	             	ListLength(L);          //求表长 
	              	getchar();getchar();
	             	break;
	            case 6:                          //根据元素下标查找元素的值 
	             	printf("\n\t请输入查找元素下标：\n");
	             	int i, e;
	             	scanf("%d", &i);
	             	GetElem(L, i, e);
	             	getchar();getchar();
	             	break;
	            case 7:                          //根据元素的值查找元素下标 
	             	printf("\n\t请输入要查找元素的值：\n");
	             	int e_2;
	             	scanf("%d", &e_2);
					LocateElem(L, e_2, compare); 
	             	getchar();getchar();
	             	break;
	            case 8:                          //根据元素的值查找前驱 
	             	printf("\n\t请输入要查找的元素，将显示它前一个元素的值：\n");
	             	int cur, pre_e;
					scanf("%d", &cur);
					PriorElem(L, cur, pre_e);
	             	getchar();getchar();
	             	break;
	            case 9:                          //根据元素的值查找后继 
	             	printf("\n\t请输入要查找的元素，将显示它后一个元素的值：\n");
	             	int cur_2, next_e;
					scanf("%d", &cur_2);
					NextElem(L, cur_2, next_e);
	             	getchar();getchar();
	             	break;
	            case 10:                         //插入元素 
	             	printf("\n\t请输入要插入的位置和新元素的值：\n");
	             	int pos, val;
	             	scanf("%d %d", &pos, &val);
	             	ListInsert(L, pos, val);
	             	getchar();getchar();
	             	break;
	            case 11:                         //删除元素 
	             	printf("\n\t请输入要删除的元素位置：\n");
	             	int pos_2, e_3;
	             	scanf("%d", &pos_2);
	             	ListDelete(L, pos_2, e_3);
	             	getchar();getchar();
	             	break;
	            case 12:                         //线性表的遍历 
			        if(!ListTraverse(L))
			        	printf("线性表为空表");
	             	getchar();getchar();
	             	break;
	            case 13:                         //将一个线性表写入文件 
	            	WriteFile(L);
	            	break;
	            case 14:                         //从已有文件中读取线性表 
	            	ReadFile(L);
	            	break;
	            case 15:                         //切换至另一线性表进行操作 
	            	printf("请输入想要切换的线性表编号：\n");
	            	scanf("%d", &num_2);
	            	num = num_2;
	            	goto Begin;
					break;
	            case 0:                          //输入0终止程序 
	             	break;
	        }//end obreakf switch
    }//end of while
    printf("\t欢迎下次再使用本系统！\n");
}//end of main()

status compare(int x1, int x2){
	if(x1 == x2)
		return TRUE;
	else
		return FALSE;
}


status visit(LNode *a){
	while(a != NULL){
		a = a->next;
		printf("%d ", a->data);
	}
	return OK;
}


LNode* InitList(LNode *Ins, int num){              //初始化，函数序号为1
	LNode *pHead = (LNode*)malloc(sizeof(LNode));  //分配一个不存放有效数据的头结点
	pHead->next = NULL;
    Ins[num].next = pHead;
	return pHead;                              //返回头节点的指示指针 
}


status DestroyList(LNode *Ins, int num){       //销毁，函数序号为2 
	if(!Ins[num].next){                        //空表也可以销毁 
		return OK; 
	}
	Ins[num].data = 0;                         //初始化标记重置为0 
	LNode *p = Ins[num].next; 
	LNode *q = p->next;
	while(p){
		free(p);
		p = q;
		if(p){
			q = q->next;
		}
	}
	return OK;
}


status ClearList(LNode *L){    //清空，函数序号为3 
	if(L->next == NULL){
		printf("\t线性表已经为空，无需清空\n");
		return FALSE; 
	}
	
	LNode *p = L->next;
	LNode *q = p->next;
	while(p){
		free(p);
		p = q;
		if(p){
			q = q->next;
		}
	}
	L->next = NULL;
	printf("\t线性表已清空\n");
	return OK;
}


status ListEmpty(LNode *L){   //判断是否为空，函数序号为4 
	if(L->next == NULL){
		printf("\t线性表为空\n");
		return TRUE; 
	}
	
	else{
		printf("\t线性表不为空\n");
		return FALSE;
	}
}


int ListLength(LNode *L){      //求表长，函数序号为5 
	int length = 0;
	LNode *p = L->next;
	while(p){
		length ++;
		p = p->next;
	}
	printf("\t线性表的长度为%d\n", length);
	return length;
}


status GetElem(LNode *L, int i, ElemType &e){  //查找元素值，函数序号为6 
	LNode *p = L->next;
	int j = 1;
	if(i <= 0){
		printf("\t输入下标不合法\n");
		return ERROR;
	}
	
	while(p && j<i){
		p = p->next;
		j++;
	}
	
	if(!p){
		printf("\t输入下表不合法\n");
		return ERROR;
	}
	
	e = p->data;
	printf("\t第%d个元素为%d\n", i, e);
	return OK;
}


status LocateElem(LNode *L, ElemType e, int (*func) (int x1, int x2)){   //查找下标，函数序号为7 
	int j;
	LNode *p = L->next;
	for(j=0; p; j++){
		if(func(p->data, e)){
			printf("\t该元素的位置在第%d个",j+1);
			return j+1;
		}
		p = p->next;
	}
	
	printf("\t该元素不在线性表中");
	return FALSE;
}


status PriorElem(LNode *L, ElemType cur, ElemType &pre_e){   //查找前驱，函数序号为8 
	LNode *p1, *p2;
	p1 = L;
	p2 = p1->next;            //p2比p1快一步，正常情况用p2找到了就返回p1所在位置的数据 
	if(p2->data == cur){
		printf("\t该元素为首元素，不存在前驱\n");
		return ERROR; 
	}
	
	while(p2->data!=cur && p2){
		p1 = p2;
		p2 = p2->next; 
	}
	
	if(!p2){
		printf("\t该元素不在表中");
		return ERROR;
	}
	else{
		pre_e = p1->data;
		printf("\t元素%d的前驱为%d\n", cur, pre_e);
		return OK;
	}
}


status NextElem(LNode *L, ElemType cur, ElemType &next_e){   //查找后继，函数序号为9
	LNode *p1 = L;
	LNode *p2 = p1->next;          //p2比p1快一步，正常情况用p1找到了就返回p2所在位置的数据 
	while(p1->data!=cur && p2){
		p1 = p2;
		p2 = p2->next;
	}
	
	if(!p2 && p1->data!=cur){
		printf("\t该元素不在表中\n");
		return ERROR;
	}
	else if(!p2 && p1->data==cur){
		printf("\t该元素为尾元素，不存在后继\n");
		return ERROR;
	}
	else{
		next_e = p2->data;
		printf("\t元素%d的后继为%d\n", cur, next_e);
		return OK; 
	}
}


status ListInsert(LNode *L, int i, ElemType e){            //插入，函数序号为10 
	LNode *p0 = L;
	int j = 0;
	while(p0 && j<i-1){
		p0 = p0->next;
		j ++;
	}              //寻找第i-1个节点 
	
	if(!p0 || j>i-1){
		printf("\t输入下标不合法\n");
		return ERROR;
	}
	
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p0->next;
	p0->next = s;
	printf("\t插入成功\n");
	return OK;
}


status ListDelete(LNode *L, int i, ElemType &e){   //删除，函数序号为11 
	LNode *p = L;
	int j = 0;
	while(p->next && j<i-1){
		p = p->next;
		j++;
	}
	
	if(!(p->next) || j>i-1){
		printf("\t输入下标不合法\n");
		return ERROR;
	}
	
	LNode *q = p->next;
	p->next = q->next;
	e = q->data;
	printf("\t元素%d删除成功\n", e); 
	free(q);
	return OK;
}


status ListTraverse(LNode *L){  //函数序号为12
    if(!L->next){
    	return ERROR;
	}
	
	LNode *p = L->next;
	printf("\n---------------all elements ------------------\n");
    while(p){
		printf("%d ", p->data);
		p = p->next;
	}
    printf("\n------------------ end -----------------------\n");
    return OK;
}


status WriteFile(LNode *L){               //写入文件，函数序号为13 
	FILE *fp; 
	printf("请输入文件名：");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"wb"))==NULL)
	{
		printf("打开文件时出错\n ");
		return ERROR;
	}
	
	int length = ListLength(L);
	fwrite(L, sizeof(LNode), 1, fp);
	printf("已成功写入文件\n");
	fclose(fp);
	return OK;
}


status ReadFile(LNode *L){                //读取文件，函数序号为14 
	FILE *fp;
	printf("\t请输入想要读取的文件名：\n");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"rb"))==NULL)
		{
			printf("打开文件时错误\n ");
			system("pause");
			return ERROR;
		}
	while(fread(L, sizeof(LNode), 1, fp));
	printf("读取成功\n");
	fclose(fp);
	return OK; 
}


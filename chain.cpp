#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;          //����Ԫ�����Ͷ���
typedef struct node{           //�ڵ㶨��
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
status LocateElem(LNode *L, ElemType e, int (*func) (int, int));       //��Ҫ���ú���compare���в��ң�ʹ�ú���ָ�� 
status PriorElem(LNode *L, ElemType cur, ElemType &pre_e);
status NextElem(LNode *L, ElemType cur, ElemType &next_e);
status ListInsert(LNode *L, int i, ElemType e);
status ListDelete(LNode *L, int i, ElemType &e);
status ListTraverse(LNode *L);       //��Ҫ���ú���visit���з��ʣ�ʹ�ú���ָ��
status WriteFile(LNode *L);
status ReadFile(LNode *L);

int main(void){
	LNode Instructor[101];          //����ڵ����͵����飬�̶�����Ϊ100�������Բ���100����ÿһ��Ԫ�ض���ͷָ��
	for(int i=0; i<101; i++){       //�Ƚ�ÿһ���Ժ�Ҫָ���ͷ��ָ��ָ��NULL 
		Instructor[i].next = InitList(Instructor, i); 
		Instructor[i].data = 0;     //Ϊ0��ʾδ��ʼ����Ϊ1��ʾ�Ѿ���ʼ�� 
		
}
	
	int op = 1;
    int num, num_2;                 //numΪ��Ҫ���в����ı��ţ�num_2��Ϊ��ѡ15��ʱ�ٴ��������ʱ���� 
    printf("������Ҫ���������Ա��ţ�\n");
	scanf("%d", &num);
	
	Begin:                          //�Ӷ������л����� 
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
        printf("\t��ѡ����Ĳ���[0~15]:");
        scanf("%d", &op);
        while(!Instructor[num].data && op != 1){
        	printf("\n���Ա�δ������\n");
        	scanf("%d",&op);
		}
		
	        switch(op){
	            case 1:
	            	if(L)
						printf("\t%d�ű����ɹ�\n", num);
					Instructor[num].data = 1;
					getchar();getchar();
					break;
				case 2:
	             	DestroyList(Instructor, num);
					printf("\n\t���Ա�������\n");
	             	getchar();getchar();
	             	break;
	            case 3:
	             	ClearList(L);            //������� 
	                getchar();getchar();
	             	break;
	            case 4:
	             	ListEmpty(L);            //�жϱ��Ƿ�Ϊ�� 
	             	getchar();getchar();
	             	break;
	            case 5:
	             	ListLength(L);          //��� 
	              	getchar();getchar();
	             	break;
	            case 6:                          //����Ԫ���±����Ԫ�ص�ֵ 
	             	printf("\n\t���������Ԫ���±꣺\n");
	             	int i, e;
	             	scanf("%d", &i);
	             	GetElem(L, i, e);
	             	getchar();getchar();
	             	break;
	            case 7:                          //����Ԫ�ص�ֵ����Ԫ���±� 
	             	printf("\n\t������Ҫ����Ԫ�ص�ֵ��\n");
	             	int e_2;
	             	scanf("%d", &e_2);
					LocateElem(L, e_2, compare); 
	             	getchar();getchar();
	             	break;
	            case 8:                          //����Ԫ�ص�ֵ����ǰ�� 
	             	printf("\n\t������Ҫ���ҵ�Ԫ�أ�����ʾ��ǰһ��Ԫ�ص�ֵ��\n");
	             	int cur, pre_e;
					scanf("%d", &cur);
					PriorElem(L, cur, pre_e);
	             	getchar();getchar();
	             	break;
	            case 9:                          //����Ԫ�ص�ֵ���Һ�� 
	             	printf("\n\t������Ҫ���ҵ�Ԫ�أ�����ʾ����һ��Ԫ�ص�ֵ��\n");
	             	int cur_2, next_e;
					scanf("%d", &cur_2);
					NextElem(L, cur_2, next_e);
	             	getchar();getchar();
	             	break;
	            case 10:                         //����Ԫ�� 
	             	printf("\n\t������Ҫ�����λ�ú���Ԫ�ص�ֵ��\n");
	             	int pos, val;
	             	scanf("%d %d", &pos, &val);
	             	ListInsert(L, pos, val);
	             	getchar();getchar();
	             	break;
	            case 11:                         //ɾ��Ԫ�� 
	             	printf("\n\t������Ҫɾ����Ԫ��λ�ã�\n");
	             	int pos_2, e_3;
	             	scanf("%d", &pos_2);
	             	ListDelete(L, pos_2, e_3);
	             	getchar();getchar();
	             	break;
	            case 12:                         //���Ա�ı��� 
			        if(!ListTraverse(L))
			        	printf("���Ա�Ϊ�ձ�");
	             	getchar();getchar();
	             	break;
	            case 13:                         //��һ�����Ա�д���ļ� 
	            	WriteFile(L);
	            	break;
	            case 14:                         //�������ļ��ж�ȡ���Ա� 
	            	ReadFile(L);
	            	break;
	            case 15:                         //�л�����һ���Ա���в��� 
	            	printf("��������Ҫ�л������Ա��ţ�\n");
	            	scanf("%d", &num_2);
	            	num = num_2;
	            	goto Begin;
					break;
	            case 0:                          //����0��ֹ���� 
	             	break;
	        }//end obreakf switch
    }//end of while
    printf("\t��ӭ�´���ʹ�ñ�ϵͳ��\n");
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


LNode* InitList(LNode *Ins, int num){              //��ʼ�����������Ϊ1
	LNode *pHead = (LNode*)malloc(sizeof(LNode));  //����һ���������Ч���ݵ�ͷ���
	pHead->next = NULL;
    Ins[num].next = pHead;
	return pHead;                              //����ͷ�ڵ��ָʾָ�� 
}


status DestroyList(LNode *Ins, int num){       //���٣��������Ϊ2 
	if(!Ins[num].next){                        //�ձ�Ҳ�������� 
		return OK; 
	}
	Ins[num].data = 0;                         //��ʼ���������Ϊ0 
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


status ClearList(LNode *L){    //��գ��������Ϊ3 
	if(L->next == NULL){
		printf("\t���Ա��Ѿ�Ϊ�գ��������\n");
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
	printf("\t���Ա������\n");
	return OK;
}


status ListEmpty(LNode *L){   //�ж��Ƿ�Ϊ�գ��������Ϊ4 
	if(L->next == NULL){
		printf("\t���Ա�Ϊ��\n");
		return TRUE; 
	}
	
	else{
		printf("\t���Ա�Ϊ��\n");
		return FALSE;
	}
}


int ListLength(LNode *L){      //������������Ϊ5 
	int length = 0;
	LNode *p = L->next;
	while(p){
		length ++;
		p = p->next;
	}
	printf("\t���Ա�ĳ���Ϊ%d\n", length);
	return length;
}


status GetElem(LNode *L, int i, ElemType &e){  //����Ԫ��ֵ���������Ϊ6 
	LNode *p = L->next;
	int j = 1;
	if(i <= 0){
		printf("\t�����±겻�Ϸ�\n");
		return ERROR;
	}
	
	while(p && j<i){
		p = p->next;
		j++;
	}
	
	if(!p){
		printf("\t�����±��Ϸ�\n");
		return ERROR;
	}
	
	e = p->data;
	printf("\t��%d��Ԫ��Ϊ%d\n", i, e);
	return OK;
}


status LocateElem(LNode *L, ElemType e, int (*func) (int x1, int x2)){   //�����±꣬�������Ϊ7 
	int j;
	LNode *p = L->next;
	for(j=0; p; j++){
		if(func(p->data, e)){
			printf("\t��Ԫ�ص�λ���ڵ�%d��",j+1);
			return j+1;
		}
		p = p->next;
	}
	
	printf("\t��Ԫ�ز������Ա���");
	return FALSE;
}


status PriorElem(LNode *L, ElemType cur, ElemType &pre_e){   //����ǰ�����������Ϊ8 
	LNode *p1, *p2;
	p1 = L;
	p2 = p1->next;            //p2��p1��һ�������������p2�ҵ��˾ͷ���p1����λ�õ����� 
	if(p2->data == cur){
		printf("\t��Ԫ��Ϊ��Ԫ�أ�������ǰ��\n");
		return ERROR; 
	}
	
	while(p2->data!=cur && p2){
		p1 = p2;
		p2 = p2->next; 
	}
	
	if(!p2){
		printf("\t��Ԫ�ز��ڱ���");
		return ERROR;
	}
	else{
		pre_e = p1->data;
		printf("\tԪ��%d��ǰ��Ϊ%d\n", cur, pre_e);
		return OK;
	}
}


status NextElem(LNode *L, ElemType cur, ElemType &next_e){   //���Һ�̣��������Ϊ9
	LNode *p1 = L;
	LNode *p2 = p1->next;          //p2��p1��һ�������������p1�ҵ��˾ͷ���p2����λ�õ����� 
	while(p1->data!=cur && p2){
		p1 = p2;
		p2 = p2->next;
	}
	
	if(!p2 && p1->data!=cur){
		printf("\t��Ԫ�ز��ڱ���\n");
		return ERROR;
	}
	else if(!p2 && p1->data==cur){
		printf("\t��Ԫ��ΪβԪ�أ������ں��\n");
		return ERROR;
	}
	else{
		next_e = p2->data;
		printf("\tԪ��%d�ĺ��Ϊ%d\n", cur, next_e);
		return OK; 
	}
}


status ListInsert(LNode *L, int i, ElemType e){            //���룬�������Ϊ10 
	LNode *p0 = L;
	int j = 0;
	while(p0 && j<i-1){
		p0 = p0->next;
		j ++;
	}              //Ѱ�ҵ�i-1���ڵ� 
	
	if(!p0 || j>i-1){
		printf("\t�����±겻�Ϸ�\n");
		return ERROR;
	}
	
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p0->next;
	p0->next = s;
	printf("\t����ɹ�\n");
	return OK;
}


status ListDelete(LNode *L, int i, ElemType &e){   //ɾ�����������Ϊ11 
	LNode *p = L;
	int j = 0;
	while(p->next && j<i-1){
		p = p->next;
		j++;
	}
	
	if(!(p->next) || j>i-1){
		printf("\t�����±겻�Ϸ�\n");
		return ERROR;
	}
	
	LNode *q = p->next;
	p->next = q->next;
	e = q->data;
	printf("\tԪ��%dɾ���ɹ�\n", e); 
	free(q);
	return OK;
}


status ListTraverse(LNode *L){  //�������Ϊ12
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


status WriteFile(LNode *L){               //д���ļ����������Ϊ13 
	FILE *fp; 
	printf("�������ļ�����");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"wb"))==NULL)
	{
		printf("���ļ�ʱ����\n ");
		return ERROR;
	}
	
	int length = ListLength(L);
	fwrite(L, sizeof(LNode), 1, fp);
	printf("�ѳɹ�д���ļ�\n");
	fclose(fp);
	return OK;
}


status ReadFile(LNode *L){                //��ȡ�ļ����������Ϊ14 
	FILE *fp;
	printf("\t��������Ҫ��ȡ���ļ�����\n");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"rb"))==NULL)
		{
			printf("���ļ�ʱ����\n ");
			system("pause");
			return ERROR;
		}
	while(fread(L, sizeof(LNode), 1, fp));
	printf("��ȡ�ɹ�\n");
	fclose(fp);
	return OK; 
}


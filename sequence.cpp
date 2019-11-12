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
typedef int ElemType;          //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{                //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
	int is_init;               //�ڶ��������õ���ֵΪ1��ʾ�ñ��Ѿ���ʼ����ֵΪ0��ʾ��δ��ʼ�� 
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
status LocateElem(SqList L, ElemType e, int (*func) (int, int));       //��Ҫ���ú���compare���в��ң�ʹ�ú���ָ�� 
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);
status NextElem(SqList L, ElemType cur, ElemType &next_e);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L, void (*func_2) (ElemType *, int));       //��Ҫ���ú���visit���з��ʣ�ʹ�ú���ָ��
status WriteFile(SqList L);
status ReadFile(SqList &L);
/*--------------------------------------------*/
int main(void){
	SqList L[100];                  //�������Ա����͵Ľṹ���飬�̶�����Ϊ100�������Բ���100����
	for(int i=0; i<100; i++){       //��ÿһ��Ԫ�ص�is_init��ʼ��Ϊ0
		L[i].is_init = 0;
	} 
	
	int op = 1, count = 0;  //count��ʾ�ڼ��β�������ʼΪ0ʱ������һ�����룩����Ϊ1�������޷��������Ա�
    int num, num_2;         //numΪ��Ҫ���в����ı��ţ�num_2��Ϊ�˱��ں����ٴ��������ʱ���� 
    printf("������Ҫ���������Ա��ţ�\n");
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
        printf("\t��ѡ����Ĳ���[0~15]:");
        scanf("%d", &op);
        while(L[num].is_init == 0 && op != 1){
        	printf("\n���Ա�δ������\n");
        	scanf("%d",&op);
		}

        switch(op){
            case 1:
            	InitList(L[num]);
            	L[num].is_init = 1;           //��Ϊ�����Ա��Ѿ���ʼ���ı�� 
             	getchar();getchar();
             	break;
            case 2:
             	DestroyList(L[num]);
				printf("\n\t���Ա�������\n");
				count = 0;                    //�˺���Ҫ���´������Ա�����count��Ϊ0�����������1������Ϊ�Ƿ�ֵ 
             	getchar();getchar();
             	break;
            case 3:
             	ClearList(L[num]);            //������� 
                getchar();getchar();
             	break;
            case 4:
             	ListEmpty(L[num]);            //�жϱ��Ƿ�Ϊ�� 
             	getchar();getchar();
             	break;
            case 5:
             	ListLength(L[num]);          //��� 
              	getchar();getchar();
             	break;
            case 6:                          //����Ԫ���±����Ԫ�ص�ֵ 
             	printf("\n\t���������Ԫ���±꣺\n");
             	int i, e;
             	scanf("%d", &i);
             	GetElem(L[num], i, e);
             	getchar();getchar();
             	break;
            case 7:                          //����Ԫ�ص�ֵ����Ԫ���±� 
             	printf("\n\t������Ҫ����Ԫ�ص�ֵ��\n");
             	int e_2;
             	scanf("%d", &e_2);
				LocateElem(L[num], e_2, compare); 
             	getchar();getchar();
             	break;
            case 8:                          //����Ԫ�ص�ֵ����ǰ�� 
             	printf("\n\t������Ҫ���ҵ�Ԫ�أ�����ʾ��ǰһ��Ԫ�ص�ֵ��\n");
             	int cur, pre_e;
				scanf("%d", &cur);
				PriorElem(L[num], cur, pre_e);
             	getchar();getchar();
             	break;
            case 9:                          //����Ԫ�ص�ֵ���Һ�� 
             	printf("\n\t������Ҫ���ҵ�Ԫ�أ�����ʾ����һ��Ԫ�ص�ֵ��\n");
             	int cur_2, next_e;
				scanf("%d", &cur_2);
				NextElem(L[num], cur_2, next_e);
             	getchar();getchar();
             	break;
            case 10:                         //����Ԫ�� 
             	printf("\n\t������Ҫ�����λ�ú���Ԫ�ص�ֵ��\n");
             	int pos, val;
             	scanf("%d %d", &pos, &val);
             	ListInsert(L[num], pos, val);
             	getchar();getchar();
             	break;
            case 11:                         //ɾ��Ԫ�� 
             	printf("\n\t������Ҫɾ����Ԫ��λ�ã�\n");
             	int pos_2, e_3;
             	scanf("%d", &pos_2);
             	ListDelete(L[num], pos_2, e_3);
             	getchar();getchar();
             	break;
            case 12:                         //���Ա�ı��� 
		        if(!ListTraverse(L[num], visit))
		        	printf("���Ա�Ϊ�ձ�");
             	getchar();getchar();
             	break;
            case 13:                         //��һ�����Ա�д���ļ� 
            	WriteFile(L[num]);
            	break;
            case 14:                         //�������ļ��ж�ȡ���Ա� 
            	ReadFile(L[num]);
            	break;
            case 15:                         //�л�����һ���Ա���в��� 
            	printf("\t��������Ҫ�л������Ա��ţ�\n");
            	scanf("%d", &num_2);
            	num = num_2;
				break;
            case 0:                          //����0��ֹ���� 
             	break;
        }//end of switch
      }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
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
status InitList(SqList &L){    //��ʼ�����������Ϊ1 
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem){
    	printf("\t����ռ�ʧ�ܣ����Ա��ʼ��ʧ��");
    	exit(OVERFLOW);
	}
	
	L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    printf("\t���Ա����ɹ�");
	return OK;
}


status DestroyList(SqList &L){  //���٣��������Ϊ2 
	L.is_init = 0;
	free(L.elem);
	return OK;
}


status ClearList(SqList &L){    //��գ��������Ϊ3 
	if(L.length == 0){
		printf("\t���Ա��Ѿ�Ϊ�գ��������");
		return FALSE; 
	}
	
	int i;
	for(i=0; i<L.length; i++){
		L.elem[i] = 0;
	}
	L.length = 0;
	printf("\t���Ա������");
	return OK;
}


status ListEmpty(SqList L){   //�ж��Ƿ�Ϊ�գ��������Ϊ4 
	if(L.length == 0){
		printf("\t���Ա�Ϊ��");
		return TRUE; 
	}
	
	else{
		printf("\t���Ա�Ϊ��");
		return FALSE;
	}
}


int ListLength(SqList L){      //������������Ϊ5 
	printf("\t���Ա�ĳ���Ϊ%d", L.length);
	return L.length;
}


status GetElem(SqList L,int i,ElemType &e){  //����Ԫ��ֵ���������Ϊ6 
	if(i<1 || i>L.length){
		printf("\t�����±겻�Ϸ�");
		return ERROR;
	}
		
	e = L.elem[i-1];
	printf("\t��%d��Ԫ��Ϊ%d", i, e);
	return OK;
}


status LocateElem(SqList L, ElemType e, int (*func) (int x1, int x2)){   //�����±꣬�������Ϊ7 
	int j;
	for(j=0; j<L.length; j++){
		if(func(L.elem[j], e)){
			printf("\t��Ԫ�ص�λ���ڵ�%d��",j+1);
			return j+1;
		}
	}
	
	if(j == L.length){
		printf("\t��Ԫ�ز������Ա���");
		return FALSE;
	}
}


status PriorElem(SqList L, ElemType cur, ElemType &pre_e){   //����ǰ�����������Ϊ8 
	int i;
	for(i=0; i<L.length; i++){
		if(L.elem[i] == cur)
			break;
	}
	
	if(i == 0){
		printf("��Ԫ��Ϊ��Ԫ�أ������ں��");
		return ERROR;
	}
	else if(i > L.length - 1){
		printf("��Ԫ�ز��ڱ���");
		return ERROR;
	}
	
	pre_e = L.elem[i-1];
	printf("\tԪ��%d֮ǰ��Ԫ��Ϊ%d", cur, pre_e);
	return OK;
}


status NextElem(SqList L,ElemType cur,ElemType &next_e){   //���Һ�̣��������Ϊ9 
	int i;
	for(i=0; i<L.length; i++){
		if(L.elem[i] == cur)
			break;
	}
	
	if(i == L.length - 1){
		printf("��Ԫ��ΪβԪ�أ������ں��");
		return ERROR;
	}
	else if(i > L.length - 1){
		printf("��Ԫ�ز��ڱ���");
		return ERROR;
	}
	
	next_e = L.elem[i+1];
	printf("\tԪ��%d֮���Ԫ��Ϊ%d", cur, next_e);
	return OK;
}


status ListInsert(SqList &L,int i,ElemType e){            //���룬�������Ϊ10 
	if(i<1 || i>L.length+1){
		printf("\t�����±겻�Ϸ�");
		return ERROR;
	}
		
	if(L.length >= L.listsize){                           //��Ҫ�ж����Ա��Ƿ���������ǣ���Ҫ�����һЩ�ռ� 
		ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase){
			printf("\t���������ʧ��");
			exit(OVERFLOW);
		}
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	
	ElemType *q = &(L.elem[i-1]);
	ElemType *p = &(L.elem[L.length-1]);
	for(; p>=q; p--)                                      //��������һ��Ԫ�ؿ�ʼ���� 
		*(p+1) = *p;                                      //�ڲ���λ��֮���ÿһ��Ԫ������ƶ�
	*q = e;
	L.length ++;
	printf("\t����ɹ�"); 
	return OK;
}


status ListDelete(SqList &L, int i, ElemType &e){   //ɾ�����������Ϊ11 
	if(i<1 || i>L.length){
		printf("\t�����±겻�Ϸ�");
		return ERROR;
	}
	
	ElemType *p = &(L.elem[i-1]);
	e = *p;
	ElemType *q = L.elem + L.length - 1;
	q = L.elem + L.length - 1;
	for(++p; p<=q; ++p)                             //����ɾ��Ԫ�صĺ�̿�ʼ���� 
		*(p-1) = *p;                                //��ɾ��λ��֮���ÿһ��Ԫ����ǰ�ƶ� 
	L.length --;
	printf("\tɾ���ɹ�"); 
	return OK;
}


status ListTraverse(SqList L, void (*func_2) (int *a, int len)){  //�������Ϊ12 
    int i;
    printf("\n---------------all elements ------------------\n");
    func_2(L.elem, L.length);
    printf("\n------------------ end -----------------------\n");
    return L.length;
}


status WriteFile(SqList L){               //д���ļ����������Ϊ13 
	FILE *fp; 
	printf("�������ļ�����");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"wb"))==NULL)
	{
		printf("���ļ�ʱ����\n ");
		return ERROR;
	}
	fwrite(L.elem, sizeof(ElemType), L.length, fp);
	printf("�ѳɹ�д���ļ�\n");
	fclose(fp);
	return OK;
}


status ReadFile(SqList &L){                //��ȡ�ļ����������Ϊ14 
	FILE *fp;
	L.length = 0;
	printf("��������Ҫ��ȡ���ļ�����\n");
	char filename[100];
	scanf("%s", filename);
	if ((fp = fopen(filename,"rb"))==NULL)
		{
			printf("���ļ�ʱ����\n ");
			system("pause");
			return ERROR;
		}
	while(fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
	L.length ++;
	printf("��ȡ�ɹ�\n");
	fclose(fp);
	return OK; 
}


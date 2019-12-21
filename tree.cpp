#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int status;
typedef char TElemType;

typedef struct BiTNode{  //���Ľڵ�ṹ 
	TElemType data;
	int key;
	int is_create;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct{      //ջ�Ľṹ 
	BiTree *base;
	BiTree *top;
}SqStack;      

BiTNode *Ttemp = NULL;
BiTNode *T1 = NULL;
BiTNode *T2 = NULL;
FILE *fp;
char filename[100]; 

status visit(TElemType e);
status CreateBiTree(BiTree *T, int definition);     //�ڶ�������Ϊ����ѡ��1-3,����3�ֲ�ͬ�Ĵ�����ʽ 
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree T);
status BiTreeEmpty(BiTree T);
status BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, int e);
status Assign(BiTree T, int e, TElemType value);      //eΪ�ؼ��� 
BiTNode* GetSibling(BiTree t, int e);
status InsertNode(BiTree T, int e, int LR, BiTree c);
status DeleteNode(BiTree T, int e);
BiTNode* Parent(BiTree, int e);
status PreOrderTraverse(BiTree T, status (*visit)(TElemType e));
status InOrderTraverse(BiTree T, status (*visit)(TElemType e));
status PostOrderTraverse(BiTree T, status (*visit)(TElemType e));
status LevelOrderTraverse(BiTree T, status (*visit)(TElemType e));
void level(BiTree T, int i);       //��������ĸ������� 
status Save(BiTree T,FILE *fp);
status Load(BiTree *T,FILE *fp);

int main(){
	int i, op, num, def;
	BiTNode TList[11];
	for(i=0; i<11; i++){
		TList[i].lchild = NULL;
		TList[i].rchild = NULL;
		TList[i].is_create = 0;              //0��ʾδ���������˺�����keyֵ����Ϊ0 
		TList[i].data = '#';                 //data���ʼ��Ϊ# 
	}
	
	printf("\t��������Ҫ����������ţ�");
	scanf("%d", &num);
	BiTree T = &TList[num];
	
	while(op){
        system("cls");
		printf("\n\n");
        printf("                 Menu for Binary Trees\n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateBiTree        7. Assign\n");
        printf("    	  2. DestroyBiTree       8. GetSibling\n");
        printf("    	  3. ClearBiTree         9. InsertNode\n");
        printf("    	  4. BiTreeEmpty        10. DeleteNode\n");
        printf("    	  5. BiTreeDepth        11. PreOrderTraverse\n");
        printf("    	  6. LocateNode         12. InOrderTraverse\n");
        printf("         13. PostOrderTraverse  14. LevelOrderTraverse\n");
        printf("         15. Load               16. Save\n");
        printf("         17. Change\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("\t��ѡ����Ĳ���[0~14]:");
        scanf("%d", &op);
        while(!TList[num].is_create && op != 1){
        	printf("\n��δ������\n");
        	scanf("%d",&op);
		} 
		
        switch(op){
            case 1:                          //������ 
            	printf("\t������definition��ֵ\n");
				printf("\t1������ ���������Ķ�����ǰ��������� ����������\n");
				printf("\t2������ ǰ��+���� ����������\n");
				printf("\t3������ ����+���� ����������\n");
				scanf("%d", &def);
				getchar();   //��ȡ��������Ļس�   
				CreateBiTree(&T, def);
					printf("\t%d���������ɹ�\n", num);
				TList[num].is_create = 1;
				getchar(); 
				break;
			case 2:                          //������ 
				 DestroyBiTree(&T);
				 T->is_create = 0;
				 printf("\t������������\n");
				 getchar(); getchar();
				 break;
			case 3:                          //����� 
				ClearBiTree(T);
				getchar(); getchar();
				break;
			case 4:                          //�п� 
				if(BiTreeEmpty(T))
					printf("\t������Ϊ��\n");
				else
					printf("\t��������Ϊ��\n");
				getchar(); getchar();
				break;
			case 5:                          //����� 
				if(BiTreeEmpty(T))
					printf("\t�������Ϊ0\n");
				else
					printf("\t�������Ϊ%d\n" ,BiTreeDepth(T));
				getchar(); getchar();
				break;
			case 6:                          //��λ 
				int e;
				printf("\t��������Ҫ���ҵ�Ԫ��keyֵ��");
				scanf("%d", &e);
				Ttemp = LocateNode(T, e);
				if(Ttemp == NULL)
					printf("\t����Ԫ�ز��ڸö�������\n");
				else
					printf("\t�����ҵ�Ԫ��dataΪ%c\n", Ttemp->data);
				getchar(); getchar();
				break;
			case 7:                          //���Ҹ�ֵ���滻�� 
				if (!T){
			   		printf("\t�����������ڣ�\n");
			   		getchar(); getchar();
			   		break;
				}
			    int k; char ch;
				printf("\t��������Ҫ���ҵ�key:");
				scanf("%d", &k);
				getchar();
				printf("\t��������Ҫ���¸�ֵ��data:");
				scanf("%c", &ch);
				if (Assign(T, k, ch) != ERROR)
					printf("\t��key��Ӧ��data��Ϊ�ˣ�%c\n", ch);
				else
					printf("\t�����key�����ֲ����ڣ�\n");
				getchar(); getchar();
				break; 
			case 8:                          //��ȡ�ֵܽڵ� 
				int e2;
				printf("\t������������ҵĽڵ�keyֵ����չʾ���ֵܽڵ㣺\n");
				scanf("%d", &e2);
				GetSibling(T, e2);
				getchar(); getchar();
				break;
			case 9:
				int LR, e3;
				if (T == NULL){
			   		printf("\t�����������ڣ�\n");
			   		getchar();getchar();
			   		break;
				}
				printf("\t��������Ҫ����λ�õ�key: ");
				scanf("%d", &e3);
				getchar();
				LocateNode(T, e3);
				printf("\t����������Ҫ����ķ���,0��ʾ���,1��ʾ�ұ�: ");
				scanf("%d", &LR);
				getchar();
				CreateBiTree(&T1, 1);
				if (InsertNode(T, e3, LR, T1) == OK){
				    printf("\t����ɹ�!\n");
					getchar(); getchar();
				}
				else
				{
				    printf("\t����ʧ��!\n");
					getchar(); getchar();
				}
				break;
			case 10:
				int e4;
				printf("\t��������Ҫɾ���Ľڵ��keyֵ��");
				scanf("%d", &e4);
				DeleteNode(T, e4);
				getchar(); getchar();
				break;
			case 11:                         //������� 
				PreOrderTraverse(T, visit);
				getchar(); getchar();
				break; 
			case 12:                         //������� 
				InOrderTraverse(T, visit);
				getchar(); getchar();
				break; 
			case 13:                         //������� 
				PostOrderTraverse(T, visit);
				getchar(); getchar();
				break;
			case 14:                         //������� 
				LevelOrderTraverse(T, visit);
				getchar(); getchar();
				break;
			case 15:
				printf("\t������Ҫ���ص��ļ���: ");
		       	scanf("%s",filename);
		       	if((fp=fopen(filename,"r"))==NULL)
				   printf("\t����ʧ�ܣ�\n");
		       	else{
		       		if(Load(&T,fp)==OK)
						printf("\t���سɹ���\n");
		       		else printf("\t����ʧ�ܣ�\n");
				}
				fclose(fp);
				getchar();getchar();
				break;
			case 16:
				printf("\t������Ҫ������ļ���: ");
				scanf("%s", filename);
			    if((fp=fopen(filename,"w"))==NULL) printf("\t\t\t���ļ�ʧ�ܣ�\n");
		       	else{
		       		if(Save(T,fp) == OK)
					   printf("\t\t\t�����ļ��ɹ���\n");
		       		else printf("\t\t\t�����ļ�ʧ�ܣ�\n");
				}
				fclose(fp);
				getchar();getchar();
				break;
			case 17:
				int num_2;
				printf("\t��������Ҫ�л������ı�ţ�");
				scanf("%d", &num_2);
				T = &TList[num_2];
				getchar();
				break;
            case 0:                          //����0��ֹ���� 
             	break;
        }//end obreakf switch
    }//end of while
    printf("\t��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


status visit(TElemType e){               //���ʺ�����ֻ���ӡ���� 
	printf("%c ", e);
	return OK;
}


status InitStack(SqStack &S){            //��ʼ��ջ 
	S.base = (BiTree*)malloc(50 * sizeof(BiTree));
	if(!S.base)
		exit(OVERFLOW);        //�洢����ʧ�� 
	S.top = S.base;
	return OK;
} 


status Push(SqStack &S, BiTree e){     //��ջ 
	//����Ԫ��eΪ�µ�ջ��Ԫ�� 
	*S.top = e;
	S.top ++;
	return OK;
}


status Pop(SqStack &S, BiTree &e){     //��ջ 
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ�� ������OK�����򷵻�ERROR
	if(S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK; 
}


status StackEmpty(SqStack S){         //�ж�ջ�Ƿ�Ϊ�� 
	if(S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//������������������� 
void xzBuild(BiTree *T, int preL, int preR, int inL, int inR, char pre[], char in[], int pre_num[], int in_num[]){
	if(preL > preR)
		return;
	char e = pre[preL];	int e_num = pre_num[preL];  //�ҵ��� 
	int root = inL;          //�����������е���ʼ�±�Ϊ�������߽磬�����ƶ����������ĸ������������е��±� 
	while(in[root]!=e && root<=inR)
		root ++;
	(*T) = (BiTree)malloc(sizeof(BiTNode));
	(*T) -> lchild = NULL;
	(*T) -> rchild = NULL;
	(*T) -> data = e;
	(*T) -> key = e_num;
	xzBuild(&(*T)->lchild, preL+1, preL+root-inL, inL, root-1, pre, in, pre_num, in_num);  //�����߽��±� 
	xzBuild(&(*T)->rchild, preL+root-inL+1, preR, root+1, inR, pre, in, pre_num, in_num);  //�����߽��±� 
}

//�ú���������������� 
void hzBuild(BiTree *T, int postL, int postR, int inL, int inR, char post[], char in2[], int post_num[], int in2_num[]){
	if(postL > postR)
		return;
	char e = post[postR];	int e_num = post_num[postR];  //�ҵ���
	int root = inL;          //�����������е���ʼ�±�Ϊ�������߽磬�����ƶ����������ĸ����±�
	while(in2[root]!=e && root<=inR)
		root ++;
	(*T) = (BiTree)malloc(sizeof(BiTNode));
	(*T) -> lchild = NULL;
	(*T) -> rchild = NULL;
	(*T) -> data = e;
	(*T) -> key = e_num;
	hzBuild(&(*T)->lchild, postL, postR-root+inL-1, inL, root-1, post, in2, post_num, in2_num); //��xzBuild����ѧ���ǶԳƵ� 
	hzBuild(&(*T)->rchild, postR-root+inL, postR-1, root+1, inR, post, in2, post_num, in2_num); //ͬ���Գ� 
}


status CreateBiTree(BiTree *T, int definition){     //�ڶ�������Ϊ����ѡ��1-3,����3�ֲ�ͬ�Ĵ�����ʽ 
	if(definition == 1){
		char ch;
		printf("\t����data(#��ʾ��):");
		scanf("%c", &ch);
		getchar();         //��ȡ�س� 
		if(ch == '#'){
			*T = NULL;
			return ERROR;
		}
		else{
			(*T) = (BiTree)malloc(sizeof(BiTNode));
			(*T)->data = ch;
			printf("\t����key:");
			scanf("%d", &(*T)->key);
			getchar();     //��ȡ�س�
			CreateBiTree(&((*T)->lchild), 1);
			CreateBiTree(&((*T)->rchild), 1);
		}
	} //end of if
	
	else if(definition == 2){
		char pre[50], in[50];
		int pre_num[50], in_num[50];
		int i;
		printf("\t������ǰ�����У��س�������\n");
		for(i=0; ; i++){
			printf("\t����data:");
			scanf("%c", &pre[i]);
			getchar();     //��ȡ�س� 
			if(pre[i] == '\n'){
				break;
			}
			printf("\t����key:");
			scanf("%d", &pre_num[i]);
			getchar();    //��ȡ�س� 
		}
		
		printf("\t�������������У��س�������\n");
		for(i=0; ; i++){
			printf("\t������data:");
			scanf("%c", &in[i]);
			if(in[i] == '\n'){
				break;
			}
			getchar();    //��ȡ�س� 
			printf("\t������key:");
			scanf("%d", &in_num[i]);
			getchar();    //��ȡ�س� 
		}
		
		int Len = i - 1;
		xzBuild(T, 0, Len, 0, Len, pre, in, pre_num, in_num);
		return OK;
	} //end of else if
	
	else{
		char post[50], in2[50];
		int post_num[50], in2_num[50];
		int i;
		printf("\t������������У��س�������\n");
		for(i=0; ; i++){
			printf("\t����data:");
			scanf("%c", &post[i]);
			if(post[i] == '\n'){
				break;
			}
			getchar();     //��ȡ�س� 
			printf("\t����key:");
			scanf("%d", &post_num[i]);
			getchar();     //��ȡ�س� 
		}
		
		printf("\t�������������У��س�������\n");
		for(i=0; ; i++){
			printf("\t������data:");
			scanf("%c", &in2[i]);
			getchar();    //��ȡ�س� 
			if(in2[i] == '\n'){
				break;
			}
			printf("\t������key:");
			scanf("%d", &in2_num[i]);
			getchar();    //��ȡ�س� 

		}
		
		int Len = i - 1;
		hzBuild(T, 0, Len, 0, Len, post, in2, post_num, in2_num);
		return OK;
	} //end of else
} //end of CreatBiTree


status DestroyBiTree(BiTree *T){   //���� 
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	return OK;
}


status ClearBiTree(BiTree T){  //��� 
	if(T){
		T->lchild = NULL;
		T->rchild = NULL;
		T->data = '#';         //��������ָ��ָ���,data������Ϊ#
		printf("\t�����������\n");
		return OK;
	}
	else{
		printf("\t����������գ��������\n");
		return ERROR;
	}
}


status BiTreeEmpty(BiTree T){      //�ж��Ƿ�Ϊ�� 
	if(T->data == '#')
		return TRUE;
	else
		return FALSE;
}


BiTNode* LocateNode(BiTree T, int e){       //��λ 
	if(!T) return NULL;   //��������Ϊ��,����ERROR 
	BiTNode *st[10], *p;
	int top = 0;  //�ÿ�ջ 
	st[top++] = T;
	while(top){
		p = st[--top]; //�������,����ջ��Ԫ��,�ж��Ƿ���key��ֵ��e���
		if(p->key == e){
            return p;
        }

		else{
			if(p->rchild!=NULL)
				st[top++] = p->rchild;
			if(p->lchild!=NULL)
				st[top++] = p->lchild;
		}
	}
	return NULL;
} 


status BiTreeDepth(BiTree T){      //��������� 
	int depth = 0;
	if(T){
		int lchilddepth = BiTreeDepth(T->lchild);
		int rchilddepth = BiTreeDepth(T->rchild);
		depth = (lchilddepth>=rchilddepth?(lchilddepth+1):(rchilddepth+1));
	}                             //ʹ�õݹ�,�õ��������������,���Ƚϴ�С,֮�󷵻��������
	return depth;
}


status Assign(BiTree T, int e, TElemType value){      //��ֵ��eΪ�ؼ��� 
	if (!T) 
		return ERROR;
    BiTNode *st[10], *p;
	int top = 0;
	st[top++] = T;
	while (top){
		p = st[--top];
		if (p->key == e){
			p->data = value;      //�ҵ�����и���
			return OK;
		}
		else{
			if (p->rchild != NULL)
				st[top++] = p->rchild;
			if (p->lchild != NULL)
				st[top++] = p->lchild;
		}
	}
	
	return ERROR;
}


BiTNode* LeftSibling(BiTree T, int e){
	BiTree p = NULL;
	if (T)
	{
		if (T->rchild!=NULL&&T->rchild->key == e)//����Һ��Ӳ�Ϊ�ղ��ҽڵ��ֵ����,��ô�㷵�����ӵ�ָ��
			return T->lchild;
		p = LeftSibling(T->lchild, e);
		if (p != NULL) 
			return p;
		p = LeftSibling(T->rchild, e);
		if (p != NULL) 
			return p;
	}
	return NULL;
}


BiTNode* RightSibling(BiTree T, int e){
	BiTree p=NULL;
	if (T){
		if (T->lchild!=NULL&&T->lchild->key == e)//����һ����������,������εݹ����������������
			return T->rchild;
		p = RightSibling(T->lchild, e);
		if (p != NULL) 
			return p;
		p = RightSibling(T->rchild, e);
		if (p != NULL) 
			return p;
	}
	return NULL;
}


BiTNode* GetSibling(BiTree T, int e){
	if(LeftSibling(T, e) != NULL){
		printf("\t���ҽڵ�����ֵܽڵ�key:%d��data:%c\n", LeftSibling(T, e)->key, LeftSibling(T, e)->data);
		return LeftSibling(T, e);
	}
	else{
		printf("\t���ҽڵ㲻�������ֵܽڵ�\n");
	}
	
	if(RightSibling(T, e)!=NULL){
		printf("\t���ҽڵ�����ֵܽڵ�key:%d��data:%c", RightSibling(T, e)->key, RightSibling(T, e)->data);
		return RightSibling(T, e);
	}
	else{
		printf("\t���ҽڵ㲻�������ֵܽڵ�\n");
		return NULL;
	}
}


status InsertNode(BiTree T, int e, int LR, BiTree c){
	BiTree p = LocateNode(T, e);
	if (!T){
		printf("\t\t\t�����������ڣ�");
		return ERROR;
	}
	if (c->rchild != NULL){
		printf("\t\t\t���������������������Ϊ�գ�");
		return ERROR;
	}
	if (LR == 0){
		c->rchild = p->lchild; //���뷽��Ϊ������
		p->lchild = c;
	}
	else{
		c->rchild = p->rchild;  //���뷽��Ϊ�ҵ����
		p->rchild = c;
    }
	return OK;
}


status DeleteNode(BiTree T, int e){    //ɾ���ڵ� 
    BiTree p = Parent(T, e);  //�ҵ���ǰ����˫��
    BiTree q = LocateNode(T, e);  //�ҵ���ǰ���
    if (q == NULL)
        return ERROR;
    else if(p == NULL){   //ɾ�������ͷ�ڵ�
        if(q->lchild == NULL)
            T = T->rchild;
        if(q->rchild == NULL)
            T = T->rchild;
        if(q->lchild!=NULL && q->rchild!=NULL){   //�����������ǿ� 
            BiTree c = T->rchild;
            q = q->lchild;
            while(q->rchild != NULL)
                q = q->rchild;
            q->rchild = c;
            T = T->lchild;
        }
    }
    else if(q->rchild==NULL && q->lchild==NULL){    //ɾ�����Ķ�Ϊ0
        if(p->lchild == q){   //ɾ�������˫�׽�������
            free(q);
            p->lchild==NULL;
        }
        else{   //�Һ���
        
            free(q);
            p->rchild==NULL;
        }
    }
    
	else if(q->lchild!=NULL && q->rchild==NULL){   //ɾ������Ϊ1,������Ϊ�� 
        if(p->lchild == q){
            p->lchild = q->rchild;
            free(q);
        }
        else{
            p->rchild = q->rchild;
            free(q);
        }
    }
    
	else if(q->lchild==NULL && q->rchild!=NULL){   //ɾ������Ϊ1��������Ϊ�� 
        if(p->lchild==q){
            p->lchild=q->lchild;
            free(q);
        }
        else{
            p->rchild=q->lchild;
            free(q);
        }
    }
    
    else{
        if(p->lchild == q){
            	BiTree c = q->lchild;//Ѱ��ɾ��������������
                p->lchild = q->lchild;
                while(c->rchild != NULL)
                    c = c->rchild;
                c->rchild = q->rchild;
            }
        else
            {
                BiTree c = q->lchild;//Ѱ��ɾ��������������
                p->rchild = q->lchild;
                while(c->rchild != NULL)
                {
                    c = c->rchild;
                }
                c->rchild = q->rchild;
            }
    }
    return OK;
}

BiTNode* Parent(BiTree T, int e){         //ɾ�������ĸ����������󸸽ڵ� 
	BiTree T1;                   //���ñ����͵ݹ�����Ѱ�������Һ��Ӷ�Ӧ��eֵ,���������㷵��ָ��
	if (T){
		if ((T->lchild!=NULL && T->lchild->key == e) ||(T->rchild!=NULL && T->rchild->key == e)) 
			return T;
		T1 = Parent(T->lchild, e);
		if (T1 != NULL) 
			return T1;
		T1 = Parent(T->rchild, e);
		if (T1 != NULL) 
			return T1;
	}
	return NULL;
}


status PreOrderTraverse(BiTree T, status (*visit)(TElemType e)){   //�ݹ�ʵ��������� 
	if(T){
		if(visit(T->data))
			if(PreOrderTraverse(T->lchild, visit))
				if(PreOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	}
	
	else
		return OK;
}


status InOrderTraverse(BiTree T, status (*visit)(TElemType e)){     //�ǵݹ飨ʹ��ջ��ʵ��������� 
	SqStack S;
	InitStack(S);
	BiTree p = T;
	while(p || !StackEmpty(S)){
		if(p){
			Push(S, p);
			p = p->lchild;
		}
		else{
			Pop(S, p);
			if(!visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	
	return OK;
}


status PostOrderTraverse(BiTree T, status (*visit)(TElemType e)){    //�ݹ�ʵ�ֺ������ 
	if(T){
		if(PostOrderTraverse(T->lchild, visit))
			if(PostOrderTraverse(T->rchild, visit))
				if(visit(T->data))//������������õݹ鷽ʽ
					return OK;
		return ERROR;
	}
	else return OK;
} 


void level(BiTree T, int i){     //�ú������������������
	if(T){
		if(i == 1)
			visit(T->data);
		else{
			level(T->lchild, i-1);
			level(T->rchild, i-1);
		}
	}
}

status LevelOrderTraverse(BiTree T, status (*visit)(TElemType e)){  //�����ʣ��ǵݹ�ʵ�ֲ������ 
	if(T){
		int h = BiTreeDepth(T);  //���ú����õ����
		int i;
		for(i=1; i<=h; i++){
			level(T, i);         //��ÿһ����з���
		} 
	}
	else
		return OK;
}


status Save(BiTree T,FILE *fp){
	int i = 0;
	char ch = '#';
	if(T){
        fprintf(fp,"%d%c",T->key,T->data);//��key��data����д���ļ�
        if(Save(T->lchild,fp))
        if(Save(T->rchild,fp)) return OK;
        else return ERROR;
	}
	else{
		fprintf(fp,"%d%c",i,ch);          //i��ch��ʼ����,��ζ�ſսڵ��keyΪ0,#����սڵ�.
		return OK;
	}
}


status Load(BiTree *T,FILE *fp){
	int i;      //��i����ʾkey
	char ch;    //��ch����ȡdata��
	if(feof(fp)){
		(*T) = NULL;
		return OK;
	}
	fscanf(fp,"%d",&i);
	fscanf(fp,"%c",&ch);
	if(ch == '#')
		(*T) = NULL;
	else{
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		(*T)->key = i;
		(*T)->data = ch;
		Load(&((*T)->lchild),fp);
		Load(&((*T)->rchild),fp);
	}    //�൱�����ζ�ȡ֮�󴴽�Ϊ������
	return OK;
}


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

typedef struct BiTNode{  //树的节点结构 
	TElemType data;
	int key;
	int is_create;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef struct{      //栈的结构 
	BiTree *base;
	BiTree *top;
}SqStack;      

BiTNode *Ttemp = NULL;
BiTNode *T1 = NULL;
BiTNode *T2 = NULL;
FILE *fp;
char filename[100]; 

status visit(TElemType e);
status CreateBiTree(BiTree *T, int definition);     //第二个参数为创建选项1-3,代表3种不同的创建方式 
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree T);
status BiTreeEmpty(BiTree T);
status BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, int e);
status Assign(BiTree T, int e, TElemType value);      //e为关键字 
BiTNode* GetSibling(BiTree t, int e);
status InsertNode(BiTree T, int e, int LR, BiTree c);
status DeleteNode(BiTree T, int e);
BiTNode* Parent(BiTree, int e);
status PreOrderTraverse(BiTree T, status (*visit)(TElemType e));
status InOrderTraverse(BiTree T, status (*visit)(TElemType e));
status PostOrderTraverse(BiTree T, status (*visit)(TElemType e));
status LevelOrderTraverse(BiTree T, status (*visit)(TElemType e));
void level(BiTree T, int i);       //层序遍历的辅助函数 
status Save(BiTree T,FILE *fp);
status Load(BiTree *T,FILE *fp);

int main(){
	int i, op, num, def;
	BiTNode TList[11];
	for(i=0; i<11; i++){
		TList[i].lchild = NULL;
		TList[i].rchild = NULL;
		TList[i].is_create = 0;              //0表示未创建树，此后输入key值不能为0 
		TList[i].data = '#';                 //data域初始化为# 
	}
	
	printf("\t请输入想要操作的树编号：");
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
        printf("\t请选择你的操作[0~14]:");
        scanf("%d", &op);
        while(!TList[num].is_create && op != 1){
        	printf("\n树未创建！\n");
        	scanf("%d",&op);
		} 
		
        switch(op){
            case 1:                          //创建树 
            	printf("\t请输入definition的值\n");
				printf("\t1代表用 带空子树的二叉树前序遍历序列 创建二叉树\n");
				printf("\t2代表用 前序+中序 创建二叉树\n");
				printf("\t3代表用 中序+后序 创建二叉树\n");
				scanf("%d", &def);
				getchar();   //读取上面输入的回车   
				CreateBiTree(&T, def);
					printf("\t%d号树创建成功\n", num);
				TList[num].is_create = 1;
				getchar(); 
				break;
			case 2:                          //销毁树 
				 DestroyBiTree(&T);
				 T->is_create = 0;
				 printf("\t二叉树已销毁\n");
				 getchar(); getchar();
				 break;
			case 3:                          //清空树 
				ClearBiTree(T);
				getchar(); getchar();
				break;
			case 4:                          //判空 
				if(BiTreeEmpty(T))
					printf("\t二叉树为空\n");
				else
					printf("\t二叉树不为空\n");
				getchar(); getchar();
				break;
			case 5:                          //求深度 
				if(BiTreeEmpty(T))
					printf("\t树的深度为0\n");
				else
					printf("\t树的深度为%d\n" ,BiTreeDepth(T));
				getchar(); getchar();
				break;
			case 6:                          //定位 
				int e;
				printf("\t请输入想要查找的元素key值：");
				scanf("%d", &e);
				Ttemp = LocateNode(T, e);
				if(Ttemp == NULL)
					printf("\t所查元素不在该二叉树中\n");
				else
					printf("\t所查找的元素data为%c\n", Ttemp->data);
				getchar(); getchar();
				break;
			case 7:                          //查找赋值（替换） 
				if (!T){
			   		printf("\t二叉树不存在！\n");
			   		getchar(); getchar();
			   		break;
				}
			    int k; char ch;
				printf("\t请输入你要查找的key:");
				scanf("%d", &k);
				getchar();
				printf("\t请输入你要重新赋值的data:");
				scanf("%c", &ch);
				if (Assign(T, k, ch) != ERROR)
					printf("\t该key对应的data改为了：%c\n", ch);
				else
					printf("\t输入的key在树种不存在！\n");
				getchar(); getchar();
				break; 
			case 8:                          //获取兄弟节点 
				int e2;
				printf("\t请输入你想查找的节点key值，将展示其兄弟节点：\n");
				scanf("%d", &e2);
				GetSibling(T, e2);
				getchar(); getchar();
				break;
			case 9:
				int LR, e3;
				if (T == NULL){
			   		printf("\t二叉树不存在！\n");
			   		getchar();getchar();
			   		break;
				}
				printf("\t请输入你要插入位置的key: ");
				scanf("%d", &e3);
				getchar();
				LocateNode(T, e3);
				printf("\t请输入你想要插入的方向,0表示左边,1表示右边: ");
				scanf("%d", &LR);
				getchar();
				CreateBiTree(&T1, 1);
				if (InsertNode(T, e3, LR, T1) == OK){
				    printf("\t插入成功!\n");
					getchar(); getchar();
				}
				else
				{
				    printf("\t插入失败!\n");
					getchar(); getchar();
				}
				break;
			case 10:
				int e4;
				printf("\t请输入你要删除的节点的key值：");
				scanf("%d", &e4);
				DeleteNode(T, e4);
				getchar(); getchar();
				break;
			case 11:                         //先序遍历 
				PreOrderTraverse(T, visit);
				getchar(); getchar();
				break; 
			case 12:                         //中序遍历 
				InOrderTraverse(T, visit);
				getchar(); getchar();
				break; 
			case 13:                         //后序遍历 
				PostOrderTraverse(T, visit);
				getchar(); getchar();
				break;
			case 14:                         //层序遍历 
				LevelOrderTraverse(T, visit);
				getchar(); getchar();
				break;
			case 15:
				printf("\t请输入要加载的文件名: ");
		       	scanf("%s",filename);
		       	if((fp=fopen(filename,"r"))==NULL)
				   printf("\t加载失败！\n");
		       	else{
		       		if(Load(&T,fp)==OK)
						printf("\t加载成功！\n");
		       		else printf("\t加载失败！\n");
				}
				fclose(fp);
				getchar();getchar();
				break;
			case 16:
				printf("\t请输入要保存的文件名: ");
				scanf("%s", filename);
			    if((fp=fopen(filename,"w"))==NULL) printf("\t\t\t打开文件失败！\n");
		       	else{
		       		if(Save(T,fp) == OK)
					   printf("\t\t\t保存文件成功！\n");
		       		else printf("\t\t\t保存文件失败！\n");
				}
				fclose(fp);
				getchar();getchar();
				break;
			case 17:
				int num_2;
				printf("\t请输入想要切换的树的编号：");
				scanf("%d", &num_2);
				T = &TList[num_2];
				getchar();
				break;
            case 0:                          //输入0终止程序 
             	break;
        }//end obreakf switch
    }//end of while
    printf("\t欢迎下次再使用本系统！\n");
}//end of main()


status visit(TElemType e){               //访问函数，只起打印作用 
	printf("%c ", e);
	return OK;
}


status InitStack(SqStack &S){            //初始化栈 
	S.base = (BiTree*)malloc(50 * sizeof(BiTree));
	if(!S.base)
		exit(OVERFLOW);        //存储分配失败 
	S.top = S.base;
	return OK;
} 


status Push(SqStack &S, BiTree e){     //进栈 
	//插入元素e为新的栈顶元素 
	*S.top = e;
	S.top ++;
	return OK;
}


status Pop(SqStack &S, BiTree &e){     //出栈 
	//若栈不空，则删除S的栈顶元素，用e返回其值， 并返回OK，否则返回ERROR
	if(S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK; 
}


status StackEmpty(SqStack S){         //判断栈是否为空 
	if(S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//用先序和中序建立二叉树 
void xzBuild(BiTree *T, int preL, int preR, int inL, int inR, char pre[], char in[], int pre_num[], int in_num[]){
	if(preL > preR)
		return;
	char e = pre[preL];	int e_num = pre_num[preL];  //找到根 
	int root = inL;          //根在中序序列的起始下标为中序的左边界，下面移动查找真正的根在中序序列中的下标 
	while(in[root]!=e && root<=inR)
		root ++;
	(*T) = (BiTree)malloc(sizeof(BiTNode));
	(*T) -> lchild = NULL;
	(*T) -> rchild = NULL;
	(*T) -> data = e;
	(*T) -> key = e_num;
	xzBuild(&(*T)->lchild, preL+1, preL+root-inL, inL, root-1, pre, in, pre_num, in_num);  //更换边界下标 
	xzBuild(&(*T)->rchild, preL+root-inL+1, preR, root+1, inR, pre, in, pre_num, in_num);  //更换边界下标 
}

//用后序和中序建立二叉树 
void hzBuild(BiTree *T, int postL, int postR, int inL, int inR, char post[], char in2[], int post_num[], int in2_num[]){
	if(postL > postR)
		return;
	char e = post[postR];	int e_num = post_num[postR];  //找到根
	int root = inL;          //根在中序序列的起始下标为中序的左边界，下面移动查找真正的根的下标
	while(in2[root]!=e && root<=inR)
		root ++;
	(*T) = (BiTree)malloc(sizeof(BiTNode));
	(*T) -> lchild = NULL;
	(*T) -> rchild = NULL;
	(*T) -> data = e;
	(*T) -> key = e_num;
	hzBuild(&(*T)->lchild, postL, postR-root+inL-1, inL, root-1, post, in2, post_num, in2_num); //与xzBuild在数学上是对称的 
	hzBuild(&(*T)->rchild, postR-root+inL, postR-1, root+1, inR, post, in2, post_num, in2_num); //同样对称 
}


status CreateBiTree(BiTree *T, int definition){     //第二个参数为创建选项1-3,代表3种不同的创建方式 
	if(definition == 1){
		char ch;
		printf("\t输入data(#表示空):");
		scanf("%c", &ch);
		getchar();         //读取回车 
		if(ch == '#'){
			*T = NULL;
			return ERROR;
		}
		else{
			(*T) = (BiTree)malloc(sizeof(BiTNode));
			(*T)->data = ch;
			printf("\t输入key:");
			scanf("%d", &(*T)->key);
			getchar();     //读取回车
			CreateBiTree(&((*T)->lchild), 1);
			CreateBiTree(&((*T)->rchild), 1);
		}
	} //end of if
	
	else if(definition == 2){
		char pre[50], in[50];
		int pre_num[50], in_num[50];
		int i;
		printf("\t请输入前序序列，回车结束：\n");
		for(i=0; ; i++){
			printf("\t输入data:");
			scanf("%c", &pre[i]);
			getchar();     //读取回车 
			if(pre[i] == '\n'){
				break;
			}
			printf("\t输入key:");
			scanf("%d", &pre_num[i]);
			getchar();    //读取回车 
		}
		
		printf("\t请输入中序序列，回车结束：\n");
		for(i=0; ; i++){
			printf("\t请输入data:");
			scanf("%c", &in[i]);
			if(in[i] == '\n'){
				break;
			}
			getchar();    //读取回车 
			printf("\t请输入key:");
			scanf("%d", &in_num[i]);
			getchar();    //读取回车 
		}
		
		int Len = i - 1;
		xzBuild(T, 0, Len, 0, Len, pre, in, pre_num, in_num);
		return OK;
	} //end of else if
	
	else{
		char post[50], in2[50];
		int post_num[50], in2_num[50];
		int i;
		printf("\t请输入后序序列，回车结束：\n");
		for(i=0; ; i++){
			printf("\t输入data:");
			scanf("%c", &post[i]);
			if(post[i] == '\n'){
				break;
			}
			getchar();     //读取回车 
			printf("\t输入key:");
			scanf("%d", &post_num[i]);
			getchar();     //读取回车 
		}
		
		printf("\t请输入中序序列，回车结束：\n");
		for(i=0; ; i++){
			printf("\t请输入data:");
			scanf("%c", &in2[i]);
			getchar();    //读取回车 
			if(in2[i] == '\n'){
				break;
			}
			printf("\t请输入key:");
			scanf("%d", &in2_num[i]);
			getchar();    //读取回车 

		}
		
		int Len = i - 1;
		hzBuild(T, 0, Len, 0, Len, post, in2, post_num, in2_num);
		return OK;
	} //end of else
} //end of CreatBiTree


status DestroyBiTree(BiTree *T){   //销毁 
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	return OK;
}


status ClearBiTree(BiTree T){  //清空 
	if(T){
		T->lchild = NULL;
		T->rchild = NULL;
		T->data = '#';         //左右子树指针指向空,data域设置为#
		printf("\t二叉树已清空\n");
		return OK;
	}
	else{
		printf("\t二叉树已清空，无需清空\n");
		return ERROR;
	}
}


status BiTreeEmpty(BiTree T){      //判断是否为空 
	if(T->data == '#')
		return TRUE;
	else
		return FALSE;
}


BiTNode* LocateNode(BiTree T, int e){       //定位 
	if(!T) return NULL;   //若二叉树为空,返回ERROR 
	BiTNode *st[10], *p;
	int top = 0;  //置空栈 
	st[top++] = T;
	while(top){
		p = st[--top]; //先序遍历,弹出栈顶元素,判断是否有key的值与e相等
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


status BiTreeDepth(BiTree T){      //求树的深度 
	int depth = 0;
	if(T){
		int lchilddepth = BiTreeDepth(T->lchild);
		int rchilddepth = BiTreeDepth(T->rchild);
		depth = (lchilddepth>=rchilddepth?(lchilddepth+1):(rchilddepth+1));
	}                             //使用递归,得到左右子树的深度,并比较大小,之后返回最大的深度
	return depth;
}


status Assign(BiTree T, int e, TElemType value){      //赋值，e为关键字 
	if (!T) 
		return ERROR;
    BiTNode *st[10], *p;
	int top = 0;
	st[top++] = T;
	while (top){
		p = st[--top];
		if (p->key == e){
			p->data = value;      //找到后进行复制
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
		if (T->rchild!=NULL&&T->rchild->key == e)//如果右孩子不为空并且节点的值符合,那么便返回左孩子的指针
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
		if (T->lchild!=NULL&&T->lchild->key == e)//与上一个函数类似,最后依次递归遍历左子树右子树
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
		printf("\t所找节点的左兄弟节点key:%d，data:%c\n", LeftSibling(T, e)->key, LeftSibling(T, e)->data);
		return LeftSibling(T, e);
	}
	else{
		printf("\t所找节点不存在左兄弟节点\n");
	}
	
	if(RightSibling(T, e)!=NULL){
		printf("\t所找节点的右兄弟节点key:%d，data:%c", RightSibling(T, e)->key, RightSibling(T, e)->data);
		return RightSibling(T, e);
	}
	else{
		printf("\t所找节点不存在右兄弟节点\n");
		return NULL;
	}
}


status InsertNode(BiTree T, int e, int LR, BiTree c){
	BiTree p = LocateNode(T, e);
	if (!T){
		printf("\t\t\t二叉树不存在！");
		return ERROR;
	}
	if (c->rchild != NULL){
		printf("\t\t\t待插入二叉树的右子树不为空！");
		return ERROR;
	}
	if (LR == 0){
		c->rchild = p->lchild; //插入方向为左的情况
		p->lchild = c;
	}
	else{
		c->rchild = p->rchild;  //插入方向为右的情况
		p->rchild = c;
    }
	return OK;
}


status DeleteNode(BiTree T, int e){    //删除节点 
    BiTree p = Parent(T, e);  //找到当前结点的双亲
    BiTree q = LocateNode(T, e);  //找到当前结点
    if (q == NULL)
        return ERROR;
    else if(p == NULL){   //删除结点是头节点
        if(q->lchild == NULL)
            T = T->rchild;
        if(q->rchild == NULL)
            T = T->rchild;
        if(q->lchild!=NULL && q->rchild!=NULL){   //左右子树都非空 
            BiTree c = T->rchild;
            q = q->lchild;
            while(q->rchild != NULL)
                q = q->rchild;
            q->rchild = c;
            T = T->lchild;
        }
    }
    else if(q->rchild==NULL && q->lchild==NULL){    //删除结点的度为0
        if(p->lchild == q){   //删除结点是双亲结点的左孩子
            free(q);
            p->lchild==NULL;
        }
        else{   //右孩子
        
            free(q);
            p->rchild==NULL;
        }
    }
    
	else if(q->lchild!=NULL && q->rchild==NULL){   //删除结点度为1,右子树为空 
        if(p->lchild == q){
            p->lchild = q->rchild;
            free(q);
        }
        else{
            p->rchild = q->rchild;
            free(q);
        }
    }
    
	else if(q->lchild==NULL && q->rchild!=NULL){   //删除结点度为1，右子树为空 
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
            	BiTree c = q->lchild;//寻找删除结点的最右子树
                p->lchild = q->lchild;
                while(c->rchild != NULL)
                    c = c->rchild;
                c->rchild = q->rchild;
            }
        else
            {
                BiTree c = q->lchild;//寻找删除结点的最右子树
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

BiTNode* Parent(BiTree T, int e){         //删除函数的辅助函数，求父节点 
	BiTree T1;                   //利用遍历和递归依次寻找左孩子右孩子对应的e值,符合条件便返回指针
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


status PreOrderTraverse(BiTree T, status (*visit)(TElemType e)){   //递归实现先序遍历 
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


status InOrderTraverse(BiTree T, status (*visit)(TElemType e)){     //非递归（使用栈）实现中序遍历 
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


status PostOrderTraverse(BiTree T, status (*visit)(TElemType e)){    //递归实现后序遍历 
	if(T){
		if(PostOrderTraverse(T->lchild, visit))
			if(PostOrderTraverse(T->rchild, visit))
				if(visit(T->data))//后序遍历，利用递归方式
					return OK;
		return ERROR;
	}
	else return OK;
} 


void level(BiTree T, int i){     //该函数用来辅助层序遍历
	if(T){
		if(i == 1)
			visit(T->data);
		else{
			level(T->lchild, i-1);
			level(T->rchild, i-1);
		}
	}
}

status LevelOrderTraverse(BiTree T, status (*visit)(TElemType e)){  //逐层访问，非递归实现层序遍历 
	if(T){
		int h = BiTreeDepth(T);  //调用函数得到深度
		int i;
		for(i=1; i<=h; i++){
			level(T, i);         //对每一层进行访问
		} 
	}
	else
		return OK;
}


status Save(BiTree T,FILE *fp){
	int i = 0;
	char ch = '#';
	if(T){
        fprintf(fp,"%d%c",T->key,T->data);//将key和data依次写入文件
        if(Save(T->lchild,fp))
        if(Save(T->rchild,fp)) return OK;
        else return ERROR;
	}
	else{
		fprintf(fp,"%d%c",i,ch);          //i和ch初始设置,意味着空节点的key为0,#代表空节点.
		return OK;
	}
}


status Load(BiTree *T,FILE *fp){
	int i;      //用i来表示key
	char ch;    //用ch来读取data域
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
	}    //相当于依次读取之后创建为二叉树
	return OK;
}


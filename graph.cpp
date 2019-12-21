#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_NAME 3

typedef int status;
typedef char VertexType[MAX_NAME]; //MAX_NAME用来表示图的每个顶点所占用的最大字符空间
typedef int InfoType;              //节点信息类型
typedef int QElemType;
int visited[MAX_VERTEX_NUM];       //储存已经访问过的顶点，用于DFS和BFS 

typedef struct ArcNode{
	int adjvex;              //该弧所指向的顶点的位置
	struct ArcNode* nextarc; //指向下一条弧的指针
	InfoType* info;          //该弧相关信息的指针
} ArcNode;

typedef struct{
	VertexType data;   //顶点信息，节点的名称
	int key;           //关键字key用来标记顶点,便于查询
	ArcNode* firstarc; //指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum, arcnum;   //用来表示图的顶点数,边数
	int is_create;        //用来辨别图是否已经创建，0表示未创建，1表示已创建 
} ALGraph;

typedef struct QNode{
	QElemType data;     //队列元素data域
	struct QNode* next; //指针域
} QNode, *QueuePtr;

typedef struct{
	QueuePtr front, rear; //队列前后两个指针
} LinkQueue;

status CreateGraph(ALGraph* G);
status DestroyGraph(ALGraph* G);
status LocateVex(ALGraph G, VertexType u);
VertexType* GetVex(ALGraph G, int i);
status PutVex(ALGraph G, VertexType v, VertexType value);
status FirstAdjVex(ALGraph G, VertexType v);
status NextAdjVex(ALGraph G, VertexType v, VertexType w);
status InsertVex(ALGraph* G, VertexType v);
status DeleteVex(ALGraph* G, VertexType v);
status InsertArc(ALGraph* G, VertexType v, VertexType w);
status DeleteArc(ALGraph* G, VertexType v, VertexType w);
status BFSTraverse(ALGraph G, void (*visit)(char*));
status DFSTraverse(ALGraph G, void (*visit)(char*));
status Save(ALGraph G);
status Load(ALGraph* G);
void visit(char* i); //数据元素类型定义
/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
/*-----page 19 on textbook ---------*/
int main() {
	int op = 1, i, i_num = 1, key;
	VertexType e, v, g, va, vb; //无向图中的节点
	ALGraph G[10];              //十个图
	for (i = 0; i <= 10; i++) {
		G[i].is_create = 0; //初始化为0，表示未创建 
	}
	while (op) {
		system("cls"); //用于清屏
		printf("\n\n");
		printf("\t\t      Menu for Undirected Graph On Chain Structure \n");
		printf("\t******************************************************************************\n");
		printf("\t\t\t1.  CreateGraph \t 2.  DestroyGraph\n");
		printf("\t\t\t3.  LocateVex   \t 4.  GetVex\n");
		printf("\t\t\t5.  PutVex      \t 6.  FirstAdjVex\n");
		printf("\t\t\t7.  NextAdjVex  \t 8.  InsertVex\n");
		printf("\t\t\t9.  DeleteVex   \t 10. InsertArc\n");
		printf("\t\t\t11. DeleteArc   \t 12. DFSTraverse\n");
		printf("\t\t\t13. BFSTraverse \t 14. Save\n");
		printf("\t\t\t15. Load	      \t 16. Choose\n");
		printf("\t\t\t0.  Exit\n");
		printf("\t******************************************************************************\n");
		printf("\t\t\t请选择你的操作[0-16]: ");
		scanf("%d", &op);
		switch (op) {

		case 1: if (CreateGraph(&G[i_num]) == OK)
				printf("\t\t\t创建无向图成功!\n");
			else
				printf("\t\t\t创建无向图失败!\n");
			getchar();
			getchar();
			break;
		case 2: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			if (DestroyGraph(&G[i_num]) == OK)
				printf("\t\t\t销毁无向图成功!\n");
			else
				printf("\t\t\t销毁无向图失败!\n");
			getchar();
			getchar();
			break;
		case 3: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入所要查找的顶点的值：");
			scanf("%s", e);
			if (LocateVex(G[i_num], e) == INFEASTABLE)
				printf("\t\t\t无向图中不存在该节点!\n");
			else
				printf("\t\t\t该顶点的key为%d\n", LocateVex(G[i_num], e) + 1);
			getchar();
			getchar();
			break;
		case 4: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入所要查找的顶点的key值：");
			scanf("%d", &key);
			if (key > G[i_num].vexnum || key < 1)
				printf("\t\t\t无向图中不存在该key值的顶点!\n");
			else {
				printf("\t\t\t所输入的key值对应的顶点为：%s\n", *GetVex(G[i_num], key - 1));
			}
			getchar();
			getchar();
			break;
		case 5: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点: ");
			scanf("%s", e);
			if (LocateVex(G[i_num], e) == INFEASTABLE)
				printf("\t\t\t该顶点不存在!\n");
			else {
				printf("\t\t\t请输入要将该点修改为的值: ");
				scanf("%s", g);
				i = LocateVex(G[i_num], e);
				strcpy(G[i_num].vertices[i].data, g);
				printf("\t\t\tkey为%d的顶点值被修改为了%s\n", i + 1, G[i_num].vertices[i].data);
			}
			getchar();
			getchar();
			break;
		case 6: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点的key：");
			scanf("%d", &key);
			if (key > G[i_num].vexnum || key < 1)
				printf("\t\t\t不存在该key的顶点!\n"); //strcpy(e,*GetVex(G[i_num],key-1));
			else {

				if (FirstAdjVex(G[i_num], *GetVex(G[i_num], key - 1)) == INFEASTABLE)
					printf("\t\t\t该顶点没有邻接顶点!\n");
				else if (FirstAdjVex(G[i_num], *GetVex(G[i_num], key - 1)) == -2)
					printf("\t\t\t该顶点不存在!");
				else {
					printf("\t\t\t该顶点首个邻接顶点为%s\n",
					       G[i_num].vertices[FirstAdjVex(G[i_num], *GetVex(G[i_num], key - 1))].data);
					printf("\t\t\t该顶点首个邻接顶点的key为%d\n", FirstAdjVex(G[i_num], *GetVex(G[i_num], key - 1)) + 1);
				}
			}
			getchar();
			getchar();
			break;
		case 7: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点 v 的key：");
			scanf("%d", &key);
			if (key > G[i_num].vexnum || key < 1)
				printf("\t\t\t不存在该key %d的顶点！", key);
			else {
				printf("\t\t\t请输入和其相对的顶点 w 的key：");
				scanf("%d", &i);
				if (i > G[i_num].vexnum || i < 1)
					printf("\t\t\t不存在该key %d的顶点！", i);
				else {
					if (NextAdjVex(G[i_num], *GetVex(G[i_num], key - 1), *GetVex(G[i_num], i - 1)) == INFEASTABLE)
						printf("\t\t\tw是v的最后一个邻接顶点!\n");
					else if (NextAdjVex(G[i_num], *GetVex(G[i_num], key - 1), *GetVex(G[i_num], i - 1)) == -3)
						printf("\t\t\tv不是w的邻接顶点!\n");
					else
						printf("\t\t\tv相对于w的下一个邻接顶点为 %s\n",
						       G[i_num].vertices[NextAdjVex(G[i_num], *GetVex(G[i_num], key - 1),
						                                    *GetVex(G[i_num], i - 1))].data);
				}

			}
			getchar();
			getchar();
			break;
		case 8: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要添加的顶点: ");
			scanf("%s", v);
			if (LocateVex(G[i_num], v) != INFEASTABLE)
				printf("\t\t\t该顶点已存在,添加失败!\n");
			else {
				if (InsertVex(&G[i_num], v) == OK)
					printf("\t\t\t添加顶点成功!\n");
				else
					printf("\t\t\t添加顶点失败!\n");
			}
			getchar();
			getchar();
			break;
		case 9: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要删除的顶点: ");
			scanf("%s", v);
			if (DeleteVex(&G[i_num], v) == ERROR)
				printf("\t\t\t所要删除的顶点不存在!\n");
			else
				printf("\t\t\t删除顶点成功!\n");
			getchar();
			getchar();
			break;
		case 10: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入边的尾节点和头节点的值(空格作为间隔,如a1 a2):");
			scanf("%s%s", va, vb);
			if (InsertArc(&G[i_num], va, vb) == ERROR)
				printf("\t\t\t添加失败!\n");
			else
				printf("\t\t\t添加成功!\n");
			getchar();
			getchar();
			break;
		case 11: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入边的尾节点和头节点的值(空格作为间隔,如a1 a2):");
			scanf("%s%s", va, vb);
			if (DeleteArc(&G[i_num], va, vb) == ERROR)
				printf("\t\t\t删除失败!\n");
			else
				printf("\t\t\t删除成功!\n");
			getchar();
			getchar();
			break;
		case 12: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t该无向图的深度优先搜索遍历为：");
			DFSTraverse(G[i_num], visit);
			printf("\n");
			getchar();
			getchar();
			break;
		case 13: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t该无向图的广度优先搜索遍历为：");
			BFSTraverse(G[i_num], visit);
			printf("\n");
			getchar();
			getchar();
			break;
		case 14: if (G[i_num].is_create == 0) {
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			if (Save(G[i_num]) == OK)
				printf("\t\t\t文件保存成功!\n");
			else
				printf("\t\t\t文件保存失败!\n");
			getchar();
			getchar();
			break;
		case 15: if (Load(&G[i_num]) == OK)
				printf("\t\t\t加载成功!\n");
			else
				printf("\t\t\t加载失败!\n");
			getchar();
			getchar();
			break;
		case 16: printf("\t\t请输入要在第几个图操作,支持在10个图进行操作: ");
			scanf("%d", &i_num);
			if (i_num < 1 || i_num > 20) {
				printf("\t\t\t不支持在该表上进行操作!\n");
				i_num = 1;
			}
			getchar();
			getchar();
			break;
		case 0: break;
		} //end of switch
	}     //end of while
	printf("\n");
	printf("\t\t\t欢迎下次使用本系统!\n\n");
} //end of main()

//创建图 
status CreateGraph(ALGraph* G) {  
	int i, j, k, m;
	VertexType va, vb; //图中的节点
	ArcNode* p;        //无向图中 边 类型的指针
	printf("\t\t\t图的类型为：无向图\n");
	(*G).is_create = 1;     //置为1表示该图已经创建 
	printf("\t\t\t请输入图的顶点数：");
	scanf("%d", &(*G).vexnum); //将用户想要生成图的节点个数存储起来
	printf("\t\t\t请输入图的边数：");
	scanf("%d", &(*G).arcnum);                                         //将用户想要生成的图的边数存储起来
	printf("\t\t\t请输入%d个顶点的值(<%d个字符,如v1): \n", (*G).vexnum, MAX_NAME); //MAX_NAME用来控制每个节点的名称所占字符大小
	for (i = 0; i < (*G).vexnum; i++) {
		m = i;
		m ++;
		(*G).vertices[i].key = m; //依次为图的节点赋予关键字
		printf("\t\t\t关键字key:%d    顶点值data:", (*G).vertices[i].key);
		scanf("%s", (*G).vertices[i].data); //将用户输入的节点存储到节点类型的data域
		(*G).vertices[i].firstarc = NULL;   //第一条依附该顶点的边的指针指向空
	}
	printf("\t\t\t请输入每条边的尾和头的值\n\t\t\t(空格作为间隔, 如v1 v2):\n");
	for (k = 0; k < (*G).arcnum; k++) {
		printf("\t\t\t边%d:", k + 1);
		scanf("%s%s", va, vb); //边的两个节点
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);                 //获得所输两个节点的位置，即第几个节点
		p = (ArcNode*)malloc(sizeof(ArcNode)); //生成一条边
		p->adjvex = j;
		p->info = NULL;
		p->nextarc = (*G).vertices[i].firstarc;
		(*G).vertices[i].firstarc = p;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->info = NULL;
		p->nextarc = (*G).vertices[j].firstarc;
		(*G).vertices[j].firstarc = p;
	}
	return OK;
}

//销毁图 
status DestroyGraph(ALGraph* G) {
	int i;
	ArcNode *p, *q; //边类型的指针p,q
	for (i = 0; i < (*G).vexnum; i++) {
		p = (*G).vertices[i].firstarc; //p指向第i个节点的 第一条依附于该节点的指针
		while (p)                      //p不为空,就依次将q指向下一条弧,释放p,最后再将p指向q，开始下一次循环
		{
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	(*G).vexnum = 0; //之后将图的信息,顶点数目,边数目,is_create置为0
	(*G).arcnum = 0;
	(*G).is_create = 0;
	return OK;
} 

//根据顶点查关键词 
status LocateVex(ALGraph G, VertexType u) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (!strcmp(u, G.vertices[i].data)) //判断节点名称是否相同
			return i;                       //如果查找成功，返回i的值
	}
	return -1;
} 

//根据关键词查顶点 
VertexType* GetVex(ALGraph G, int i) {
	if (i >= G.vexnum || i < 0)
		printf("对应key值不存在\n"); //因为采用数组存储节点，因此可以随机访问
	return &G.vertices[i].data;
} 

//修改顶点的值 
status PutVex(ALGraph G, VertexType v, VertexType value) {
	int i;
	i = LocateVex(G, v);
	strcpy(G.vertices[i].data, value); //将输入节点的名称改为相应的名称
	return 1;
} 

//查找第一邻接顶点 
status FirstAdjVex(ALGraph G, VertexType v) {
	ArcNode* p;
	status v1 = LocateVex(G, v);
	if (v1 == -1)
		return -2;
	p = G.vertices[v1].firstarc; //调用LocateVex函数,根据返回值，将p指向边
	if (p)
		return p->adjvex;
	else
		return -1;
} 

//查找下一邻接顶点 
status NextAdjVex(ALGraph G, VertexType v, VertexType w) {
	ArcNode* p;
	int v1 = LocateVex(G, v);
	int w1 = LocateVex(G, w);
	if (v1 == -1 || w1 == -1)
		return -2;
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1) {
		p = p->nextarc;
	}
	if (!p)
		return -3; //根据返回值来判断是否有邻接点,是否是最后一个邻接点
	if (!p->nextarc)
		return -1;
	else
		return p->nextarc->adjvex;
} 

//插入顶点 
status InsertVex(ALGraph* G, VertexType v) {
	if ((*G).vexnum == MAX_VERTEX_NUM)
		return ERROR;
	strcpy((*G).vertices[(*G).vexnum].data, v);
	(*G).vertices[(*G).vexnum].key = (*G).vexnum + 1;
	(*G).vertices[(*G).vexnum].firstarc = NULL;
	(*G).vexnum++;
	return OK;
} 

//删除顶点 
status DeleteVex(ALGraph* G, VertexType v) {
	int i, j;
	ArcNode *p, *q;
	j = LocateVex(*G, v);
	if (j == -1)
		return ERROR;
	p = (*G).vertices[j].firstarc;
	while (p) {
		q = p;
		p = p->nextarc;
		free(q);
		(*G).arcnum--;
	}
	(*G).vexnum--;
	for (i = j; i < (*G).vexnum; i++)
		(*G).vertices[i] = (*G).vertices[i + 1];
	for (i = 0; i < (*G).vexnum; i++) {
		p = (*G).vertices[i].firstarc;
		while (p) {
			if (p->adjvex == j) {
				if (p == (*G).vertices[i].firstarc) {
					(*G).vertices[i].firstarc = p->nextarc;
					free(p);
					p = (*G).vertices[i].firstarc;
				}
				else {
					q->nextarc = p->nextarc;
					free(p);
					p = q->nextarc;
				}
			}
			else {
				if (p->adjvex > j)
					p->adjvex--;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
} 

//插入边 
status InsertArc(ALGraph* G, VertexType v, VertexType w) {
	ArcNode* p;
	int i, j;
	i = LocateVex(*G, v);
	j = LocateVex(*G, w);
	if (i == -1 || j == -1)
		return ERROR;
	(*G).arcnum++;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	p->info = NULL;
	p->nextarc = (*G).vertices[i].firstarc;
	(*G).vertices[i].firstarc = p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = i;
	p->info = NULL;
	p->nextarc = (*G).vertices[j].firstarc;
	(*G).vertices[j].firstarc = p;
	return OK;
} 

//删除边 
status DeleteArc(ALGraph* G, VertexType v, VertexType w) {
	ArcNode *p, *q;
	int i, j;
	i = LocateVex(*G, v);
	j = LocateVex(*G, w);
	if (i < 0 || j < 0)
		return ERROR;
	p = (*G).vertices[i].firstarc;
	while (p && p->adjvex != j) {
		q = p;
		p = p->nextarc;
	}
	if (p && p->adjvex == j) {
		if (p == (*G).vertices[i].firstarc)
			(*G).vertices[i].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;
		free(p);
		(*G).arcnum--;
	}
	p = (*G).vertices[j].firstarc;
	while (p && p->adjvex != i) {
		q = p;
		p = p->nextarc;
	}
	if (p && p->adjvex == i) {
		if (p == (*G).vertices[j].firstarc)
			(*G).vertices[j].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;
		free(p);
	}
	return OK;
} 

//初始化队列 
status InitQueue(LinkQueue* Q) {
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
} 

//销毁队列 
status DestroyQueue(LinkQueue* Q) {
	while ((*Q).front) {
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	return OK;
} 

//清空队列 
status ClearQueue(LinkQueue* Q) {
	QueuePtr p, q;
	(*Q).rear = (*Q).front;
	p = (*Q).front->next;
	(*Q).front->next = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	return OK;
} 

//队列判空 
status QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear) //如果前指针等于尾指针,则此时已经为空
		return TRUE;
	else
		return FALSE;
} 

//求队列长度 
int QueueLength(LinkQueue Q) {
	QueuePtr p;
	p = Q.front;
	int i = 0;
	while (Q.rear != p) {
		i++;
		p = p->next;
	}
	return i;
} 

//入队 
status EnQueue(LinkQueue* Q, QElemType e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;         //新节点的data域
	p->next = NULL;      //新节点的next指向空
	(*Q).rear->next = p; //尾指针的下一个节点设置为p所指的新节点
	(*Q).rear = p;       //将尾指针
	return OK;
} 

//出队 
status DeQueue(LinkQueue* Q, QElemType* e) {
	QueuePtr p;
	if ((*Q).front == (*Q).rear)
		return ERROR;
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next; //删除队列元素
	if ((*Q).rear == p)
		(*Q).rear = (*Q).front;
	free(p);
	return OK;
} 

//遍历队列 
status QueueTraverse(LinkQueue Q, void (*vi)(QElemType)) {
	QueuePtr p;
	p = Q.front->next;
	while (p) {
		printf("&d ", p->data); //遍历，输出队列元素的data
		p = p->next;
	}
	printf("\n");
	return OK;
} 

//广度优先搜索 
status BFSTraverse(ALGraph G, void (*visit)(char*)) {
	int i, j, w;
	VertexType va, vb;
	LinkQueue Q;
	for (i = 0; i < G.vexnum; i++)
		visited[i] = FALSE;
	InitQueue(&Q);
	for (i = 0; i < G.vexnum; i++)
		if (!visited[i]) {
			visited[i] = TRUE;         //表示已经访问过该节点
			visit(G.vertices[i].data); //访问该节点的data域
			EnQueue(&Q, i);            //利用队列类型的性质，进行广度优先遍历
			while (!QueueEmpty(Q)) {
				DeQueue(&Q, &j);
				strcpy(va, *GetVex(G, j));
				for (w = FirstAdjVex(G, va); w >= 0; w = NextAdjVex(G, va, strcpy(vb, *GetVex(G, w))))
					if (!visited[w]) {
						visited[w] = TRUE;
						visit(G.vertices[w].data);
						EnQueue(&Q, w);
					}
			}
		}
	printf("\n");
	return OK;
} 

//DFS辅助函数 
void DFS(ALGraph G, int v) {
	int i;
	VertexType va, vb;
	strcpy(va, *GetVex(G, v));
	visited[v] = TRUE;
	printf("%s ", G.vertices[v].data);
	for (i = FirstAdjVex(G, va); i >= 0; i = NextAdjVex(G, va, strcpy(vb, *GetVex(G, i))))
		if (!visited[i])
			DFS(G, i);
} 

//DFS主要函数 
status DFSTraverse(ALGraph G, void (*visit)(char*)) {
	int i;
	for (i = 0; i < G.vexnum; i++)
		visited[i] = FALSE;
	for (i = 0; i < G.vexnum; i++)
		if (!visited[i])
			DFS(G, i);  // 对尚未访问的顶点调用DFS 
	printf("\n");
	return OK;
} 

//访问函数 
void visit(char* i) {
	printf("%s ", i);
}    //仅起打印作用

//写文件函数的辅助函数 
int OutDegree(VNode i) {
	int num = 0;
	ArcNode* p;
	p = i.firstarc;
	while (p != NULL) {
		num++;
		p = p->nextarc;
	}
	return num;
} 

//写入文件 
status Save(ALGraph G) {
	int i, num;
	FILE* fp;
	char filename[30];
	ArcNode* p;
	printf("\t\t\t请输入要保存的文件名: ");
	scanf("%s", &filename);
	if ((fp = fopen(filename, "w")) == NULL) {
		printf("\t\t\t保存文件失败！\n");
		return ERROR;
	}
	fwrite(&G.is_create, sizeof(int), 1, fp);
	fwrite(&G.vexnum, sizeof(int), 1, fp);
	fwrite(&G.arcnum, sizeof(int), 1, fp);
	for (i = 0; i < G.vexnum; i++) {
		fwrite(G.vertices[i].data, sizeof(char), MAX_VERTEX_NUM, fp);
		num = OutDegree(G.vertices[i]);   //获取与顶点相关的存储参数 
		fwrite(&num, sizeof(int), 1, fp);
		if ((p = G.vertices[i].firstarc) != NULL) {
			fwrite(&p->adjvex, sizeof(int), 1, fp);
			while ((p = p->nextarc) != NULL) {
				fwrite(&(p->adjvex), sizeof(int), 1, fp);
			}
		}
	}
	fclose(fp);
	return OK;
} 

//读取文件 
status Load(ALGraph* G) {
	int i, k = 0, num;
	FILE* fp;
	ArcNode* p;
	char filename[30];
	printf("\t\t\t请输入要加载的文件名: ");
	scanf("%s", &filename);
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("\t\t\t文件加载失败！\n");
		return ERROR;
	}
	fread(&G->is_create, sizeof(int), 1, fp);
	fread(&G->vexnum, sizeof(int), 1, fp);
	fread(&G->arcnum, sizeof(int), 1, fp);
	while (fread(G->vertices[k].data, sizeof(char), MAX_VERTEX_NUM, fp)) {
		fread(&num, sizeof(int), 1, fp);
		if (num == 0)
			G->vertices[k].firstarc = NULL;
		else {
			G->vertices[k].firstarc = NULL;
			for (i = 0; i < num; i++) {
				p = (ArcNode*)malloc(sizeof(ArcNode));
				fread(&(p->adjvex), sizeof(int), 1, fp);
				p->info = NULL;
				p->nextarc = (*G).vertices[k].firstarc;
				(*G).vertices[k].firstarc = p;
			}
		}
		k++;
	}
	fclose(fp);
	return OK;
}


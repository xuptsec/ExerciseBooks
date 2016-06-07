#include<stdio.h>
#include<stdlib.h>
#define INFINITE 65535
#define N 8
//定义存储节点结构
typedef struct node{
	int data;                                //存放数据
	struct node * next;                      //存放挂在该链节点的地址
}Node;
Node * Creat(int n)
{
	Node * arr=(Node *)malloc(n*sizeof(Node));
	for(int i=0;i<n;i++)                   //对数据元素进行初始化
	{
		arr[i].data = INFINITE;
		arr[i].next = NULL;
	}
	return arr;
	
}
Node * Resize(Node * arr,int  n,int m)
{
	int i;
	Node * arr2=(Node *)malloc((m*n)*sizeof(Node));   //新建一个动态数组（扩容数组）
	for(i=0;i<n;i++)                                //将以前的数组数据全部迁移到新数组
	{
		arr2[i].data=arr[i].data;
		arr2[i].next=arr[i].next;
	
	}
	for(;i<m*n;i++)                                 //对新数组扩容增加的元素初始化
	{
		arr2[i].data = INFINITE;
		arr2[i].next=NULL;
	}
	free(arr);                     //释放以前的数组
	arr=NULL;
	return arr2;
}
Node * InsertNode(Node * arr,int n,int * count,int * m) //插入数据
{           
	*count=*count+1;
	if(*count>((*m*n)*0.75))                         //判断是否超过负载因子
	{
		*m=(*m)*2;
		arr=Resize(arr,n,*m);                     //对数组进行扩容
		
 }
	int val,index;
	printf("please enter the val:");
	scanf("%d",&val);
	index=val%(*m*n);                         //求出位置下标
	if(arr[index].data == INFINITE)      //判断该下标是否有值
	{
		arr[index].data=val;
	}
	else
	{
		Node * p=(Node*)malloc(sizeof(Node));  //建立新节点，挂链
		p->data=val;
		p->next=NULL;
		Node * q=&arr[index];        //查找要挂的链的地址
		while(q->next)
		{
			q=q->next;
		}
	
		q->next=p;
	}
	return arr;
}

Node * Search(Node * arr,int n,int m,int key)
{
	int index=key%n;
	for(int i=index;i<m*n;i=i+n)                     //先判断扩容之前的，扩容之前若没有，则i=i+n找到扩容之后的
	{
		Node * p=&arr[i];                      
		while(p&&p->data!=key)
			p=p->next;
		if(p)
			return p;
	}
	return NULL;
}
void DelNode(Node * arr,int n,int m,int key)
{
	int index=key%n;
	for(int i=index;i<m*n;i=i+n)
	{
		if(arr[i].data==key)
		{arr[i].data=INFINITE;
		break;
		}
		else
		{
			Node * p=arr[i].next;
			Node * q=&arr[i];
			while(p&&p->data!=key)
			{
				q=p;
				p=p->next;
			}
			if(p)
			{
				q->next=p->next;
				free(p);;
				p=q->next;
				break;
			}
		}
	}
	if(i>=m*n)
		printf("NO FOUND\n");
}
void Traverse(Node * arr,int m)
{
	//printf("%d\n",n);
	for(int i=0;i<m;i++)
	{
		Node * p=&arr[i];
		while(p)
		{
			printf("%d---",p->data);
			p=p->next;
		}
		printf("end\n");
	}
}
int main()
{
	int n=8,count=0,j,m=1;
	int key;
	Node * arr=Creat(n);
	printf("插入几个数据：");
	scanf("%d",&j);
	for(int i=0;i<j;i++)
	{
		arr=InsertNode(arr,n,&count,&m);
	}
	printf("n=%d,m=%d\n",n,m);
	Traverse(arr,n*m);                     //遍历
	printf("key=:");
	scanf("%d",&key);
	Node * p=Search(arr,n,m,key);           //查找key
	printf("%x\n",p);
	DelNode(arr,n,m,key);                  //删除key
	Traverse(arr,n*m);
	free(arr);
	arr=NULL;
	return 0;
}
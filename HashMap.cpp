#include<stdio.h>
#include<stdlib.h>
#define INFINITE 65535
#define N 8
//����洢�ڵ�ṹ
typedef struct node{
	int data;                                //�������
	struct node * next;                      //��Ź��ڸ����ڵ�ĵ�ַ
}Node;
Node * Creat(int n)
{
	Node * arr=(Node *)malloc(n*sizeof(Node));
	for(int i=0;i<n;i++)                   //������Ԫ�ؽ��г�ʼ��
	{
		arr[i].data = INFINITE;
		arr[i].next = NULL;
	}
	return arr;
	
}
Node * Resize(Node * arr,int  n,int m)
{
	int i;
	Node * arr2=(Node *)malloc((m*n)*sizeof(Node));   //�½�һ����̬���飨�������飩
	for(i=0;i<n;i++)                                //����ǰ����������ȫ��Ǩ�Ƶ�������
	{
		arr2[i].data=arr[i].data;
		arr2[i].next=arr[i].next;
	
	}
	for(;i<m*n;i++)                                 //���������������ӵ�Ԫ�س�ʼ��
	{
		arr2[i].data = INFINITE;
		arr2[i].next=NULL;
	}
	free(arr);                     //�ͷ���ǰ������
	arr=NULL;
	return arr2;
}
Node * InsertNode(Node * arr,int n,int * count,int * m) //��������
{           
	*count=*count+1;
	if(*count>((*m*n)*0.75))                         //�ж��Ƿ񳬹���������
	{
		*m=(*m)*2;
		arr=Resize(arr,n,*m);                     //�������������
		
 }
	int val,index;
	printf("please enter the val:");
	scanf("%d",&val);
	index=val%(*m*n);                         //���λ���±�
	if(arr[index].data == INFINITE)      //�жϸ��±��Ƿ���ֵ
	{
		arr[index].data=val;
	}
	else
	{
		Node * p=(Node*)malloc(sizeof(Node));  //�����½ڵ㣬����
		p->data=val;
		p->next=NULL;
		Node * q=&arr[index];        //����Ҫ�ҵ����ĵ�ַ
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
	for(int i=index;i<m*n;i=i+n)                     //���ж�����֮ǰ�ģ�����֮ǰ��û�У���i=i+n�ҵ�����֮���
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
	printf("���뼸�����ݣ�");
	scanf("%d",&j);
	for(int i=0;i<j;i++)
	{
		arr=InsertNode(arr,n,&count,&m);
	}
	printf("n=%d,m=%d\n",n,m);
	Traverse(arr,n*m);                     //����
	printf("key=:");
	scanf("%d",&key);
	Node * p=Search(arr,n,m,key);           //����key
	printf("%x\n",p);
	DelNode(arr,n,m,key);                  //ɾ��key
	Traverse(arr,n*m);
	free(arr);
	arr=NULL;
	return 0;
}
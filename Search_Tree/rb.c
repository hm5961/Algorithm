//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#pragma warning(disable:4996)
//typedef struct __node//��� ����ü
//{
//	int data;//������, Ű��
//	struct __node* left;//���� �ڽ�
//	struct __node* right;//������ �ڽ�
//	int color;//����� ��
//	struct __node* parent;//�θ�
//
//
//}Node;
//
//Node* nilNode;//nil��� ������
//clock_t start,end;
//
//
//void InitTree(Node** root);
//void InsertNode(Node**,int);
//void rotateLeft(Node**,Node*);
//void rotateRight(Node**,Node*);
//void checkViolation(Node**,Node*);
//void SearchTree(Node*,int);
//
//void InitTree(Node** root)//Ʈ�� �ʱ�ȭ
//{
//	*root=NULL;//��Ʈ��带 NULL��
//	nilNode=(Node*)malloc(sizeof(Node));//nilNode �Ҵ�
//	nilNode->color=1;//nilNode�� ���� ����������
//
//}
//
//void rotateLeft(Node** root,Node* p)//��� �������� �������� ȸ����Ű�� �Լ�
//{
//	Node* cur=p->right;//cur�� p�� ������ �ڽ�(x)
//	p->right=cur->left;//p�� ������ �ڽ��� cur�� ���� �ڽ�(����Ʈ�� 1)��
//	if(cur->left!=nilNode)//����Ʈ��1�� nilNode�� �ƴϸ�
//	{
//		cur->left->parent=p;//����Ʈ��1�� �θ� p��
//	}
//
//
//	cur->parent=p->parent;//cur�� �θ��带 p�� �θ����
//	if(p->parent==NULL)//p�� �θ��尡 ���ٸ�
//	{
//		*root=cur;//cur�� ��Ʈ����
//	}
//	else//p�� �θ��尡 �����ϸ�
//	{
//		if(p==p->parent->right)//p�� p�� �θ����� ������ �ڽ��̸�
//			p->parent->right=cur;//p�� �θ��� ������ �ڽ��� cur��
//		else//p�� p�� �θ����� ���� �ڽ��̸�
//			p->parent->left=cur;//p�� �θ��� ���� �ڽ��� cur��
//	}
//	cur->left=p;//cur�� ���� �ڽ��� p��
//	p->parent=cur;//p�� �θ��带 cur��
//
//
//}
//void rotateRight(Node** root,Node* p)//��� �������� ���������� ȸ���ϴ� �Լ�
//{
//	Node* cur=p->left;//cur�� ���(p)�� �����ڽ�(x)��
//	p->left=cur->right;//p�� ���� �ڽ��� cur�� ���� �ڽ�(����Ʈ��2)����
//	if(cur->right!=nilNode)//����Ʈ��2�� nilNode�� �ƴϸ�
//		cur->right->parent=p;//����Ʈ��2�� �θ� p��
//
//	cur->parent=p->parent;//cur�� �θ� p�� �θ��
//	if(p->parent==NULL)//p�� �θ� ���ٸ�
//		*root=cur;//cur�� ��Ʈ����
//	else//p�� �θ� �����ϸ�
//	{
//		if(p==p->parent->left)//p�� p�� �θ��� ���� �ڽ��̸�
//			p->parent->left=cur;//p�� �θ��� ���� �ڽ��� cur��
//		else//p�� p�� �θ��� ������ �ڽ��̸�
//			p->parent->right=cur;//p�� �θ��� ������ �ڽ��� cur��
//
//	}
//	cur->right=p;//cur�� ������ �ڽ��� p��
//	p->parent=cur;//p�� �θ� cur��
//}
//void checkViolation(Node** root,Node* x)//red black tree�� ��Ģ�� �����ϴ��� Ȯ���ϴ� �Լ�
//{
//	while(x!=(*root) && x->parent->color==0)//��尡 ��Ʈ����̰ų� �θ���(p)�� ���� �������� �� ���� �ݺ�
//	{
//		if(x->parent==x->parent->parent->left)//�θ���(p)�� ���θ� ���(p2)�� ���� �ڽ��� ���
//		{
//			if(x->parent->parent->right->color==0)//���̳��(s)�� �������� ���(case1)
//			{
//				x->parent->color=1;//�θ���(p)�� ���� ����������
//				x->parent->parent->right->color=1;//���̳��(s)�� ���� ����������
//				x->parent->parent->color=0;//���θ� ���(p2)�� ���� ����������
//				x=x->parent->parent;//���θ���� �̵�(���)
//			}
//			else//���̳��(s)�� �������� ���(case2)
//			{
//				if(x==x->parent->right)//���(x)�� �θ���(p)�� ������ �ڽ��̸�(case2-1)
//				{
//					x=x->parent;//case2-2���� �Ϲ�ȭ�� ���� ���(x)�� �θ���(p)�� �ٲ�
//					rotateLeft(root,x);//�θ���(p)�� �߽����� �������� ȸ��
//
//				}
//				//���(x)�� �θ���(p)�� ���� �ڽ��� ���(case2-2)
//				x->parent->color=1;//�θ���(p)�� ���� ����������
//				x->parent->parent->color=0;//���θ� ���(p2)�� ���� ����������
//				rotateRight(root,x->parent->parent);//���θ� ���(p2)�� �������� ���������� ȸ��
//			}
//		}
//		else//�θ���(p)�� ���θ���(p2)�� ������ �ڽ��� ���
//		{
//			if(x->parent->parent->left->color==0)//���̳��(s)�� �������� ���(case1)
//			{
//				x->parent->color=1;//�θ���(p)�� ���� ����������
//				x->parent->parent->left->color=1;//���̳��(s)�� ���� ����������
//				x->parent->parent->color=0;//���θ� ���(p2)�� ���� ����������
//				x=x->parent->parent;//���θ� ���(p2)�� �̵�(���)
//			}
//			else
//			{
//				if(x==x->parent->left)//��尡 �θ����� ���� �ڽ��̸�(case2)
//				{
//					x=x->parent;//case2-2���� �Ϲ�ȭ�� ���� ���(x)�� �θ���(p)�� �ٲ�
//					rotateRight(root,x);//�θ���(p)�� �߽����� �������� ȸ��
//
//
//				}
//				x->parent->color=1;//���(x)�� �θ���(p)�� ���� ����������
//				x->parent->parent->color=0;//���(x)�� ���θ���(p2)�� ���� ����������
//				rotateLeft(root,x->parent->parent);//���θ���(p2)�� �������� �������� ȸ��
//			}
//		}
//
//	}
//
//	(*root)->color=1;//��Ʈ��带 ����������
//}
//void InsertNode(Node** root,int data)//��带 �����ϰ� Ʈ���� �����ϴ� �Լ�
//{
//	Node* newNode=(Node*)malloc(sizeof(Node));//��� �Ҵ�
//	newNode->parent=NULL;//����� �θ� NULL�� �ʱ�ȭ
//	newNode->left=nilNode;//����� �����ڽ��� nilNode�� �ʱ�ȭ
//	newNode->right=nilNode;//����� �������ڽ��� nilNode�� �ʱ�ȭ
//	newNode->data=data;//��忡 ������ ����
//	newNode->color=0;//����� ���� ����������
//	if(*root==NULL)//root�� ���ٸ�
//	{
//		(*root)=newNode;//��Ʈ�� ������ ����
//		(*root)->left=nilNode;//��Ʈ����� ���� �ڽ��� nilNode��
//		(*root)->right=nilNode;//��Ʈ����� ������ �ڽ��� nilNode��
//		(*root)->color=1;//��Ʈ����� ���� ����������
//
//	}
//	else//��Ʈ��尡 �����ϸ�
//	{
//		Node* cur=*root;//cur�� ��Ʈ��带 ����Ŵ
//		while(cur!=nilNode)//cur�� nilNode�� �ƴѵ���
//		{
//			if(cur->data<newNode->data)//cur�� ����Ű�� ����� �����ͺ��� ���Գ���� �����Ͱ� ũ��
//			{
//				if(cur->right==nilNode)//cur�� ������ �ڽ��� nilNode��
//				{
//					cur->right=newNode;//cur�� ������ �ڽĿ� ������
//					newNode->parent=cur;//����� �θ� cur��
//					break;//Ž�� ����
//				}
//				else//cur�� ������ �ڽ��� nilNode�� �ƴϸ�
//				{
//					cur=cur->right;//cur�� ������ �ڽ����� �̵�
//				}
//			}
//
//			else//cur�� ����Ű�� ����� �����ͺ��� ���Գ���� �����Ͱ� ������
//			{
//				if(cur->left==nilNode)//cur�� ���� �ڽ��� nilNode�̸�
//				{
//					cur->left=newNode;//cur�� ���� �ڽĿ� nilNode ����
//					newNode->parent=cur;//����� �θ� cur��
//					break;//Ž�� ����
//				}
//				else//cur�� ���� �ڽ��� nilNode�� �ƴϸ�
//				{
//					cur=cur->left;//cur�� ���� �ڽ����� �̵�
//				}
//			}
//		}
//	}
//	checkViolation(root,newNode);//���� �� ��Ģ ���� �˻�
//}
//void SearchTree(Node* root,int data)//�����Ͱ� �����ϴ��� ã�� �Լ�
//{
//	Node* cur=root;//cur�� ��Ʈ����
//	while(cur!=nilNode)//cur�� nilNode�� �ƴѵ���
//	{
//		if(cur->data==data)//cur�� �����Ͱ� ã�� �����Ϳ� ��ġ�ϸ�
//		{
//			printf("%d �� Ʈ���� �����մϴ�.",data);//������ ���
//			return;//�Լ� ����
//		}
//		else if(cur->data<data)//cur�� �����ͺ��� ã�� �����Ͱ� ũ��
//		{
//			cur=cur->right;//cur�� ������ �ڽ����� �̵�
//		}
//		else//cur�� �����ͺ��� ã�� �����Ͱ� ������
//			cur=cur->left;//cur�� ���� �ڽ����� �̵�
//	}
//
//	
//	printf("%d �� Ʈ���� �������� �ʽ��ϴ�.",data);//�����޽��� ���
//	return;//�Լ� ����
//}
//int main()
//{
//	Node* root;//��Ʈ���
//	FILE* file=fopen("33.txt","r");//test.txt������ �б���� ��
//	int intTemp=-1;//�����͸� ���� �ӽú���
//
//	if(file==NULL)//������ ������
//	{
//		printf("File does not exist");//�����޽��� ���
//		return 0;//����
//	}
//	InitTree(&root);//Ʈ�� �ʱ�ȭ
//	clock_t istart=clock();
//	while(1)
//	{
//		fscanf(file,"%d",&intTemp);//���Ͽ��� ������ �ϳ��� �о��
//		if(intTemp<0) break;//-1�̸� ����
//		InsertNode(&root,intTemp);//Ʈ���� ����
//	}
//	fclose(file);//���� ������ �ݱ�
//	clock_t iend=clock();
//	printf("%lf\n",((double)(iend)-(double)istart)/CLOCKS_PER_SEC);
//
//
//	printf("�˻��� �����͸� �Է��ϼ���: ");
//	fflush(stdout);//���� ����
//	int data;
//	scanf("%d",&data);//ã�� ������ �Է�
//	start=clock();
//	SearchTree(root,data);//������ Ž��
//	end=clock();
//	printf("%lf",((double)end-(double)start)/CLOCKS_PER_SEC);
//
//	return 0;
//}
//
//

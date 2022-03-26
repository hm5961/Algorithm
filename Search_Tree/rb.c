//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#pragma warning(disable:4996)
//typedef struct __node//노드 구조체
//{
//	int data;//데이터, 키값
//	struct __node* left;//왼쪽 자식
//	struct __node* right;//오른쪽 자식
//	int color;//노드의 색
//	struct __node* parent;//부모
//
//
//}Node;
//
//Node* nilNode;//nil노드 포인터
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
//void InitTree(Node** root)//트리 초기화
//{
//	*root=NULL;//루트노드를 NULL로
//	nilNode=(Node*)malloc(sizeof(Node));//nilNode 할당
//	nilNode->color=1;//nilNode의 색을 검정색으로
//
//}
//
//void rotateLeft(Node** root,Node* p)//노드 기준으로 왼쪽으로 회전시키는 함수
//{
//	Node* cur=p->right;//cur는 p의 오른쪽 자식(x)
//	p->right=cur->left;//p의 오른쪽 자식을 cur의 왼쪽 자식(서브트리 1)로
//	if(cur->left!=nilNode)//서브트리1이 nilNode가 아니면
//	{
//		cur->left->parent=p;//서브트리1의 부모를 p로
//	}
//
//
//	cur->parent=p->parent;//cur의 부모노드를 p의 부모노드로
//	if(p->parent==NULL)//p의 부모노드가 없다면
//	{
//		*root=cur;//cur을 루트노드로
//	}
//	else//p의 부모노드가 존재하면
//	{
//		if(p==p->parent->right)//p가 p의 부모노드의 오른쪽 자식이면
//			p->parent->right=cur;//p의 부모의 오른쪽 자식을 cur로
//		else//p가 p의 부모노드의 왼쪽 자식이면
//			p->parent->left=cur;//p의 부모의 왼쪽 자식을 cur로
//	}
//	cur->left=p;//cur의 왼쪽 자식을 p로
//	p->parent=cur;//p의 부모노드를 cur로
//
//
//}
//void rotateRight(Node** root,Node* p)//노드 기준으로 오른쪽으로 회전하는 함수
//{
//	Node* cur=p->left;//cur을 노드(p)의 왼쪽자식(x)로
//	p->left=cur->right;//p의 왼쪽 자식을 cur의 왼쪽 자식(서브트리2)으로
//	if(cur->right!=nilNode)//서브트리2가 nilNode가 아니면
//		cur->right->parent=p;//서브트리2의 부모를 p로
//
//	cur->parent=p->parent;//cur의 부모를 p의 부모로
//	if(p->parent==NULL)//p의 부모가 없다면
//		*root=cur;//cur을 루트노드로
//	else//p의 부모가 존재하면
//	{
//		if(p==p->parent->left)//p가 p의 부모의 왼쪽 자식이면
//			p->parent->left=cur;//p의 부모의 왼쪽 자식을 cur로
//		else//p가 p의 부모의 오른쪽 자식이면
//			p->parent->right=cur;//p의 부모의 오른쪽 자식을 cur로
//
//	}
//	cur->right=p;//cur의 오른쪽 자식을 p로
//	p->parent=cur;//p의 부모를 cur로
//}
//void checkViolation(Node** root,Node* x)//red black tree의 규칙을 위반하는지 확인하는 함수
//{
//	while(x!=(*root) && x->parent->color==0)//노드가 루트노드이거나 부모노드(p)의 색이 빨간색일 때 까지 반복
//	{
//		if(x->parent==x->parent->parent->left)//부모노드(p)가 조부모 노드(p2)의 왼쪽 자식일 경우
//		{
//			if(x->parent->parent->right->color==0)//삼촌노드(s)가 빨간색인 경우(case1)
//			{
//				x->parent->color=1;//부모노드(p)의 색을 검은색으로
//				x->parent->parent->right->color=1;//삼촌노드(s)의 색을 검은색으로
//				x->parent->parent->color=0;//조부모 노드(p2)의 색을 빨간색으로
//				x=x->parent->parent;//조부모노드로 이동(재귀)
//			}
//			else//삼촌노드(s)가 검은색인 경우(case2)
//			{
//				if(x==x->parent->right)//노드(x)가 부모노드(p)의 오른쪽 자식이면(case2-1)
//				{
//					x=x->parent;//case2-2로의 일반화를 위해 노드(x)를 부모노드(p)로 바꿈
//					rotateLeft(root,x);//부모노드(p)를 중심으로 왼쪽으로 회전
//
//				}
//				//노드(x)가 부모노드(p)의 왼쪽 자식인 경우(case2-2)
//				x->parent->color=1;//부모노드(p)의 색을 검은색으로
//				x->parent->parent->color=0;//조부모 노드(p2)의 색을 빨간색으로
//				rotateRight(root,x->parent->parent);//조부모 노드(p2)를 기준으로 오른쪽으로 회전
//			}
//		}
//		else//부모노드(p)가 조부모노드(p2)의 오른쪽 자식인 경우
//		{
//			if(x->parent->parent->left->color==0)//삼촌노드(s)가 빨간색인 경우(case1)
//			{
//				x->parent->color=1;//부모노드(p)의 색을 검은색으로
//				x->parent->parent->left->color=1;//삼촌노드(s)의 색을 검은색으로
//				x->parent->parent->color=0;//조부모 노드(p2)의 색을 빨간색으로
//				x=x->parent->parent;//조부모 노드(p2)로 이동(재귀)
//			}
//			else
//			{
//				if(x==x->parent->left)//노드가 부모노드의 왼쪽 자식이면(case2)
//				{
//					x=x->parent;//case2-2로의 일반화를 위해 노드(x)를 부모노드(p)로 바꿈
//					rotateRight(root,x);//부모노드(p)를 중심으로 왼쪽으로 회전
//
//
//				}
//				x->parent->color=1;//노드(x)의 부모노드(p)의 색을 검정색으로
//				x->parent->parent->color=0;//노드(x)의 조부모노드(p2)의 색을 빨간색으로
//				rotateLeft(root,x->parent->parent);//조부모노드(p2)를 기준으로 왼쪽으로 회전
//			}
//		}
//
//	}
//
//	(*root)->color=1;//루트노드를 검은색으로
//}
//void InsertNode(Node** root,int data)//노드를 생성하고 트리에 삽입하는 함수
//{
//	Node* newNode=(Node*)malloc(sizeof(Node));//노드 할당
//	newNode->parent=NULL;//노드의 부모를 NULL로 초기화
//	newNode->left=nilNode;//노드의 왼쪽자식을 nilNode로 초기화
//	newNode->right=nilNode;//노드의 오른쪽자식을 nilNode로 초기화
//	newNode->data=data;//노드에 데이터 삽입
//	newNode->color=0;//노드의 색을 빨간색으로
//	if(*root==NULL)//root가 없다면
//	{
//		(*root)=newNode;//루트를 생성한 노드로
//		(*root)->left=nilNode;//루트노드의 왼쪽 자식을 nilNode로
//		(*root)->right=nilNode;//루트노드의 오른쪽 자식을 nilNode로
//		(*root)->color=1;//루트노드의 색을 검정색으로
//
//	}
//	else//루트노드가 존재하면
//	{
//		Node* cur=*root;//cur이 루트노드를 가리킴
//		while(cur!=nilNode)//cur이 nilNode가 아닌동안
//		{
//			if(cur->data<newNode->data)//cur이 가리키는 노드의 데이터보다 삽입노드의 데이터가 크면
//			{
//				if(cur->right==nilNode)//cur의 오른쪽 자식이 nilNode면
//				{
//					cur->right=newNode;//cur의 오른쪽 자식에 노드삽입
//					newNode->parent=cur;//노드의 부모를 cur로
//					break;//탐색 종료
//				}
//				else//cur의 오른쪽 자식이 nilNode가 아니면
//				{
//					cur=cur->right;//cur을 오른쪽 자식으로 이동
//				}
//			}
//
//			else//cur이 가리키는 노드의 데이터보다 삽입노드의 데이터가 작으면
//			{
//				if(cur->left==nilNode)//cur의 왼쪽 자식이 nilNode이면
//				{
//					cur->left=newNode;//cur의 왼쪽 자식에 nilNode 삽입
//					newNode->parent=cur;//노드의 부모를 cur로
//					break;//탐색 종료
//				}
//				else//cur의 왼쪽 자식이 nilNode가 아니면
//				{
//					cur=cur->left;//cur을 왼쪽 자식으로 이동
//				}
//			}
//		}
//	}
//	checkViolation(root,newNode);//삽입 후 규칙 위반 검사
//}
//void SearchTree(Node* root,int data)//데이터가 존재하는지 찾는 함수
//{
//	Node* cur=root;//cur을 루트노드로
//	while(cur!=nilNode)//cur이 nilNode가 아닌동안
//	{
//		if(cur->data==data)//cur의 데이터가 찾는 데이터와 일치하면
//		{
//			printf("%d 가 트리에 존재합니다.",data);//데이터 출력
//			return;//함수 종료
//		}
//		else if(cur->data<data)//cur의 데이터보다 찾는 데이터가 크면
//		{
//			cur=cur->right;//cur을 오른쪽 자식으로 이동
//		}
//		else//cur의 데이터보다 찾는 데이터가 작으면
//			cur=cur->left;//cur을 왼쪽 자식으로 이동
//	}
//
//	
//	printf("%d 가 트리에 존재하지 않습니다.",data);//에러메시지 출력
//	return;//함수 종료
//}
//int main()
//{
//	Node* root;//루트노드
//	FILE* file=fopen("33.txt","r");//test.txt파일을 읽기모드로 염
//	int intTemp=-1;//데이터를 받을 임시변수
//
//	if(file==NULL)//파일이 없으면
//	{
//		printf("File does not exist");//에러메시지 출력
//		return 0;//종료
//	}
//	InitTree(&root);//트리 초기화
//	clock_t istart=clock();
//	while(1)
//	{
//		fscanf(file,"%d",&intTemp);//파일에서 정수값 하나를 읽어옴
//		if(intTemp<0) break;//-1이면 종료
//		InsertNode(&root,intTemp);//트리에 삽입
//	}
//	fclose(file);//파일 포인터 닫기
//	clock_t iend=clock();
//	printf("%lf\n",((double)(iend)-(double)istart)/CLOCKS_PER_SEC);
//
//
//	printf("검색할 데이터를 입력하세요: ");
//	fflush(stdout);//버퍼 비우기
//	int data;
//	scanf("%d",&data);//찾는 데이터 입력
//	start=clock();
//	SearchTree(root,data);//데이터 탐색
//	end=clock();
//	printf("%lf",((double)end-(double)start)/CLOCKS_PER_SEC);
//
//	return 0;
//}
//
//

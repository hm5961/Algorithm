#include<stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#include <time.h> // 실행시간 측정용

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;
// 트리로 사용 할 노드

void make_clean_tree(Node** h,int tmp); // 트리의 헤드를 생성하는 함수
void insert_node_small_root(Node* h, int tmp); // tmp를 키값으로 가지는 노드를 트리에 삽입하는 함수
void insert_node_big_root(Node* h, int tmp); // tmp를 키값으로 가지는 노드를 트리에 삽입하는 함수
// small : 우측편향일 때 빠른 삽입, big : 좌측편향일 때 빠른 삽입
void search(Node* h, int tmp); // 인풋받은 tmp를 검색하는 함수

/* 시간 측정 기준이 명시되어 있지 않아 각 기능은 사용 직전 생성하는 방향으로 했습니다. */
/* 같은 이유로 트리 초기화나 파일 종료 등 다른 기능 또한 사용하지 않았습니다.*/

int main(void)
{
	double start, end; // 실행시간 측정용
	start = (double)clock() / CLOCKS_PER_SEC; // 실행시간 측정용
	FILE* pFile = fopen("33.txt", "r"); //read mode 

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	} //파일 없을 시 종료

	int num[2] = {0};

	int intTemp = -1; // 텍스트 파일에서 정수를 임시저장 후 넘겨주는 변수
	Node* head = NULL; // 헤드노드

	// 파일 읽기 성공

	//for(int i = 0; i<2; i++)

	fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
	num[0] = intTemp;
	if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
	{
		printf("첫 값이 -1 입니다.");
		return 0;
	}
	make_clean_tree(&head, intTemp); // 헤드노드 트리형태로 초기화

	fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
	num[1] = intTemp;
	if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
	{
		printf("첫 값이 -1 입니다.");
		return 0;
	}
	insert_node_small_root(head, intTemp); // 트리에 intTemp삽입
	if (num[0] > num[1])
	{
		if ((num[0] / num[1]) >= 2)	
			while (1)
			{
				fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
				if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
					break;
				insert_node_small_root(head, intTemp); // 트리에 intTemp삽입
			}
		else
			while (1)
			{
				fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
				if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
					break;
				insert_node_big_root(head, intTemp); // 트리에 intTemp삽입
			}
	}
	else
	{
		if ((num[1] / num[0]) >= 3 / 2)
			while (1)
			{
				fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
				if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
					break;
				insert_node_small_root(head, intTemp); // 트리에 intTemp삽입
			}
		else
			while (1)
			{
				fscanf_s(pFile, "%d", &intTemp); // 파일에서 정수형을 intTemp에 저장
				if (intTemp == -1) // 파일 마지막 요소가 -1이기 때문에 -1이 나오면 종료
					break;
				insert_node_big_root(head, intTemp); // 트리에 intTemp삽입
			}
	}

	end = (((double)clock()) / CLOCKS_PER_SEC); // 실행시간 측정용
	printf("프로그램 수행 시간 :%lf\n", (end - start)); // 실행시간 측정용

	printf("검색할 값을 입력하세요 : ");
	scanf_s("%d", &intTemp);
	search(head, intTemp);
	// 사용자로부터 값을 인풋받아 서치 함수로 넘겨준다.
	
	fclose(pFile);          //close file  //종료시간 단축을 위해 주석처리
	return 0;
}

void make_clean_tree(Node** h, int tmp)
{
	*h = (Node*)malloc(sizeof(Node)); // 헤드를 Node*형으로 동적 메모리 할당 
	(*h)->right = *h; // 헤드노드 오른쪽 지정은 헤드 
	(*h)->key = -52; // 헤드노드 키값 임의 지정 	
	
	Node* n = (Node*)malloc(sizeof(Node));
	n->key = tmp;
	n->left = NULL;
	n->right = NULL;

	(*h)->left = n;
}

void insert_node_small_root(Node* h, int tmp)
{
	Node* n = (Node*)malloc(sizeof(Node)); 
	n->key = tmp;
	n->left = NULL;
	n->right = NULL;
	// tmp의 키값을 가지는 노드 신규 생성 후 left, right는 초기화

	Node* p = h->left; // 연산을 위해 노드 위치 탐색용

	while(1) // break가 나올 때 까지 반복
	{
		if (n->key > p->key) // 인풋받은 값이 p 값보다 큰 경우
		{
			if (p->right == NULL) // p의 right가 비었다면 p->right가 n을 가르키게 한 후 종료
			{
				p->right = n;
				return;
			}
			else // 비어있지 않다면 현재 탐색중인 위치를 p->right로 변경 후 반복
				p = p->right;
		}

		else if (n->key < p->key)// p의 left가 비었다면 p->left가 n을 가르키게 한 후 종료
		{
			if (p->left == NULL)
			{
				p->left = n;
				return;
			}
			else // 비어있지 않다면 현재 탐색중인 위치를 p->left로 변경 후 반복
				p = p->left;
		}
		else if (n->key == p->key)
			return;
			//printf("중복된 값이 존재합니다.\n");
	}
	return;
}
void insert_node_big_root(Node* h, int tmp)
{
	Node* n = (Node*)malloc(sizeof(Node));
	n->key = tmp;
	n->left = NULL;
	n->right = NULL;
	// tmp의 키값을 가지는 노드 신규 생성 후 left, right는 초기화

	Node* p = h->left; // 연산을 위해 노드 위치 탐색용

	while (1) // break가 나올 때 까지 반복
	{
		if (n->key < p->key) // p의 left가 비었다면 p->left가 n을 가르키게 한 후 종료
		{
			if (p->left == NULL)
			{
				p->left = n;
				return;
			}
			else // 비어있지 않다면 현재 탐색중인 위치를 p->left로 변경 후 반복
				p = p->left;
		}

		else if (n->key > p->key) // 인풋받은 값이 p 값보다 큰 경우
		{
			if (p->right == NULL) // p의 right가 비었다면 p->right가 n을 가르키게 한 후 종료
			{
				p->right = n;
				return;
			}
			else // 비어있지 않다면 현재 탐색중인 위치를 p->right로 변경 후 반복
				p = p->right;
		}
		else if (n->key == p->key)
			return;
			//printf("중복된 값이 존재합니다.\n");
	}
}

void search(Node* h, int tmp)
{
	Node* p = h->left; // 연산을 위해 노드 위치 탐색용
	
	while (1)
	{
		double start, end; // 실행시간 측정용
		start = (double)clock() / CLOCKS_PER_SEC; // 실행시간 측정용

		if (p->key == tmp) // 탐색을 성공했을 경우 메세지 출력 후 종료
		{
			printf("%d가 존재합니다.\n", p->key);
			end = (((double)clock()) / CLOCKS_PER_SEC); // 실행시간 측정용
			printf("프로그램 수행 시간 :%lf\n", (end - start)); // 실행시간 측정용
			return;
		}
		
		if (tmp > p->key) //tmp가 현재 탐색중인 p의 키값보다 클 경우 현재 탐색 위치를 p->right로 이동 후 반복
		{
			p = p->right;
		}

		else if (tmp < p->key) //tmp가 현재 탐색중인 p의 키값보다 작을 경우 현재 탐색 위치를 p->left로 이동 후 반복
		{
			p = p->left;
		}

		if ( (p->right == NULL) && (p->left == NULL)  && (p->key != tmp)) // 현재 탐색중인 위치인 p에서 key값이 tmp와 일치하지 않고, 자식노드가 없을경우 오류메세지 출력 후 종료
		{
			printf("%d가 존재하지 않습니다.\n", tmp);
			end = (((double)clock()) / CLOCKS_PER_SEC); // 실행시간 측정용
			printf("프로그램 수행 시간 :%lf\n", (end - start)); // 실행시간 측정용
			return;
		}
	}
}
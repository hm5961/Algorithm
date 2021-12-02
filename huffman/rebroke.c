#include<stdio.h>
#include <stdlib.h> 
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031) // scanf("%s" ,arr); 오류
#pragma warning(disable:6001)
#pragma warning(disable:6011)
typedef struct node {
	int freq;
	char* bin;
	struct node* left;
	struct node* right;
} Node;
// 트리로 사용 할 노드

void input_eng(char* alp, int* cnt);
// 알파벳을 받아서 숫자당 빈도 카운트
void sorting_alp(char* alp, int* cnt, int num);

void make_huffman_tree(Node** h);
void insert_node(Node* h, int* cnt, int* alp, int ncnt);
void recursiveInorder(Node* ptr);
void makecleantree(Node* node, Node* head, int height);
void encoding(Node* n, char* binen, int length, int* alp, int ncnt);
void recursiveInorderbin(Node* ptr);
void read_num(Node* h, char* arr, int* alp, int arrlen, int ncnt);
void recursivereadnum(Node* n, char* arr, char arrcmp, int binlen);
void decoding(Node* n, char* arr, int* alp, int ncnt);
void recursivedecoding(Node* n, int* alp);

void main()
{
	char* arr = malloc(sizeof(char) * 10000); // 인풋받는 영어문자열
	int* cnt = malloc(sizeof(int) * 52); // 알파벳 별 빈도 카운팅용

	//cnt[0]를 arr[0]이 영대문자인지 소문자인지 연산

	for (int i = 0; i < 52; i++)
	{
		cnt[i] = 0; // cnt가 ++연산만 이뤄져서 초기화
	}

	input_eng(arr, cnt); // 문자열 인풋받고 빈도 계산

	Node* head = NULL; // 헤드노드

	int* alp = malloc(sizeof(char) * 52); // 알파벳으로 사용 할 배열

	int ncnt = 0; // 빈도가 1 이상인 알파벳 수 카운트
	for (int i = 0; i < 52; i++)
	{
		if (cnt[i] != 0 && i<26)
		{
			alp[i] = i + 65; // 빈도가 있는 알파벳만 활성화
			ncnt++;
		}
		else if (cnt[i] != 0 && i>=26)
		{
			alp[i] = i + 71; // 빈도가 있는 알파벳만 활성화
			ncnt++;
		}
	}

	int temp;
	// 빈도수 기준 내림차순 버블정렬
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < (52 - 1) - i; j++)
		{
			if (cnt[j] > cnt[j + 1])
			{
				temp = cnt[j];
				cnt[j] = cnt[j + 1];
				cnt[j + 1] = temp;

				temp = alp[j]; // 빈도수기준에 맞게 알파벳도 정렬
				alp[j] = alp[j + 1];
				alp[j + 1] = temp;
			}
		}

	}
	// cnt[] = 0을 뒤로 밀기
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((cnt[i] != 0) && (cnt[j] == 0) && (cnt[i] > cnt[j]))
			{
				temp = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = temp;

				temp = alp[i]; // cnt와 alp 같이 정렬
				alp[i] = alp[j];
				alp[j] = temp;
			}
		}
	}
	for (int i = 0; i < ncnt; i++)
	{
		printf("cnt[%d] = %d", i, cnt[i]);
		printf("alp[%d] = %c\n", i, alp[i]);
	}


	int icnt = 0;
	printf("\nencoding");
	make_huffman_tree(&head); // 허프만트리 헤드노드 생성
	insert_node(head, cnt, alp, ncnt);
	free(cnt);
	printf(".");
	char* binen = malloc(sizeof(char) * 6);
	printf("problem");
	for (int i = 0; i < strlen(binen);i++)
		binen[i] = NULL;
	encoding(head->left, binen, 0, alp, ncnt);
	printf("%d\n", icnt);
	icnt++;
	//recursiveInorderbin(head->left);
	printf(".");
	int arrlen = strlen(arr);
	read_num(head, arr, alp, arrlen, ncnt);
	printf(".\n\n");
	printf("Encoded result: ");
	printf("%s", arr);
	printf("\ndecoding...\n\n");

	printf("Decoded result: ");

	decoding(head->left, arr, alp, ncnt);


	return;

}

void input_eng(char* arr, int* cnt) // 사용자로부터 문자열을 입력받아서 각 영문자별 숫자 카운트
{
	printf("Put the string to encode: ");
	//scanf("%s", arr);
	printf("bdBbeacdEeeAeeDBDcd\n");
	strcpy(arr, "bdBbeacdEeeAeeDBDcd");

	for (int i = 0; i < strlen(arr);i++) 
	{
			sorting_alp(arr, cnt, i);
	}
}
void sorting_alp(char* arr, int* cnt, int num)
{
	int trs_alp = -64;

	trs_alp += arr[num];
	if (arr[num] >= 65 && arr[num] <= 90)
	{
		for (int i = 1; i <= 26; i++)
		{
			if (arr[num] - 64 == i)
			{
				cnt[i - 1]++;
				break;
			}
		}
	}
	else if (arr[num] >= 97 && arr[num] <= 122)
	{
		for (int i = 27; i <= 52; i++)
		{
			if (arr[num]-96 == i-26) // alp가 영문자면 각 영문자에 해당되는 빈도수 ++
			{
				cnt[i - 1]++;
				break;
			}
		}
	}



}
void make_huffman_tree(Node** h) //트리 헤드 생성
{
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = *h;
	(*h)->right = *h;
	(*h)->freq = -52;
	(*h)->bin = '@';

}
void insert_node(Node* h, int* cnt, int* alp, int ncnt)
{
	Node* n[52];
	Node* m[51];
	int i;
	int bincnt = ncnt;
	for (i = 1; i < 52; i++)
	{
		if (bincnt & (bincnt - 1)) // 2제곱수 만들기
			bincnt++;
		else
			break;
	}
	//n = (Node*)malloc(sizeof(Node));  // 가장 적은빈도 순으로 사용할 노드들
	//m = (Node*)malloc(sizeof(Node)); // 리프노드 위에서 freq을 저장할 노드들
	for (i = 0; i < ncnt; i++)
	{
		n[i] = (Node*)malloc(sizeof(Node));  // 가장 적은빈도 순으로 사용할 
	}
	for (i = 0; i < bincnt - 1; i++)
	{
		m[i] = (Node*)malloc(sizeof(Node)); // 리프노드 위에서 freq을 저장할 노드들
	}
	for (i = 0; i < ncnt; i++) // n[i] 초기화
	{

		n[i]->bin = alp[i];
		n[i]->freq = cnt[i];
		n[i]->left = NULL;
		n[i]->right = NULL;

	}

	for (i = 0; i < bincnt - 1; i++) // m[i] 초기화
	{
		m[i]->bin = 0; //bincnt - 2 - i;
		m[i]->freq = 0;
		m[i]->left = NULL;
		m[i]->right = NULL;
	}
	int mcnt = 0; // 사용된 m카운트
	i = 0;
	for (int j = 0; j < ncnt; j++) // 동일값끼리 우선 묶음
	{
		if (i > ncnt - 1)
			break;

		if ((i + 1) < ncnt && (n[i]->freq == n[i + 1]->freq)) // freq이 같은값 있으면 묶기
		{
			m[mcnt]->left = n[i];
			m[mcnt]->right = n[i + 1];
			m[mcnt]->freq = n[i]->freq + n[i + 1]->freq;
			i += 2;
			mcnt++;
		}
		else if (n[i]->freq) // 동일값 없으면 넘기기
		{
			m[mcnt]->left = n[i];
			m[mcnt]->freq = n[i]->freq;
			i++;
			mcnt++;
		}
	}


	int tcal;

	//printf("d\n");
	while (1)
	{


		for (int i = bincnt / 2; i < bincnt - 1; i++) // m[i] 초기화
		{
			tcal = bincnt - 2 - i;
			m[i]->left = m[i - tcal - 2];
			m[i]->right = m[i - tcal - 1];
			m[i]->freq = m[i - tcal - 2]->freq + m[i - tcal - 1]->freq;
		}
		h->left = m[bincnt - 2];
		break;
	}

	printf("before make tree\n");
	recursiveInorder(h->left);
	printf("\n");
	makecleantree(h->left, h, (bincnt - 2) / 2);
	printf("after make tree\n");
	recursiveInorder(h->left);
	printf("\n");
	return;
}
void recursiveInorder(Node* ptr)
{
	if (ptr) { // ptr의 자식노드로 재귀된 값이 노드의 형태 일 때 
		recursiveInorder(ptr->left); // 왼쪽 자식노드 재귀로 탐색  
		if(!(ptr->left)&&!(ptr->right))
			printf(" [%d] ", ptr->freq); // 탐색된 값 출력 
		recursiveInorder(ptr->right); // 오른쪽 자식 노드 재귀로 탐색 
	}
}
void makecleantree(Node* n, Node* p, int height) // 조건부 삭제
{
	if (n)
	{
		if ( (n->left!=NULL) || (n->right!=NULL)) {
			if (height > 0)
			{
				if (n->left)
				{
					height--;
					makecleantree(n->left, n, height); // 왼쪽 자식노드 재귀로 탐색  
				}

				height++;

				if (n->freq == n->left->freq)
				{
					if (p->left == n)
					{
						p->left = n->left;
						height++;
					}
					else if (p->right == n)
					{
						p->right = n->left;
						height++;
					}
				}
				else if (n->freq == n->right->freq)
				{
					if (p->left == n)
					{
						p->left = n->right;
						height++;
					}
					else if (p->right == n)
					{
						p->right = n->right;
						height++;
					}
				}
				if (n->right)
				{
					height--;
					makecleantree(n->right, n, height); // 오른쪽 자식 노드 재귀로 탐색 
				}
			}
		}
	}

}
int ecnt = 0;
void encoding(Node* n, char* binen, int length, int* alp, int ncnt)
{
	if (n)
	{
		if (n->left)
		{
			binen[length] = '0';
			encoding(n->left, binen, length + 1, alp, ncnt);
		}
		if ((n->left == NULL) && (n->right == NULL))
		{
			n->freq = alp[ecnt]; // alp는 중위탐색순으로 할당되어있어 재귀함수일때 전역변수 사용가능

			n->bin = malloc(sizeof(char) * length); // binen 문자열 복사에 앞서 동적할당
			binen[length] = '\0';

			strcpy(n->bin, binen); // 문자열 복사
			ecnt++;
		}

		if (n->right)
		{
			binen[length] = '1';
			encoding(n->right, binen, length + 1, alp, ncnt);
		}

	}
}
void recursiveInorderbin(Node* ptr)
{
	if (ptr) { // ptr의 자식노드로 재귀된 값이 노드의 형태 일 때 
		recursiveInorderbin(ptr->left); // alp, ncnt); // 왼쪽 자식노드 재귀로 탐색  
		if (!ptr->left && !ptr->right)
			printf("[%c = %s]", ptr->freq, ptr->bin); // 탐색된 값 출력 
		recursiveInorderbin(ptr->right);//, alp, ncnt); // 오른쪽 자식 노드 재귀로 탐색 
	}
}
void read_num(Node* h, char* arr, int* alp, int arrlen, int ncnt)
{
	int binsum = 0; // 누적 bin축적
	for (int i = 0; i < strlen(arr); i++)
	{
		for (int j = 0; j < ncnt; j++)
		{
			if (arr[i] == alp[j]) // alp에 존재하는지 확인
				recursivereadnum(h->left, arr, arr[i], strlen(arr));
		}
	}
}

int prevlen = 0;
void recursivereadnum(Node* n, char* arr, char arrcmp)
{
	if (n)
	{
		if (n->left)
			recursivereadnum(n->left, arr, arrcmp);
		if (!(n->left) && !(n->right))
		{

			if (arrcmp == n->freq) // arr[i] == n->freq일떄
			{
				int binlen = strlen(n->bin);
				int arrlen = strlen(arr) + binlen;
				char* temp = malloc(sizeof(char) * arrlen);



				strcpy(temp, n->bin);

				strcat(temp, arr + prevlen + 1);


				strcpy(arr + prevlen, temp);
				prevlen += binlen;

			}
		}

		if (n->right)
			recursivereadnum(n->right, arr, arrcmp);

	}
}

int freqcnt = 0;

void decoding(Node* n, char* arr, int* alp, int ncnt)
{
	Node* p = n;
	for (int i = 0; i < strlen(arr);i++)
	{
		if (p->left && arr[i] == 48) //아스키 코드 기준 0
			p = p->left;

		else if (p->right && arr[i] == 49)// 아스키 코드 기준 1
			p = p->right;

		if (!(p->left) && !(p->right))
		{
			for (int j = 0; j < ncnt;j++)
			{
				if (alp[j] == p->freq)
				{
						printf("%c", alp[j]); // 변환없이 출력만
						p = n;
				}
			}
		}

	}
}

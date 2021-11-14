#include<stdio.h>
#include<string.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;
// 트리로 사용 할 노드

void input_eng(char alp);
// 알파벳을 받아서 숫자당 빈도 카운트

int encoding();
void read_num(); // 트리 좌우 타고 다니며 수에 해당하는 이진코드 나오게하는 함수

char decoding();

// 중위탐색으로 진행할 것

// if(p->left \or\ right == (int)p->left \or\ right))
// {
//		p=p->left 
//		\or\
//		p= p->right
// }

void main()
{
	char alp = "";
	input_eng(alp);
	printf("");
}

void input_eng(char alp)
{

}

char decoding()
{

}

int encoding()
{

}

#include<stdio.h>
#include<string.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;
// Ʈ���� ��� �� ���

void input_eng(char alp);
// ���ĺ��� �޾Ƽ� ���ڴ� �� ī��Ʈ

void read_num(); // Ʈ�� �¿� Ÿ�� �ٴϸ� ���� �ش��ϴ� �����ڵ� �������ϴ� �Լ�

int decoding();
char incoding();

// ����Ž������ ������ ��

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

int decoding()
{

}

char incoding()
{

}
#include<stdio.h>
#include <stdlib.h> 
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031) // scanf("%s" ,arr); ����
#pragma warning(disable:6001)
#pragma warning(disable:6011)
typedef struct node {
	int freq;
	char* bin;
	struct node* left;
	struct node* right;
} Node;
// Ʈ���� ��� �� ���

void input_eng(char* alp, int* cnt);
void sorting_alp(char* alp, int* cnt, int num);
// ���ĺ��� �޾Ƽ� ���ڴ� �� ī��Ʈ

void make_huffman_tree(Node** h);
// ����� ����

void insert_node(Node* h, int* cnt, int* alp, int ncnt);
// n�� ��Ʈ���� ���� ���� ����Ʈ�� ����

void makecleantree(Node* node, Node* head, int height);
// ���� �󵵳��� ���� �󵵰� 0�̰ų� �� �� �ڽĳ��� ���� �θ��� ����

void encoding(Node* n, char* binen, int length, int* alp, int ncnt);
// ��������� ���� Ž���ϸ� �迭�� 0/1 �߰� �� ��Ʈ���� 2������ �̷���� �迭�� �ش� ��忡 ���� 

void read_num(Node* h, char* arr, int* alp, int arrlen, int ncnt);
// ��忡 ����� 2�� �迭�� ���� ��������� ����Ž���ϸ� �������� arr�� 2���迭�� ��ȯ

void decoding(Node* n, char* arr, int* alp, int ncnt);
// 2�� �迭�� ����� arr�� 0/1������ Ž���ϸ� ��Ʈ��� �� ��� �ش� ���̸�ŭ�� 2���迭�� �����ڷ� ��ȯ

void main()
{
	char* arr = malloc(sizeof(char) * 10000); // ��ǲ�޴� ����ڿ�
	int* cnt = malloc(sizeof(int) * 52); // ���ĺ� �� �� ī���ÿ�

	//cnt[0]�� arr[0]�� ���빮������ �ҹ������� ����

	for (int i = 0; i < 52; i++)
	{
		cnt[i] = 0; // cnt�� ++���길 �̷����� �ʱ�ȭ
	}

	input_eng(arr, cnt); // ���ڿ� ��ǲ�ް� �� ���

	Node* head = NULL; // �����

	int* alp = malloc(sizeof(char) * 52); // ���ĺ����� ��� �� �迭

	int ncnt = 0; // �󵵰� 1 �̻��� ���ĺ� �� ī��Ʈ
	for (int i = 0; i < 52; i++)
	{
		if (cnt[i] != 0 && i < 26)
		{
			alp[i] = i + 65; // �󵵰� �ִ� ���ĺ��� Ȱ��ȭ
			ncnt++;
		}
		else if (cnt[i] != 0 && i >= 26)
		{
			alp[i] = i + 71; // �󵵰� �ִ� ���ĺ��� Ȱ��ȭ
			ncnt++;
		}
	}

	int temp;
	// �󵵼� ���� �������� ��������
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < (52 - 1) - i; j++)
		{
			if (cnt[j] > cnt[j + 1])
			{
				temp = cnt[j];
				cnt[j] = cnt[j + 1];
				cnt[j + 1] = temp;

				temp = alp[j]; // �󵵼����ؿ� �°� ���ĺ��� ����
				alp[j] = alp[j + 1];
				alp[j + 1] = temp;
			}
		}

	}
	// cnt[] = 0�� �ڷ� �б�
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((cnt[i] != 0) && (cnt[j] == 0) && (cnt[i] > cnt[j]))
			{
				temp = cnt[i];
				cnt[i] = cnt[j];
				cnt[j] = temp;

				temp = alp[i]; // cnt�� alp ���� ����
				alp[i] = alp[j];
				alp[j] = temp;
			}
		}
	}


	printf("\nencoding");
	make_huffman_tree(&head); // ������Ʈ�� ����� ����
	insert_node(head, cnt, alp, ncnt);
	free(cnt);
	printf(".");
	char* binen = malloc(sizeof(char) * 6);
	for (int i = 0; i < strlen(binen); i++)
		binen[i] = NULL;

	encoding(head->left, binen, 0, alp, ncnt);
	printf(".");
	int arrlen = strlen(arr);
	read_num(head, arr, alp, arrlen, ncnt);
	printf(".\n\n");
	printf("Encoded result: ");
	printf("%s", arr);
	printf("\ndecoding...\n\n");

	printf("Decoded result: ");

	decoding(head->left, arr, alp, ncnt);

	printf("%s\n", arr);
	return;

}

void input_eng(char* arr, int* cnt) // ����ڷκ��� ���ڿ��� �Է¹޾Ƽ� �� �����ں� ���� ī��Ʈ
{
	printf("Put the string to encode: ");
	scanf("%s", arr);
	for (int i = 0; i < strlen(arr); i++)
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
			if (arr[num] - 96 == i - 26) // alp�� �����ڸ� �� �����ڿ� �ش�Ǵ� �󵵼� ++
			{
				cnt[i - 1]++;
				break;
			}
		}
	}
	else
		printf("input string is not alphabet");



}
void make_huffman_tree(Node** h) //Ʈ�� ��� ����
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
		if (bincnt & (bincnt - 1)) // 2������ �����
			bincnt++;
		else
			break;
	}
	for (i = 0; i < ncnt; i++)
	{
		n[i] = (Node*)malloc(sizeof(Node));  // ���� ������ ������ ����� 
	}
	for (i = 0; i < bincnt - 1; i++)
	{
		m[i] = (Node*)malloc(sizeof(Node)); // ������� ������ freq�� ������ ����
	}
	for (i = 0; i < ncnt; i++) // n[i] �ʱ�ȭ
	{

		n[i]->bin = alp[i];
		n[i]->freq = cnt[i];
		n[i]->left = NULL;
		n[i]->right = NULL;

	}

	for (i = 0; i < bincnt - 1; i++) // m[i] �ʱ�ȭ
	{
		m[i]->bin = 0; //bincnt - 2 - i;
		m[i]->freq = 0;
		m[i]->left = NULL;
		m[i]->right = NULL;
	}
	int mcnt = 0; // ���� mī��Ʈ
	i = 0;
	for (int j = 0; j < ncnt; j++) // ���ϰ����� �켱 ����
	{
		if (i > ncnt - 1)
			break;

		if ((i + 1) < ncnt && (n[i]->freq == n[i + 1]->freq)) // freq�� ������ ������ ����
		{
			m[mcnt]->left = n[i];
			m[mcnt]->right = n[i + 1];
			m[mcnt]->freq = n[i]->freq + n[i + 1]->freq;
			i += 2;
			mcnt++;
		}
		else if (n[i]->freq) // ���ϰ� ������ �ѱ��
		{
			m[mcnt]->left = n[i];
			m[mcnt]->freq = n[i]->freq;
			i++;
			mcnt++;
		}
	}


	int tcal;

	while (1)
	{


		for (int i = bincnt / 2; i < bincnt - 1; i++) // m[i] �ʱ�ȭ
		{
			tcal = bincnt - 2 - i;
			m[i]->left = m[i - tcal - 2];
			m[i]->right = m[i - tcal - 1];
			m[i]->freq = m[i - tcal - 2]->freq + m[i - tcal - 1]->freq;
		}
		h->left = m[bincnt - 2];
		break;
	}

	makecleantree(h->left, h, (bincnt - 2) / 2);
	return;
}
void makecleantree(Node* n, Node* p, int height) // ���Ǻ� ����
{
	if (n)
	{
		if ((n->left != NULL) || (n->right != NULL)) {
			if (height > 0)
			{
				if (n->left)
				{
					height--;
					makecleantree(n->left, n, height); // ���� �ڽĳ�� ��ͷ� Ž��  
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
					makecleantree(n->right, n, height); // ������ �ڽ� ��� ��ͷ� Ž�� 
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
			n->freq = alp[ecnt]; // alp�� ����Ž�������� �Ҵ�Ǿ��־� ����Լ��϶� �������� ��밡��

			n->bin = malloc(sizeof(char) * length); // binen ���ڿ� ���翡 �ռ� �����Ҵ�
			binen[length] = '\0';

			strcpy(n->bin, binen); // ���ڿ� ����
			ecnt++;
		}

		if (n->right)
		{
			binen[length] = '1';
			encoding(n->right, binen, length + 1, alp, ncnt);
		}

	}
}

void read_num(Node* h, char* arr, int* alp, int arrlen, int ncnt)
{
	int binsum = 0; // ���� bin����
	for (int i = 0; i < strlen(arr); i++)
	{
		for (int j = 0; j < ncnt; j++)
		{
			if (arr[i] == alp[j]) // alp�� �����ϴ��� Ȯ��
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

			if (arrcmp == n->freq) // arr[i] == n->freq�ϋ�
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
	int tcnt = 0; // ��Ż ī��Ʈ
	int cnt = 0; // ���� ī��Ʈ
	int icnt = 0;
	for (int i = 0; i < strlen(arr); i++)
	{

		if (p->left && arr[i] == 48) //�ƽ�Ű �ڵ� ���� 0
		{
			cnt++;
			p = p->left;
		}

		else if (p->right && arr[i] == 49)// �ƽ�Ű �ڵ� ���� 1
		{
			cnt++;
			p = p->right;
		}

		if (!(p->left) && !(p->right))
		{
			for (int j = 0; j < ncnt; j++)
			{
				if (alp[j] == p->freq)
				{
					tcnt += cnt;


					int arrlen = strlen(arr) - cnt;
					char* temp = malloc(sizeof(char) * arrlen);

					temp[0] = p->freq;
					for (int k = 1; k < strlen(temp); k++)
					{
						temp[k] = arr[k + i];
					}

					strcpy(arr + icnt, temp);
					p = n;
					cnt = 0;
					i = icnt;
					icnt++;
				}
			}
		}
	}
}
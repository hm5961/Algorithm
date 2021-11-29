#include<stdio.h>
#include <stdlib.h> 
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:2371)

typedef struct node {
    int freq;
    int alpha;
    char bin[4]; // 알파벳 26 최대 4bit
    struct node* left;
    struct node* right;
} Node;
// 트리로 사용 할 노드

void input_eng(char* alp, int* cnt);
// 알파벳을 받아서 숫자당 빈도 카운트
void sorting_alp(char* alp, int* cnt, int num);

void make_huffman_tree(Node** h);
void insert_node(Node* h, int* cnt, int* alp, int ncnt);
void insert_tree(Node* h, Node* m, Node* n1, Node* n2, int* cnt, int* alp, int num);
void recursiveInorder(Node* ptr);

void recursivedelete(Node* node);
Node* makecleantree(Node* node, Node* head, int height);
void InOrderPrintTree(Node* node);
int encoding();
int read_num(Node* h); // 트리 좌우 타고 다니며 수에 해당하는 이진코드 나오게하는 함수

char decoding();

void main()
{
    char* arr = malloc(sizeof(char) * 10000); // 인풋받는 영어문자열
    int* cnt = malloc(sizeof(int) * 26); // 빈도


    for (int i = 0; i <= 26; i++)
    {
        cnt[i] = 0; // cnt가 ++연산만 이뤄져서 초기화
    }

    input_eng(arr, cnt); // 문자열 인풋받고 빈도 계산

    Node* head = NULL; // 헤드노드


    int* alp = malloc(sizeof(char) * 26); // 알파벳으로 사용 할 배열

    int ncnt = 0; // 빈도가 1 이상인 알파벳 수 카운트
    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] != 0)
        {
            alp[i] = i + 1; // 초기값 지정
            ncnt++;
            //printf("%c : %d / %d\n", alp[i] + 64, cnt[i], alp[i]);
        }
    }

    int temp;
    // 빈도수 기준 내림차순 버블정렬
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < (26 - 1) - i; j++)
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
    for (int i = 0; i < 26; i++)
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

    // 테스터
    printf("\n");
    for (int i = 0; i < 26; i++)
    {
        //for(int j = 0; j<25; j++)
        //   if (cnt[i] == 0)
        //   {
        //      alp[i] = 0;
        //   }
           //if (cnt[i] != 0)
           //{
           //   temp = cnt[j-i];
           //   cnt[j-i] = cnt[i];
           //   cnt[i] = temp;

           //   alp[i] = 0;
           //}

        if (cnt[i] != 0)
            printf("alp[%d] : %c / cnt[%d] : %d / alp[%d] : %d\n", i, alp[i] + 64, i, cnt[i], i, alp[i]);
    }

    //printf("%d\n", ncnt);

    make_huffman_tree(&head); // 허프만트리 헤드노드 생성

    insert_node(head, cnt, alp, ncnt);
    printf("\n out to main \n");

    return;

}

void input_eng(char* arr, int* cnt)
{
    printf("Put the string to encode: ");
    scanf("%s", arr);

    for (int i = 0; i < _msize(arr); i++)
    {
        sorting_alp(arr, cnt, i);
    }
}

void sorting_alp(char* arr, int* cnt, int num)
{
    int trs_alp = -64;
    int i;

    trs_alp += arr[num];

    for (i = 1; i <= 26; i++)
    {
        if (trs_alp == i || trs_alp + 32 == i)
        {
            cnt[i - 1]++;
            break;
        }
    }
    //for (i = 0; i <= 26; i++)
    //{
    //    free(arr[i]);
    //}

}

void make_huffman_tree(Node** h)
{
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = *h;
    (*h)->right = *h;
    (*h)->freq = -52;
    (*h)->alpha = '@';

}

void insert_node(Node* h, int* cnt, int* alp, int ncnt)
{
    Node* n[26];
    Node* m[25];
    int i;
    int bincnt = ncnt;
    for (i = 1; i < 9; i++)
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
        n[i] = (Node*)malloc(sizeof(Node));  // 가장 적은빈도 순으로 사용할 노드들
    }
    for (i = 0; i < bincnt - 1; i++)
    {
        m[i] = (Node*)malloc(sizeof(Node)); // 리프노드 위에서 freq을 저장할 노드들
    }

    for (i = 0; i < ncnt; i++) // n[i] 초기화
    {
        n[i]->alpha = alp[i] + 64;
        n[i]->freq = cnt[i];
        n[i]->left = NULL;
        n[i]->right = NULL;
    }
    for (i = 0; i < bincnt - 1; i++) // m[i] 초기화
    {
        m[i]->alpha = 122-i; //bincnt - 2 - i;
        m[i]->freq = 0;
        m[i]->left = NULL;
        m[i]->right = NULL;
    }
    //for (i = 0; i <= 26; i++)
    //{
    //    free(alp[i]);
    //    free(cnt[i]);
    //}
    int mcnt = 0; // 사용된 m카운트
    i = 0;
    for (int j = 0; j < ncnt; j++) // 동일값끼리 우선 묶음
    {
        if (i > ncnt - 1)
            break;

        if ((n[i]->freq == n[i + 1]->freq))//&& (i+2<ncnt))
        {
            m[mcnt]->left = n[i];
            m[mcnt]->right = n[i + 1];
            m[mcnt]->freq = n[i]->freq + n[i + 1]->freq;

            i += 2;
            mcnt++;
        }
        else //if(n[i]->freq)
        {
            m[mcnt]->left = n[i];
            m[mcnt]->freq = n[i]->freq;
            i++;
            mcnt++;
        }
    }


    int tcal;

    printf("d\n");
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
    recursiveInorder(h->left); // 고정 길이 코드
    printf("\n");
    printf("into the clean tree\n");
    makecleantree(h->left, h, (bincnt - 2) / 2);
    printf("in to insert\n");
    recursiveInorder(h->left);
    return;
}
void recursiveInorder(Node* ptr)
{
    if (ptr) { // ptr의 자식노드로 재귀된 값이 노드의 형태 일 때 
        recursiveInorder(ptr->left); // 왼쪽 자식노드 재귀로 탐색  
        printf(" [%d] ", ptr->freq); // 탐색된 값 출력 
        recursiveInorder(ptr->right); // 오른쪽 자식 노드 재귀로 탐색 
    }
}
int roop = 0;
Node* makecleantree(Node* n, Node* p, int height) // 조건부 삭제
{
    printf("---------------a\n");
    if ((height >= 1)&&(((n->alpha > 64) && (n->alpha < 91)) || ((n->alpha > 96) && (n->alpha < 123))))
    { // n의 높이가 정상범위이며 n->alpha값이 영 대/소문자 범위일 경우
        printf("alpha = %d\n", n->alpha);
        if (((n->left->alpha > 64) && (n->left->alpha < 91)) || ((n->left->alpha > 96) && (n->left->alpha < 123)))
        {
            printf("go to left\n");
            height--;
            roop++;
            printf("roop = %d\n",roop);
            makecleantree(n->left, n, height); // 왼쪽 자식노드 재귀로 탐색  
        }

        if (n->freq == 0)
        {
            printf("in height = %d \t n->alpha = %d \t n->freq = %d\n", height, n->alpha, n->freq);
            printf("a");
            recursivedelete(n);
            height++;
        }
        else if (n->freq == n->left->freq)
        {
            printf("in height = %d \t n->alpha = %d \t n->freq = %d\n", height, n->alpha, n->freq);
            printf("b");
            if (p->left == n)
            {
                printf("-1\n");
                p->left = n->left;
                free(n);
                height++;
            }
            else if (p->right == n)
            {
                printf("-2\n");
                printf("1...");
                p->right = n->left;
                printf("2...");
                recursivedelete(n->right);
                free(n);
                printf("3...");
                height++;
                printf("---end\n");
            }
        }
        else if (n->freq == n->right->freq)
        {
            printf("in height = %d \t n->alpha = %d \t n->freq = %d\n", height, n->alpha, n->freq);
            printf("c");
            if (p->left == n)
            {
                printf("-1\n");
                p->left = n->right;
                free(n);
                height++;
            }
            else if (p->right == n)
            {
                printf("-2");
                p->right = n->right;
                printf("1...");
                n->right = NULL;
                printf("2...");
                free(n);
                printf("3...");
                height++;

                printf("---end\n");
            }
        }
        if (((n->right->alpha > 64) && (n->right->alpha < 91)) || ((n->right->alpha > 96) && (n->right->alpha < 123)))
        {
            printf("go to right\n");
            roop++;
            printf("roop = %d\n", roop);
            makecleantree(n->right, n, height); // 오른쪽 자식 노드 재귀로 탐색 
        }
    }
    else
    {
        printf("under height = %d \t n->alpha = %c \t n->freq = %d\n",height , n->alpha, n->freq);
        return;
    }

}
void recursivedelete(Node* ptr) // 무조건 삭제
{
    if (ptr) {
        recursivedelete(ptr->left); // 왼쪽 자식노드 재귀로 탐색  
        free(ptr);
        recursivedelete(ptr->right); // 오른쪽 자식 노드 재귀로 탐색 
    }
}

int read_num(Node* h)
{
    Node* p = h->left; // 연산을 위해 노드 위치 탐색용

}

char decoding()
{

}

int encoding()
{

}

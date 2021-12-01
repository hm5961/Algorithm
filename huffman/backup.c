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
int read_num(Node* h, char* arr); 

char decoding();

void main()
{
    char* arr = malloc(sizeof(char) * 10000); // 인풋받는 영어문자열
    int* cnt = malloc(sizeof(int) * 26); // 알파벳 별 빈도 카운팅용


    for (int i = 0; i < 26; i++)
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
            alp[i] = i + 65; // 초기값 지정
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
            printf("alp[%d] : %c / cnt[%d] : %d / alp[%d] : %d\n", i, alp[i], i, cnt[i], i, alp[i]);
    }



    //printf("%d\n", ncnt);

    make_huffman_tree(&head); // 허프만트리 헤드노드 생성

    insert_node(head, cnt, alp, ncnt);
    printf("\n out to main \n");
    char* binen = malloc(sizeof(char) * 5);
    encoding(head->left, binen, 0, alp, ncnt);
    printf("encodingout\n");

    printf("into print bin\n");
    recursiveInorderbin(head->left);
    printf("printbin\n");



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
    (*h)->bin = '@';

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
        n[i] = (Node*)malloc(sizeof(Node));  // 가장 적은빈도 순으로 사용할 
    }
    for (i = 0; i < bincnt - 1; i++)
    {
        m[i] = (Node*)malloc(sizeof(Node)); // 리프노드 위에서 freq을 저장할 노드들
    }

    for (i = 0; i < ncnt; i++) // n[i] 초기화
    {
        
        n[i]->bin = alp[i];
        printf("n[%d]->bin = %c \t", i, n[i]->bin);
        n[i]->freq = cnt[i];
        n[i]->left = NULL;
        n[i]->right = NULL;
        printf("n[%d]->freq = %d\n", i, n[i]->freq);

    }

    for (i = 0; i < bincnt - 1; i++) // m[i] 초기화
    {
        m[i]->bin = 122 - i; //bincnt - 2 - i;
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
        else if (n[i]->freq)//if(n[i]->freq)
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

void makecleantree(Node* n, Node* p, int height) // 조건부 삭제
{
    if (n->left || n->right) {
        if (height > 0)//(((n->alpha > 64) && (n->alpha < 91)) || ((n->alpha > 96) && (n->alpha < 123))))
        { // n의 높이가 정상범위이며 n->alpha값이 영 대/소문자 범위일 경우
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


int read_num(Node* h, char* arr)
{
    for(int i = 0; i<)
    return 0;
}

char decoding()
{
    return 0;
}
//char bin= bin[5]
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
            printf("n->freq = %d\t", n->freq);
            printf("n->bin = % c\n", n->bin);
            for (int i = 0; i <ncnt;i++)
            {
                if (alp[i] == n->bin)
                {
                    printf("same \t");
                    printf("alp[i] = %c\n", alp[i]);

                    n->freq = alp[i];

                    //alp[i] = malloc(sizeof(char) * length);
                    n->bin = malloc(sizeof(char) * length);
                    binen[length] = '\0';

                    strcpy(n->bin, binen); 
                    //strcpy(alp[i], binen);
                }
            }
        }

        if (n->right)
        {
            binen[length] = '1';
            encoding(n->right, binen, length + 1, alp, ncnt);
        }

    }
}
void recursiveInorderbin(Node* ptr) //, char *alp, int ncnt)
{
    if (ptr) { // ptr의 자식노드로 재귀된 값이 노드의 형태 일 때 
        recursiveInorderbin(ptr->left); // alp, ncnt); // 왼쪽 자식노드 재귀로 탐색  
        if (!ptr->left && !ptr->right)
            printf("[%c = %s]", ptr->freq, ptr->bin); // 탐색된 값 출력 
        recursiveInorderbin(ptr->right);//, alp, ncnt); // 오른쪽 자식 노드 재귀로 탐색 
    }
}

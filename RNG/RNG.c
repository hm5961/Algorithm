<<<<<<< HEAD
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>
//#define MAX_COUNT	32000
//int main()
//{
//	FILE* p_file = fopen("33.txt", "wt");
//	int data[MAX_COUNT], i, sub_i;
//	srand((unsigned int)time(NULL));
//
//	if (p_file != NULL)
//	{
//		for (int i = 0; i < MAX_COUNT; i++)
//		{
//			data[i] = rand() % MAX_COUNT + 1;
//			for (sub_i = 0; sub_i < i; sub_i++)
//			{
//				if (data[i] == data[sub_i])
//				{
//					i--;
//					break;
//				}
//
//			}
//			printf("%d\n", i);
//		}	
//
//		for (i = 0; i < MAX_COUNT; i++)
//		{
//			printf("1");
//			fprintf(p_file, "%d ", data[i]);
//
//		}
//		fprintf(p_file, "%d ", -1);
//	}
//	return 0;
//}
=======
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX_COUNT	32000 //최대값 *32767 초과 금지
int main()
{
	FILE* p_file = fopen("33.txt", "wt"); // 작성 파일 명 사용 시 수정 필
	int data[MAX_COUNT], i, sub_i;
	srand((unsigned int)time(NULL));

	if (p_file != NULL)
	{
		for (int i = 0; i < MAX_COUNT; i++)
		{
			data[i] = rand() % MAX_COUNT + 1;
			for (sub_i = 0; sub_i < i; sub_i++)
			{
				if (data[i] == data[sub_i])
				{
					i--;
					break;
				}

			}
			printf("%d\n", i);
		}	

		for (i = 0; i < MAX_COUNT; i++)
		{
			printf("1");
			fprintf(p_file, "%d ", data[i]);

		}
		fprintf(p_file, "%d ", -1);
	}
	return 0;
}
>>>>>>> rng/main

#include<stdio.h>

typedef struct node { // 트리로 사용될 구조체 선언 
	
	int key;
	struct node *left;
	struct node *right;
};

int main(void)
{
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// 파일 읽기 성공
	while (true) {
		fscanf(pFile, "%d", &intTemp); //읽은값
		 
		if (intTemp < 0) 
			break; // -1일경우 루프 탈출 -> 다 읽음
		 
		 // 트리생성
		
		if ( )

		 // 생성된 트리에서 키 검색
		printf("%d ", intTemp);
	}
	
	//파일 형태로 반환

	fclose(pFile);          //close file
	return 0;
}

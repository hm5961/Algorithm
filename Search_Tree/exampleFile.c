#include<stdio.h>

typedef struct node { // Ʈ���� ���� ����ü ���� 
	
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

	// ���� �б� ����
	while (true) {
		fscanf(pFile, "%d", &intTemp); //������
		 
		if (intTemp < 0) 
			break; // -1�ϰ�� ���� Ż�� -> �� ����
		 
		 // Ʈ������
		
		if ( )

		 // ������ Ʈ������ Ű �˻�
		printf("%d ", intTemp);
	}
	
	//���� ���·� ��ȯ

	fclose(pFile);          //close file
	return 0;
}

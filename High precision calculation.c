#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//�ú��������ж����������������ֵ����Ϊ������1����Ϊ������0
int attributes(char str[])
{
	if (str[0] == '-')
		return 0;
	else
		return 1;
}

/*
 �ú������ڼ��������֮�ͣ����㷽���� "����ʽ����" ��ͬ������ʱ��˳��ֱ�����
 ��һ��������Ӧ�ĵ����������飬�ڶ���������Ӧ�ĵ����������飬��������������飬��Ҫ���м��������
 �����г��Ƚϴ���Ǹ�����ĳ���
*/
void add(int a[], int b[], int out[],int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		out[i]+= a[i] + b[i];
		out[i + 1]= out[i] / 10;
		out[i] = out[i] % 10;
	}
}

/*
 �ú������ڼ��������֮����㷽���� "����ʽ����" ��ͬ������ʱ��˳��ֱ�����
 ��һ��������Ӧ�ĵ����������飬�ڶ���������Ӧ�ĵ����������飬��������������飬��Ҫ���м��������
 �����г��Ƚϴ���Ǹ�����ĳ��ȣ�
 ע�⣺�ú����������ʱֻ�ܼ���"������С��"�� �Ⲣ��Ӱ����㣬���ǿ���ͨ�����㷨������"С��������"�����滻
*/
void reduce(int a[], int b[], int out[],int len)
{
	int i, t;
	for (i = 0; i < len; i++)
	{
	
		t=out[i]+ a[i] - b[i];
		if (t >= 0)
			out[i] = t;
		else
		{
			out[i] = 10+t;
			out[i + 1] = -1;
		}
	}
}


int main()
{
	while (1)
	{	
		//��ģ��Ϊ���û���ʾ�Ľ��棬�û�����0�˳���������1����ӷ�������2�������	
		int judge;
		printf("/***************�߾��ȼ���***************/\n");
		printf("\t\t����0�˳�\n\t\t����1����ӷ�\n\t\t����2�������\n");
		printf("�����룺");
		scanf("%d", &judge);
		getchar();
		//���˳�ʱ
		if (judge == 0)
			break;
		char str1[100], str2[100],s1[100],s2[100];	//�����ַ����飬��ȡ������ַ���
		int integer1[100], integer2[100];			//�����������飬���ڴ洢���������
		int result[101];							//������Ϊ���
		memset(result, 0, sizeof(result));			//�Խ����������
		printf("�������һ��������");
		gets(str1);								//�����һ������
		int attributes1 = attributes(str1);			//�жϵ�һ������������ֵ
		int len1 = strlen(str1);					//�����һ���ַ�������
		printf("������ڶ���������");
		gets(str2);								//����ڶ�������
		int attributes2 = attributes(str2);			//�жϵڶ�������������ֵ
		int len2 = strlen(str2);					//����ڶ����ַ�������
		memset(integer1, 0, sizeof(integer1));		//������integer1��������
		memset(integer2, 0, sizeof(integer2));		//������integer2��������
		int i, l1, l2;								//iΪѭ��������l1��l2Ϊ��Ӧ���޷��������ĳ���
		/*��������ѭ������Ϊ��1.ȥ�����ţ������ַ��������ָ�����Ӧ������������
							2.����ȥ�����ŵ������ַ���						*/
		if (attributes1 == 1)
		{
			for (i = 0; i < len1; i++)
				integer1[i] = str1[len1 - 1 - i] - '0';
			l1 = len1;
			strcpy(s1, str1);
		}
		else
		{
			for (i = 0; i < (len1 - 1); i++)
				integer1[i] = str1[len1 - 1 - i] - '0';
			l1 = len1 - 1;
			for (i = 0; i < (len1-1); i++)
				s1[i] = str1[i + 1];
			
		}

		if (attributes2 == 1)
		{
			for (i = 0; i < len2; i++)
				integer2[i] = str2[len2 - 1 - i] - '0';
			l2 = len2;
			strcpy(s1, str2);
		}
		else
		{
			for (i = 0; i < (len2 - 1); i++)
				integer2[i] = str2[len2 - 1 - i] - '0';
			l2 = len2 - 1;
			for (i = 0; i < (len2 - 1); i++)
				s2[i] = str2[i + 1];
		}
		int len = (l1 >= l2) ? l1 : l2;		//lenΪl1��l2�нϴ��һ��
		int flage = 1;						//flage����ָʾ���ŵ�������1��������0������
		if ((strlen(s1) < strlen(s2)) || (strcmp(s1, s2) < 0 && (strlen(s1) == strlen(s2))))
			flage = 0;

		//������ӷ�ʱ
		if (judge == 1)
		{
			if (attributes1 == 1 && attributes2 == 1)			//���������������ʱ
			{
				add(integer1, integer2, result, len);

			}
			else if (attributes1 == 1 && attributes2 == 0)		//���������Ӹ�����ʱ
			{
				if (flage == 1)
					reduce(integer1, integer2, result, len);
				else 
				{
					reduce(integer2, integer1, result, len);
					printf("-");
				}	
			}
			else if (attributes1 == 0 && attributes2 == 1)		//����������������ʱ
			{
				if (flage == 1)
				{
					reduce(integer1, integer2, result, len);
					printf("-");
				}
				else 
					reduce(integer2, integer1, result, len);
			}
			else if (attributes1 == 0 && attributes2 == 0)		//���������������ʱ
			{
				add(integer1, integer2, result, len);
				printf("-");
			}

		}
		//���������ʱ
		if (judge == 2)
		{
			if (attributes1 == 1 && attributes2 == 1)			//���������������ʱ
			{
				if(flage==1)
					reduce(integer1, integer2, result, len);
				else 
				{
					reduce(integer2, integer1, result, len);
					printf("-");
				}
			}
			else if (attributes1 == 1 && attributes2 == 0)		//����������������ʱ
			{
				add(integer1, integer2, result, len);
			}
			else if (attributes1 == 0 && attributes2 == 1)		//����������������ʱ
			{
				add(integer1, integer2, result, len);
				printf("-");
			}
			else if (attributes1 == 0 && attributes2 == 0)		//���������������ʱ
			{
				if (flage == 1)
				{
					reduce(integer1, integer2, result, len);
					printf("-");
				}
				else
					reduce(integer2, integer1, result, len);
			}

		}

		if (result[len] != 0)				//�ж��Ƿ��н�λ,�����д���
			len += 1;
		for (i = (len - 1); i >= 0; i--)	//ѭ��������
			printf("%d", result[i]);
		printf("\n\n\n");
		continue;							//�������㣬��ʼ��һ��ѭ��

	}
	
	return 0;

}

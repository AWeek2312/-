#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//该函数用于判断输入的整数的正负值，若为正返回1，若为负返回0
int attributes(char str[])
{
	if (str[0] == '-')
		return 0;
	else
		return 1;
}

/*
 该函数用于计算大整数之和，计算方法与 "列竖式计算" 相同；调用时按顺序分别输入
 第一个整数对应的倒叙纯数字数组，第二个整数对应的倒叙纯数字数组，保存计算结果的数组，需要进行计算的两个
 数组中长度较大的那个数组的长度
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
 该函数用于计算大整数之差，计算方法与 "列竖式计算" 相同；调用时按顺序分别输入
 第一个整数对应的倒叙纯数字数组，第二个整数对应的倒叙纯数字数组，保存计算结果的数组，需要进行计算的两个
 数组中长度较大的那个数组的长度；
 注意：该函数计算减法时只能计算"大数减小数"。 这并不影响计算，我们可以通过运算法则来对"小数减大数"进行替换
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
		//该模块为对用户显示的界面，用户输入0退出程序，输入1计算加法，输入2计算减法	
		int judge;
		printf("/***************高精度计算***************/\n");
		printf("\t\t输入0退出\n\t\t输入1计算加法\n\t\t输入2计算减法\n");
		printf("请输入：");
		scanf("%d", &judge);
		getchar();
		//当退出时
		if (judge == 0)
			break;
		char str1[100], str2[100],s1[100],s2[100];	//定义字符数组，读取输入的字符串
		int integer1[100], integer2[100];			//定义整数数组，用于存储输入的整数
		int result[101];							//该数组为结果
		memset(result, 0, sizeof(result));			//对结果数组清零
		printf("请输入第一个整数：");
		gets(str1);								//输入第一个整数
		int attributes1 = attributes(str1);			//判断第一个整数的正负值
		int len1 = strlen(str1);					//计算第一个字符串长度
		printf("请输入第二个整数：");
		gets(str2);								//输入第二个整数
		int attributes2 = attributes(str2);			//判断第二个整数的正负值
		int len2 = strlen(str2);					//计算第二个字符串长度
		memset(integer1, 0, sizeof(integer1));		//对数组integer1进行清零
		memset(integer2, 0, sizeof(integer2));		//对数组integer2进行清零
		int i, l1, l2;								//i为循环变量，l1、l2为相应的无符号整数的长度
		/*以下两个循环功能为：1.去掉符号，倒叙将字符串的数字赋到对应的整型数组中
							2.保存去掉符号的正序字符串						*/
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
		int len = (l1 >= l2) ? l1 : l2;		//len为l1和l2中较大的一个
		int flage = 1;						//flage用于指示符号的正负，1代表正，0代表负。
		if ((strlen(s1) < strlen(s2)) || (strcmp(s1, s2) < 0 && (strlen(s1) == strlen(s2))))
			flage = 0;

		//当计算加法时
		if (judge == 1)
		{
			if (attributes1 == 1 && attributes2 == 1)			//当两个正整数相加时
			{
				add(integer1, integer2, result, len);

			}
			else if (attributes1 == 1 && attributes2 == 0)		//当正整数加负整数时
			{
				if (flage == 1)
					reduce(integer1, integer2, result, len);
				else 
				{
					reduce(integer2, integer1, result, len);
					printf("-");
				}	
			}
			else if (attributes1 == 0 && attributes2 == 1)		//当负整数加正整数时
			{
				if (flage == 1)
				{
					reduce(integer1, integer2, result, len);
					printf("-");
				}
				else 
					reduce(integer2, integer1, result, len);
			}
			else if (attributes1 == 0 && attributes2 == 0)		//当两个负整数相加时
			{
				add(integer1, integer2, result, len);
				printf("-");
			}

		}
		//当计算减法时
		if (judge == 2)
		{
			if (attributes1 == 1 && attributes2 == 1)			//当两个正整数相减时
			{
				if(flage==1)
					reduce(integer1, integer2, result, len);
				else 
				{
					reduce(integer2, integer1, result, len);
					printf("-");
				}
			}
			else if (attributes1 == 1 && attributes2 == 0)		//当正整数减负整数时
			{
				add(integer1, integer2, result, len);
			}
			else if (attributes1 == 0 && attributes2 == 1)		//当负整数减正整数时
			{
				add(integer1, integer2, result, len);
				printf("-");
			}
			else if (attributes1 == 0 && attributes2 == 0)		//当两个负整数相减时
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

		if (result[len] != 0)				//判断是否有进位,并进行处理
			len += 1;
		for (i = (len - 1); i >= 0; i--)	//循环输出结果
			printf("%d", result[i]);
		printf("\n\n\n");
		continue;							//结束运算，开始下一次循环

	}
	
	return 0;

}

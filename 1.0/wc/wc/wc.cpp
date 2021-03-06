#include"stdafx.h"
#include <iostream>
#include"stdlib.h"
using namespace std;
void CharCount(char path[])
{
	FILE*fp = NULL;
	int c = 0, space = 0;
	char ch;
	char *path1 = path;
	int k = strlen(path);
	*(path1 + k) = '\0';
	//cout << path1 << endl;			//添加以对比路径，判断错误
	errno_t err = 0;
	if ((err = fopen_s(&fp, path1, "r")) != 0)
	{
		cout << "文件读取失败！" << endl;
		exit(0);						//读取失败则强行退出
	}
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == ' ')
		{
			space++;
		}
		c++;
		ch = fgetc(fp);
	}
	cout << "总字符为：" << c << endl;			//总字符包含空格、标点符号等
	cout << "总字数为：" << c - space << endl;		//总字数不包括空格
	fclose(fp);
}

void WordCount(char path[])
{
	FILE*fp;
	int W = 0;
	char word;
	char*p = path;
	cout << p << endl;
	int k = strlen(path);
	*(p + k) = '\0';
	errno_t err;
	if ((err = fopen_s(&fp, p, "r")) != 0)
	{
		cout << "文件读取失败！" << endl;
		exit(0);								//读取失败则强行退出
	}
	word = fgetc(fp);
	while (word != EOF)
	{
		if ((word >= 'a'&&word <= 'z') || (word >= 'A'&&word <= 'Z') || (word >= '0'&&word <= '9'))
		{
			while ((word >= 'a'&&word <= 'z') || (word >= 'A'&&word <= 'Z') || (word >= '0'&&word <= '9'))
			{
				word = fgetc(fp);
			}
			W++;
			word = fgetc(fp);
		}
		else
		{
			word = fgetc(fp);
		}
	}										//遇到英文字母与数字便获取下一字符，直到为非英文、非数字，词数加1
	cout << "总英文词数为：" << W << endl;
	fclose(fp);
}

void LineCount(char path[])
{
	FILE*fp;
	int L = 1;
	char ch;
	char*p = path;
	int k = strlen(path);
	*(p + k) = '\0';
	errno_t err;
	if ((err = fopen_s(&fp, p, "r")) != 0)
	{
		cout << "文件读取失败！" << endl;
		exit(0);
	}
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == '\n')
		{
			L++;
			ch = fgetc(fp);
		}
		else
		{
			ch = fgetc(fp);
		}
	}
	cout << "行数为：" << L << endl;
	fclose(fp);
}

void Multiple(char path[])
{
	FILE*fp = NULL;
	char ch;
	char*path4 = path;
	int k = strlen(path);
	*(path4 + k) = '\0';
	int c = 0, e = 0, n = 0;
	errno_t err;
	if ((err = fopen_s(&fp, path4, "r")) != 0)
	{
		cout << "文件读取失败！" << endl;
		exit(0);
	}
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == '{' || ch == '}')
		{
			e++;
			ch = fgetc(fp);
		}
		else if (ch == '\n' || ch == ' ')
		{
			ch = fgetc(fp);
			if (ch == ' ')
			{
				ch = fgetc(fp);
			}
			while (ch == '\n')
			{
				e++;
				ch = fgetc(fp);
			}
		}
		else if (ch == '/')
		{
			ch = fgetc(fp);
			if (ch == '/')
			{
				while (ch != '\n')
				{
					ch = fgetc(fp);
				}
			}
			n++;
		}
		else
		{
			c++;
			while (ch != '{'&&ch != '}'&&ch != '\n'&&ch != '/'&&ch != EOF)
			{
				ch = fgetc(fp);
			}
		}
	}
	cout << "代码行数为：" << c << endl;
	cout << "空行数为：" << e << endl;
	cout << "注释行数为：" << n << endl;
	fclose(fp);
}
int main()
{
	char input[100], path[50];
	gets_s(input);
	int x = strlen(input);
	strncpy_s(path, input + 18, x - 18);
	path[x - 17] = '\0';
	while (1)
	{
		{
			int i = 15;
			if ((input[i] == '-') && (input[i + 1] == 'c'))
			{
				CharCount(path);
				break;
			}
			if ((input[i] == '-') && (input[i + 1] == 'w'))
			{
				WordCount(path);
				break;
			}
			if ((input[i] == '-') && (input[i + 1] == 'l'))
			{
				LineCount(path);
				break;
			}
			if ((input[i] == '-') && (input[i + 1] == 'm'))
			{
				Multiple(path);
				break;
			}
			else
			{
				cout << "输入格式错误" << endl;
				break;
			}
		}
	}
	system("pause");
	return 0;
}


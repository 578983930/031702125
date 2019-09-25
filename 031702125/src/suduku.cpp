#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable:4996)
using namespace std;
int num, siz, len, wid, a[100][100], b[10][100][100];
bool jugde(int x, int y, int i) //判断是否唯一
{
	int l, w;
	for (l = 0; l < siz; l++) //行判断 
	{
		if (l != y && a[x][l] == i)
			return false;
	}
	for (w = 0; w < siz; w++)//列判断 
	{
		if (w != x && a[w][y] == i)
			return false;
	}
	if (len != siz)//宫判断 
	{
		for (l = (x / len)*len; l < (x / len)*len + len; l++)
		{
			for (w = (y / wid)*wid; w < (y / wid)*wid + wid; w++)
			{
				if (a[l][w] == i)
				{
					if (l == x && w == y)
						continue;
					else
						return false;
				}
			}
		}
	}
	return true;
}

bool DSF(int dsf) //利用递归解出数独 
{
	int i, x, y;
	if (dsf >= siz * siz)
		return true;
	x = dsf / siz;
	y = dsf % siz;
	if (a[x][y] != 0)
		return DSF(dsf + 1);
	else
	{
		for (i = 1; i <= siz; i++)
		{
			if (jugde(x, y, i))
			{
				a[x][y] = i;
				if (DSF(dsf + 1))
					return true;
			}
			a[x][y] = 0;
		}
	}
	return false;
}
int main(int argc, char *argv[])
{
	int i, j , k;
	siz = atoi(argv[2]);
	num = atoi(argv[4]);
	if (siz % 3 == 0)
		len = siz / 3, wid = siz / len;
	else if (siz % 2 == 0)
		len = siz / 2, wid = siz / len;
	else
		len = siz;
	wid = siz;
	FILE* afile;
	afile = fopen("input.txt", "r");
	if (afile == NULL)
	{
		cout << "请输入正确的文件名！" << endl;
		return 0;
	}
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < siz; j++)
			for (k = 0; k < siz; k++)
				fscanf(afile, "%d", &a[j][k]);
		DSF(0);
		for (j = 0; j < siz; j++)
			for (k = 0; k < siz; k++)
				b[i][j][k] = a[j][k];
	}
	fclose(afile);
	afile = fopen("output.txt", "w");
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < siz; j++)
		{
			for (k = 0; k < siz; k++)
			{
				fprintf(afile, "%d", b[i][j][k]);
				if (k != siz - 1)
					fprintf(afile, " ");
			}
			if (j != siz - 1)
				fprintf(afile, "\n");
		}
		if (i != num - 1)
			fprintf(afile, "\n\n");

	}
	fclose(afile);
	return 0;
}

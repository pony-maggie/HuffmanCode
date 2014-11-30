// HuffmanCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;

typedef char **HuffmanCode;

const int MAX = 0xFFFF;

//从HT[1...nEnd]中选出parent为0, 并且weight最小的两个结点，序号分别由s1 和 s2返回
static bool Select(HuffmanTree HT, int nEnd, int *s1, int *s2)
{
	int i = 0;
	int nComp = 0;
	
	nComp = MAX;
	*s1 = MAX;
	*s2 = MAX;

	//第一轮循环，找到最小的给s1
	for (i = 1; i <= nEnd; i++)
	{
		if ((HT[i].weight < nComp) && (HT[i].parent == 0))
		{
			nComp = HT[i].weight;
			*s1 = i;
		}
			
	}

	//第二轮循环，找到次小的给s2
	nComp = MAX;

	for (i = 1; i <= nEnd; i++)
	{
		if ((HT[i].weight < nComp) && (i != *s1) && (HT[i].parent == 0))
		{
			nComp = HT[i].weight;
			*s2 = i;
		}
			
	}
	if ((*s1 == MAX) || (*s2 == MAX))
	{
		return false;
	}
	return true;
}

bool HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n)
{
	HuffmanTree p;
	int i = 0;
	int s1 = 0;
	int s2 = 0;
	char *cd = NULL;

	if (n < 1) return false;

	int m = 2 * n - 1;
	*HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));//多分配一个空间，0号不用
	for (p = (*HT)+1, i = 1; i <= n; i++, p++, w++)
	{
		//初始化n个叶子结点
		*p = { *w, 0, 0, 0};
	}
	for (; i <= m; i++, p++)
	{
		//初始化其它结点
		*p = { 0, 0, 0, 0 };
	}
	//构建赫夫曼树
	for (i = n + 1; i <= m; i++)
	{
		if (!Select(*HT, i - 1, &s1, &s2)) return false;
		(*HT)[s1].parent = i;
		(*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}

	//开始求每个字符的编码
	*HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));//输出结果用
	cd = (char *)malloc(n*sizeof(char));
	cd[n - 1] = '\0';

	int c, f;
	int start = 0;
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)
		{
			//左0右1
			if ((*HT)[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		(*HC)[i] = (char *)malloc((n - start));
		strcpy((*HC)[i], &cd[start]);
	}



	free(cd);
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HuffmanTree pTree;
	HuffmanCode codeResult;
	static const int N = 4;
	int i = 0;

	//分别代表A,B,C,D四个字符出现的次数, 求这四个字符的赫夫曼编码
	int wArray[N] = { 3, 1, 2, 1 };
	char string[] = " ABCD";

	if (!HuffmanCoding(&pTree, &codeResult, wArray, N))
	{
		printf("Err!\n");
		return 0;
	}
		
	for (i = 1; i <= N; i++)
	{
		printf("%c,code:", string[i]);
		printf("%s\n", codeResult[i]);
	}
	free(pTree);
	free(codeResult);

	return 0;
}


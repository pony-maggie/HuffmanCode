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

//��HT[1...nEnd]��ѡ��parentΪ0, ����weight��С��������㣬��ŷֱ���s1 �� s2����
static bool Select(HuffmanTree HT, int nEnd, int *s1, int *s2)
{
	int i = 0;
	int nComp = 0;
	
	nComp = MAX;
	*s1 = MAX;
	*s2 = MAX;

	//��һ��ѭ�����ҵ���С�ĸ�s1
	for (i = 1; i <= nEnd; i++)
	{
		if ((HT[i].weight < nComp) && (HT[i].parent == 0))
		{
			nComp = HT[i].weight;
			*s1 = i;
		}
			
	}

	//�ڶ���ѭ�����ҵ���С�ĸ�s2
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
	*HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));//�����һ���ռ䣬0�Ų���
	for (p = (*HT)+1, i = 1; i <= n; i++, p++, w++)
	{
		//��ʼ��n��Ҷ�ӽ��
		*p = { *w, 0, 0, 0};
	}
	for (; i <= m; i++, p++)
	{
		//��ʼ���������
		*p = { 0, 0, 0, 0 };
	}
	//�����շ�����
	for (i = n + 1; i <= m; i++)
	{
		if (!Select(*HT, i - 1, &s1, &s2)) return false;
		(*HT)[s1].parent = i;
		(*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}

	//��ʼ��ÿ���ַ��ı���
	*HC = (HuffmanCode)malloc((n + 1)*sizeof(char *));//��������
	cd = (char *)malloc(n*sizeof(char));
	cd[n - 1] = '\0';

	int c, f;
	int start = 0;
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)
		{
			//��0��1
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

	//�ֱ����A,B,C,D�ĸ��ַ����ֵĴ���, �����ĸ��ַ��ĺշ�������
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


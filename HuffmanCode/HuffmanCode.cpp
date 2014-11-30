// HuffmanCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int a = 0;
	char *b = NULL;
	/////////////////////////////////////////
	if (a < 60) b = "不及格";
	else if (a < 70) b = "及格";
	else if (a < 80) b = "中等";
	else if (a < 90) b = "良好";
	else b = "优秀";
	/////////////////////////////////////////
	if (a >= 70 && a < 80) b = "中等";
	else if (a >= 80 && a < 90) b = "良好";
	else if (a >= 60 && a < 70) b = "及格";
	else if (a < 60) b = "不及格";
	else b = "优秀";






	return 0;
}


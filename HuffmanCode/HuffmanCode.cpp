// HuffmanCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int a = 0;
	char *b = NULL;
	/////////////////////////////////////////
	if (a < 60) b = "������";
	else if (a < 70) b = "����";
	else if (a < 80) b = "�е�";
	else if (a < 90) b = "����";
	else b = "����";
	/////////////////////////////////////////
	if (a >= 70 && a < 80) b = "�е�";
	else if (a >= 80 && a < 90) b = "����";
	else if (a >= 60 && a < 70) b = "����";
	else if (a < 60) b = "������";
	else b = "����";






	return 0;
}


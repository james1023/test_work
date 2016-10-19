// interview_cpp.cpp : 定義主控台應用程式的進入點。
//

#include "stdio.h"
#include "stdlib.h"
//#include <iostream>
//#include <iomanip>
//using namespace std;

void test_subptr()
{
	int a[] = { 3, 6, 9 };
	int *p = a;
	//int *q = p + 1;
	int *q = &p[1];

	//cout << "q-p=" << q-p << endl;
	//cout << "(int)q-(int)p=" << (int)q - (int)p << endl;
	printf("q-p=%d. \n", q - p);
	printf("(int)q-(int)p=%d. \n", (int)q - (int)p);

	if (q == p + 1) {
		//cout << "q==p+1" << endl;
		printf("q==p+1. \n");
	}
}

int main()
{
	test_subptr();

	system("PAUSE");

    return 0;
}



#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <iomanip>
using namespace std;

void test_subptr()
{
	int a[] = { 3, 6, 9 };
	int *p = a;
	int *q = p + 1; //=> int *q = &p[1];

	cout << "q-p=" << q - p << endl;
	cout << "(int)q-(int)p=" << ((int)q) - ((int)p) << endl;

	if (q == p + 1) {
		cout << "q==p+1" << endl;
	}

	cout << endl;

	char a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	char *p1 = a1;
	char *q1 = p1 + 8;
	//int *q = &p[1];

	cout << "q1-p1=" << q1 - p1 << endl;
	cout << "(int)q1-(int)p1=" << ((int)q1) - ((int)p1) << endl;
	cout << "(int *)q1-(int *)p1=" << ((int *)q1) - ((int *)p1) << endl;
}

int main()
{
	test_subptr();

#if defined(WIN32)
	system("PAUSE");
#endif

	return 0;
}


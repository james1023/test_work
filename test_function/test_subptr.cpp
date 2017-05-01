
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

	cout << "q-p=" << q - p << endl; // q-p=1
	cout << "(int)q-(int)p=" << (int)q - (int)p << endl; // (int)q-(int)p=4

	if (q == p + 1) {
		cout << "q==p+1" << endl; // q==p+1
	}

	cout << endl;

	char a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	char *p1 = a1;
	char *q1 = p1 + 8;
	//int *q = &p[1];

	cout << "q1-p1=" << q1 - p1 << endl; // q1-p1=8
	cout << "(int)q1-(int)p1=" << (int)q1 - (int)p1 << endl; // (int)q1-(int)p1=8
	cout << "(int *)q1-(int *)p1=" << (int *)q1 - (int *)p1 << endl; // (int *)q1-(int *)p1=2
}

class base {
public:
	int a;
	base() :a(0)
	{}
	int getA() { return a; }
};

class der :public base
{
public:
	int b;
	der() :b(1)
	{}
	int getB() { return b; }
};

void display(base *obj, int ele)
{
	for (int i = 0; i < ele; i++)
	{
		cout << (obj + i)->getA() << endl;
	}
}

void test_der_display()
{
	//int i = 3;
	base arrb[3];
	display(arrb, 3); // 0 0 0
	der arrd[3];
	display(arrd, 3); //? 0 1 0
	return;
}

int main()
{
	test_subptr();

	test_der_display();


	//system("PAUSE");
	std::cin.get();


	return 0;
}


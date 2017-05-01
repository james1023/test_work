
#include "stdio.h"
#include "stdlib.h"

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <bitset>

#include <gtest/gtest.h>

using namespace std;

char *itobs(int n, char *ps) 
{
	int size = 8 * sizeof(n);
	int i = size - 1;
	
	while (i + 1) {
		ps[i--] = (1 & n) + '0';
		n >>= 1;
	}

	ps[size] = '\0';
	
	return ps;
}

TEST(itobs, test1)
{
	int n = 8;
	char s[8 * sizeof(n) + 1];
	cout << n << "=" << itobs(n, s) << endl;
}

TEST(itobs, test2)	
{
	int n = 8;
	bitset<sizeof(n)*8> s(n);

	cout << n << "=" << s << endl;
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cin.get();

	return 0;
}


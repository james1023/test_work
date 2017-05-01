
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

/*
1. bit sequence
給你一個8-bit的整數數列，要你找出這串數列的連續最長的1bit的長度和他的起始位置
(ps. 255=11111111就是8個連續的1bit, 119=01110111有兩組連續3個1bit)
*/
int max_onebits(int N)
{
	int ones = 0;
	int max_gap = 0;

	while (N > 0) {
		if ((N & 1) == 1) {
			ones++;
			if (max_gap < ones) {
				max_gap = ones;
			}
		}
		else {
			ones = 0;
		}

		N = N >> 1;
	}

	return max_gap;
}

TEST(max_onebits, test1)
{
	std::cout << "9=>" << max_onebits(9) << std::endl;
	EXPECT_EQ(1, max_onebits(9));
	
	std::cout << "255=>" << max_onebits(255) << std::endl;
	EXPECT_EQ(8, max_onebits(255));

	std::cout << "119=>" << max_onebits(119) << std::endl;
	EXPECT_EQ(3, max_onebits(119));
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cin.get();

	return 0;
}


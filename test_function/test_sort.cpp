
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



TEST(sort, test1)
{
	std::vector<int> in{ -1, 6, 8, 90, -6, 4, 6, -345, 7, 7 };

	sort(in.begin(), in.end());
}

struct greater
{
	template<class T>
	bool operator()(T const &a, T const &b) const { return a > b; }
};
TEST(sort, test2)
{
	std::vector<int> in{ -1, 6, 8, 90, -6, 4, 6, -345, 7, 7 };

	std::sort(in.begin(), in.end(), greater());
}

// ---

bool comp(int i, int j) { return i > j; }
TEST(sort, test3)
{
	std::vector<int> in{ -1, 6, 8, 90, -6, 4, 6, -345, 7, 7 };

	std::sort(in.begin(), in.end(), comp);
}

// ---
// 給定一個正整數數列進行排列，使其奇數在前，偶數在後。奇數部份由小到大排列，偶數部份由大到小排列。
// 

bool isOdd(int x) {
	return ((x & 1) == 1);
}
TEST(sort, test4)	
{
	// int tab[]={1,2,3,4,5,6,7,8,9,10}; 
	// vector<int> in(tab, tab + sizeof(tab) / sizeof(tab[0]));
	//
	std::vector<int> in{ 7, 6, 10, 9, 8, 2, 1, 5, 4, 3 };

	auto bound = std::partition(in.begin(), in.end(), isOdd);
	std::sort(in.begin(), bound);
	std::sort(bound, in.end(), comp);
}

// -

bool sort_even_odd(const int& left, const int& right)
{
	if (left & 1 && right & 1) // both are odd
	{
		return left > right;
	}
	else if (left & 1) // left is odd
	{
		return false;
	}
	else if (right & 1) // right is odd
	{
		return true;
	}

	// both are even
	return left < right;
}

bool sort_odd_even(const int& left, const int& right)
{
	if (left & 1 && right & 1)
	{
		return left < right;
	}
	else if (left & 1) // left is odd
	{
		return true;
	}
	else if (right & 1) // right is odd
	{
		return false;
	}

	// both are even
	return left > right;
}

TEST(sort, test5)
{
	std::vector<int> in{ 7, 6, 10, 9, 8, 2, 1, 5, 4, 3 };

	std::sort(in.begin(), in.end(), sort_odd_even);
}

// ---

class myclass {
public:
	myclass(int a, int b) :first(a), second(b) {}
	int first;
	int second;
	bool operator < (const myclass &m)const {
		return first < m.first;
	}
};

bool less_second(const myclass &m1, const myclass &m2) {
	return m1.second < m2.second;
}

TEST(sort, test6) 
{
	vector< myclass > vect;
	for (int i = 0; i < 10; i++) {
		myclass my(10 - i, i * 3);
		vect.push_back(my);
	}
	for (int i = 0; i < vect.size(); i++)
		cout << "(" << vect[i].first << "," << vect[i].second << ")\n";

	cout << "after sorted by first:" << endl;
	sort(vect.begin(), vect.end());
	for (int i = 0; i < vect.size(); i++)
		cout << "(" << vect[i].first << "," << vect[i].second << ")\n";

	cout << "after sorted by second:" << endl;
	sort(vect.begin(), vect.end(), less_second);
	for (int i = 0; i < vect.size(); i++)
		cout << "(" << vect[i].first << "," << vect[i].second << ")\n";
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cin.get();

	return 0;
}


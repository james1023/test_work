
#include "stdio.h"
#include "stdlib.h"

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <gtest/gtest.h>

using namespace std;

/*
a) int a; // An integer
b) int *a; // A pointer to an integer
c) int **a; // A pointer to a pointer to an integer
d) int a[10]; // An array of 10 integers
e) int *a[10]; // An array of 10 pointers to integers
f) int (*a)[10]; // A pointer to an array of 10 integers
g) int (*a)(int); // A pointer to a function a that takes an integer argument
// and returns an integer
h) int (*a[10])(int); // An array of 10 pointers to functions that take
// an integer argument and return an integer
*/

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	/*
	*a ^= *b;
    *b ^= *a;
    *a ^= *b;
	*/
}

TEST(swap, test1)
{
	int a = 123;
	int b = 321;
	swap(&a, &b);
}

int fib1(int n) 
{
	if (n == 0)
		return 0;

	if (n == 1)
		return 1;

	return (fib1(n - 1) + fib1(n - 2));
}

unsigned long fib2(int n)
{
	unsigned long tmp, fn_2, fn_1;
	int i;
	if (n <= 2)
		return 1;
	else
		for (fn_2 = fn_1 = 1, i = 3; i <= n; i++)
		{
			tmp = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = tmp;
		}
	return tmp;
}

TEST(fib1, test1)
{
	EXPECT_EQ(21, fib1(8));
}

TEST(fib2, test1)
{
	EXPECT_EQ(21, fib2(8));
}

typedef enum _ENDIAN_TYPE
{
	ENDIAN_BIG,
	ENDIAN_LITTLE,
} ENDIAN_TYPE;

ENDIAN_TYPE get_endian()
{
	unsigned int i = 1;
	char *c = (char *)&i;

	if (*c) {
		return ENDIAN_LITTLE;
	}
	else {
		return ENDIAN_BIG;
	}
}

// htonl 不一定具有可攜性
/*ENDIAN_TYPE get_endian_1()
{
	int a = 0x12345678;
	int b = htonl(a);
	if (b == a)
		return ENDIAN_BIG;
	else
		return ENDIAN_LITTLE;
	
}*/

inline void endian_swap_16(unsigned short& x)
{
	x = (x >> 8) |
		(x << 8);
}

inline void endian_swap_32(unsigned int& x)
{
	x = (x >> 24) |
		((x << 8) & 0x00FF0000) |
		((x >> 8) & 0x0000FF00) |
		(x << 24);
}

// __int64 for MSVC, "long long" for gcc
inline void endian_swap_64(unsigned __int64& x)
{
	x = (x >> 56) |
		((x << 40) & 0x00FF000000000000) |
		((x << 24) & 0x0000FF0000000000) |
		((x << 8) & 0x000000FF00000000) |
		((x >> 8) & 0x00000000FF000000) |
		((x >> 24) & 0x0000000000FF0000) |
		((x >> 40) & 0x000000000000FF00) |
		(x << 56);
}

void show_big_little()
{
	unsigned int n = 0x00010203;
	unsigned char *c;
	printf("n = %d\n", n);
	c = (unsigned char*)&n;
	printf("n is allocated at\n%11u\t%11u\t%11u\t%11u\n", c, c + 1, c + 2, c + 3);
	printf("%11u\t", *c);
	printf("%11u\t", *(c+1));
	printf("%11u\t", *(c+2));
	printf("%11u\n", *(c+3));

	// ---

	unsigned int temp = 0;

	temp = *(c); temp <<= 8;
	temp |= *(c + 1); temp <<= 8;
	temp |= *(c + 2); temp <<= 8;
	temp |= *(c + 3);
	c = (unsigned char *)&temp;

	// or
	/*endian_swap_32(n);
	temp = n;*/

	unsigned short size = 0;
	size |= *(c + 2);
	size <<= 8;
	size |= *(c + 3);
}

void show_bit_little_float()
{
	char *a;
	float f = 3.14159;  // number to start with

	a = (char *)&f;   // point a to f's location

					  // print float & byte array as hex
	printf("float: %f\n", f);
	printf("byte array: %hhX:%hhX:%hhX:%hhX\n", \
		a[0], a[1], a[2], a[3]);

	// toggle the sign of f -- using the byte array
	a[3] = ((unsigned int)a[3]) ^ 128;

	//print the numbers again
	printf("float: %f\n", f);
	printf("byte array: %hhX:%hhX:%hhX:%hhX\n", \
		a[0], a[1], a[2], a[3]);
}

void test_endian()
{
	//Run the follow code on 32bit little - endian PC.What is the final result ?
	char hello[] = "hello";
	int data[] = { 348, 152, 65538, NULL, 32, 222 }; 
	// 5c 01 00 00 98 00 00 00 02 00 01 00 00 00 00 00 20 00 00 00 de 00 00 00
	void *p1 = data - 1;
	int n = sizeof(hello);
	short *p2 = (short *)p1 + n; // n=6, p1+n*sizeof(short)
	int *p3 = (int *)((char *)p2 + (char)*p2);
	//printf("%d", *p3);
	std::cout << "*p3 = " << *p3 << std::endl; // *p3=1
}

void smooth(const unsigned char *src, unsigned char *dst, int width, int height)
{
	const int mask_w = 3, mask_h = 3;
	int templates[mask_w*mask_h] = {
		1, 1, 1, 
		1, 2, 1,
		1, 1, 1
	};

	for (int i = 0; i < height; i+=mask_w) {
		for (int j = 0; j < width; j+= mask_h) {
			int sum = 0;
			int index = 0;
			for (int m = i; m < i+mask_w; m++)	{
				for (int n = j; n < j+mask_h; n++) {
					sum += src[m*width + n] * templates[index++];
				}
			}
			sum /= (mask_w*mask_h);
			if (sum > 255) sum = 255;

			for (int m = i; m < i+mask_w; m++) {
				for (int n = j; n < j+mask_h; n++) {
					dst[m*width + n] = sum;
				}
			}
		}
	}
}

TEST(smooth, test1)
{
	unsigned char src[] = {
		4, 4, 4,
		4, 2, 4, 
		4, 4, 4
	};

	unsigned char dst[9];

	smooth(src, dst, 3, 3);
}

TEST(smooth, test2)
{
	unsigned char src[] = {
		4, 4, 4, 2, 2, 2,
		4, 2, 4, 2, 1, 2,
		4, 4, 4, 2, 2, 2
	};

	unsigned char dst[64];

	smooth(src, dst, 6, 3);
}

TEST(smooth, test3)
{
	unsigned char src[] = {
		4, 4, 4, 2, 2, 2,
		4, 2, 4, 2, 1, 2,
		4, 4, 4, 2, 2, 2,
		5, 6, 7, 7, 8, 9,
		5, 3, 7, 7, 4, 9,
		5, 6, 7, 7, 8, 9
	};

	unsigned char dst[64];

	smooth(src, dst, 6, 6);
}

int reverse(int src, int result)
{
	int reverse = 0;

	while (src != 0)
	{
		reverse = reverse * 10;
		reverse = reverse + src % 10;
		src = src / 10;
	}

	return reverse;
}

TEST(reverse, test1)
{
	EXPECT_EQ(54321, reverse(12345, 0));
}


int main(int argc, char *argv[])
{
	show_big_little();
	show_bit_little_float();
	test_endian();
	ENDIAN_TYPE endian = get_endian();

	

	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	std::cin.get();

	return 0;
}


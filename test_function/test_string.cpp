
#include "stdio.h"
#include "stdlib.h"

#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

void test_ntos()
{
	std::stringstream ss;
	std::string s;

	short num = 127;

	ss.str(""); ss << num;
	std::cout << ss.str() << std::endl;

	ss.str(""); ss << std::hex << num;
	std::cout << "std::hex: " << ss.str() << std::endl;

	ss.str(""); ss << std::oct << num;
	std::cout << "std::oct: " << ss.str() << std::endl;

	ss.str(""); ss << std::oct << std::setw(4) << std::setfill('0') << 63;
	std::cout << "std::oct+std::setw(4)+std::setfill('0'): " << ss.str() << std::endl;

	double real = 123.78999;
	ss.str(""); ss << std::setprecision(3) << std::fixed << real;
	std::cout << "std::setprecision(3)+std::fixed: " << ss.str() << std::endl;

	num = 127;
	s = boost::lexical_cast<std::string>(num);
	std::cout << "boost::lexical_cast<std::string>: " << s << std::endl;

	num = 127;
	ss.str(""); ss << boost::format("%02X")%(num);
	std::cout << "boost::format(\"%02X\"): " << ss.str() << std::endl;
}

void test_ston()
{
	std::string s;
	int num;
	double real;

	s = "800";
	std::string::size_type sz;
	num = std::stoi(s, &sz);
	std::cout << "stoi: " << num << std::endl;

	num = atoi(s.c_str());
	std::cout << "atoi: " << num << std::endl;

	s = "FFFF";
	num = std::stoul(s, nullptr, 32);
	std::cout << "stoul: "<< num << std::endl;

	s = "123.123";
	real = atof(s.c_str());
	std::cout << "atof: " << real << std::endl;

	s = "800";
	num = boost::lexical_cast<int>(s);
	std::cout << "boost::lexical_cast: " << num << std::endl;
}

int main()
{
	test_ntos();

	test_ston();

	std::cin.get();

	return 0;
}


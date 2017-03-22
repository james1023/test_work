//============================================================================
// Name        : test_c_makefile.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <set>
#include <vector>
#include <exception>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include <test_boost_lib.h>

using namespace std;

int main(void) {
	struct _def_account
	{
		string username;
		string password;
	};

	struct _model_def_account
	{
		struct def_account;
	    string model_name;
	};

	struct _model_def_account model_def_account;
	string s1;

	boost::property_tree::ptree head_tree, model_child;
	boost::property_tree::xml_parser::read_xml("/Users/Alan/Dropbox/work/test/test_boost_xml/src/model_def_account.xml", head_tree);
	model_child = head_tree.get_child("model");

	//string s1 = head_tree.get<string>("model.default_account.username");

	for (boost::property_tree::ptree::iterator itr=model_child.begin(); itr!=model_child.end(); itr++) {
		boost::property_tree::ptree account = itr->second;

		s1 = account.get<string>("username");
		std::cout << "1=" << s1;
		s1 = account.get<string>("password");
		std::cout << ", 2=" << s1;
		s1 = account.get<string>("list_name");
		std::cout << ", 3=" << s1 << "\n";

	}
    
    ///////////
    


	return EXIT_SUCCESS;
}

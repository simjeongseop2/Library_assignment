#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <iostream>
#include <vector>
#include <string>
#include "date.h"
using namespace std;

class resource {
public:
	string type; //book, magazine, e_book
	string name;
	bool isborrowed;
	string user;
	date return_date;
	resource();
	resource(string type, string name);
};

class book : public resource {
public:
	book() {}
	book(string name);
};

class magazine : public resource {
public:
	date public_date;
	magazine() {}
	magazine(string name);
};

class e_book : public resource {
public:
	e_book() {}
	e_book(string name);
};

#endif

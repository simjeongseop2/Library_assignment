#ifndef __MEMBER_H__
#define __MEMBER_H__
#include <vector>
#include <string>
#include "date.h"
using namespace std;

class member {
public:
	string type; //undergraduate, graduate, faculty
	string name;
	int max_num; // max able num
	int max_lent; // max day of lent
	vector<string> book_name;
	vector<date> lent_date;
	date disable; //available date
	int max_capacity;
	int now_capacity;
	member();
	member(string type, string name, int max_num, int max_lent);
	bool is_able(date today);
};

class undergraduate : public member {
public:
	undergraduate() {}
	undergraduate(string name);
};

class graduate : public member {
public:
	graduate() {}
	graduate(string name);
};

class faculty : public member {
public:
	faculty() {}
	faculty(string name);
}; 

#endif
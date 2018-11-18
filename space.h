#ifndef __SPACE_H__
#define __SPACE_H__
#include <vector>
#include <string>
#include "date.h"
using namespace std;

class space {
public:
	int max_num, max_time, num, empty_num; //num = present num, emptynum = present empty num
	int open_time, close_time;
	struct user_info {
		user_info() {}
		user_info(string name, int num, date dat, int borrow_time) : name(name), num(num) {
			dat.t += borrow_time;
			end = dat;
			isEmpty = false;
		}
		string name;
		int num;
		date end;
		bool isEmpty;
		int empty_time;
	};
	virtual void update(date d) = 0;
	virtual int return_available_time(int t, int n) = 0;
	vector<user_info> user;
	space(int mn, int mt, int ot, int ct);
	bool isThereUser(string name);
	void borrow_space(string name, int n, date dat, int borrow_time);
	void return_space(string name);
	void empty_space(string name, date dat);
	void comback_space(string name);
};

class study_room : public space {
public:
	study_room();
	void update(date d);
	int return_available_time(int t, int n);
};

class seat : public space {
public:
	seat(int ot, int ct);
	void update(date d);
	int return_available_time(int t, int n);
};

#endif
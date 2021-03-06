#include "member.h"

member::member() { disable.y = -1; book_name.resize(0); lent_date.resize(0); }

member::member(string type, string name, int max_num, int max_lent) 
	: type(type), name(name), max_num(max_num), max_lent(max_lent) {
		disable.y = -1; book_name.resize(0); lent_date.resize(0); now_capacity = 0;
}

bool member::is_able(date today) {
	if(disable.y > today.y)
		return false;
	else if(disable.y == today.y) {
		if(disable.m > today.m)
			return false;
		else if(disable.m == today.m && disable.d >= today.d)
			return false;
	}
	return true;
}

undergraduate::undergraduate(string name) : member("Undergraduate", name, 1, 14) { max_capacity = 100; }
graduate::graduate(string name) : member("Graduate", name, 5, 30) { max_capacity = 500; }
faculty::faculty(string name) : member("Faculty", name, 10, 30) { max_capacity = 1000; }
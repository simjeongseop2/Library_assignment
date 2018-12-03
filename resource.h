#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <iostream>
#include	 <cstdio>
#include <vector>
#include <string>
#include "date.h"
#include "member.h"
using namespace std;

class resource {
public:
	int capacity;
	string type; //book, magazine, e_book
	string name;
	bool isborrowed;
	string user;
	date return_date;
	resource();
	resource(string type, string name);
	date date_plus(date today, int p) {
	today.d += p;
	while(today.d > 30) {
		today.m++;
		today.d -= 30;
	}
	while(today.m > 12) {
		today.y++;
		today.m -= 12;
	}
	return today;
}
	virtual bool isSame(string rsc_name, date now, date m_date) {
		if(name == rsc_name)
			return true;
		return false;
	}
	virtual bool already_borrow(member* m, date m_date) {
		return true;
	}
	virtual bool return_isborrowed(date m_date) {
		if(isborrowed == true)
			return true;
		return false;
	}
	virtual void borrow_rsc(member* m, date now, date m_date, string origin_name) {
		m->book_name.push_back(name); //borrow_rsc!!
		m->lent_date.push_back(now);
		isborrowed = true;	
		user = m->name;
		return_date = date_plus(now, m->max_lent - 1);
	}
	virtual void update(date now) {
		return;
	}
	virtual bool matching_user(member* m, date m_date, string origin_name) {
		for(int i = 0; i < m->book_name.size(); i++) {
			if(name == m->book_name[i]) {
				return true;
			}
		}
		return false;
	}
	virtual void return_rsc(member* m, date now, date m_date, string origin_rsc_name, string rsc_name, int bidx) {
		m->book_name.erase(m->book_name.begin() + bidx);
		m->lent_date.erase(m->lent_date.begin() + bidx);
		isborrowed = false;
		user = "NULL";
		return_date = now;
	}
	virtual date find_return_date(date m_date, string origin_name) {
		return return_date;
	}
};

class book : public resource {
public:
	book() {}
	book(string name);
};

class magazine : public resource {
public:
	vector<date> date_arr;
	vector<member*> mem_arr;
	bool check_publication(date a, date b) {
		if(a.y == b.y && a.m == b.m)
			return true; 
		return false;
	}
	magazine() {}
	magazine(string name) : resource("Magazine", name) {
		isborrowed = false;	date_arr.resize(0);	mem_arr.resize(0);
	}
	void update(date now) {
		int idx = 0;
		while(idx < date_arr.size()) {
			int diff = (now.y - date_arr[idx].y) * 12 + (now.m - date_arr[idx].m);
			if(diff >= 12) {
				date_arr.erase(date_arr.begin() + idx);
				mem_arr.erase(mem_arr.begin() + idx);
			}
			else
				idx++;
		}
	}
	bool isSame(string rsc_name, date now, date m_date) {
		for(int i = 0; i < rsc_name.size(); i++) {
			if(rsc_name[i] == '[') {
				rsc_name = rsc_name.substr(0, i);
				break;
			}
		}
		if(rsc_name != name)
			return false;
		int diff = (now.y - m_date.y) * 12 + (now.m - m_date.m);
		if(diff >= 12 || diff < 0)
			return false;
		return true;
	}
	bool already_borrow(member* m, date m_date) {
		for(int i = 0; i < mem_arr.size(); i++) {
			if(check_publication(date_arr[i], m_date) && mem_arr[i]->name == m->name)
				return true;
		}
		return false;
	}
	bool return_isborrowed(date m_date) {
		for(int  i = 0; i < date_arr.size(); i++)
			if(check_publication(date_arr[i], m_date))
				return true;
		return false;
	}
	void borrow_rsc(member* m, date now, date m_date, string origin_name) {
		m->book_name.push_back(origin_name); //borrow_rsc!!
		m->lent_date.push_back(now);
		date_arr.push_back(m_date);
		mem_arr.push_back(m);
	}
	bool matching_user(member* m, date m_date, string origin_name) {
		cout << "come in " << endl;
		for(int i = 0; i < m->book_name.size(); i++) {
			cout << "origin_name : " << origin_name << " book_name : " << m->book_name[i] << endl;
			if(origin_name == m->book_name[i])
				return true;
		}
		return false;
	}
	void return_rsc(member* m, date now, date m_date, string origin_rsc_name, string rsc_name, int bidx) {
		m->book_name.erase(m->book_name.begin() + bidx);
		m->lent_date.erase(m->lent_date.begin() + bidx);
		for(int i = 0; i < date_arr.size(); i++) {
			if(check_publication(date_arr[i], m_date)) {
				date_arr.erase(date_arr.begin() + i);
				mem_arr.erase(mem_arr.begin() + i);
				break;
			}
		}
	}
	date find_return_date(date m_date, string origin_name) {
		for(int i = 0; i < date_arr.size(); i++) {
			if(check_publication(date_arr[i], m_date)) {
				for(int j = 0; j < mem_arr[i]->book_name.size(); j++) {
					if(mem_arr[i]->book_name[j] == origin_name)
						return date_plus(mem_arr[i]->lent_date[j], mem_arr[i]->max_lent - 1);
				}
			}
		}
	}
};

class e_book : public resource {
public:
	vector<member*> mem_arr;
	vector<date> ret_date_arr;
	e_book() {}
	e_book(string n) {
		mem_arr.resize(0); ret_date_arr.resize(0);
		isborrowed = false;
		int i;
		for(i = 0; i < n.size(); i++)
			if(n[i] == '[')
				break;
		type = "E-book";	name = n.substr(0, i);
		string c = n.substr(i + 1, n.size() - 1 - i);
		capacity = 0;
		int mul = 1;
		for(int idx = c.size() - 1; idx >= 0; idx--) {
			capacity += (c[idx] - '0') * mul;
			mul *= 10;
		}
	}
	void update(date now) {
		int idx = 0;
		while(idx < ret_date_arr.size()) {
			if(now > ret_date_arr[idx]) {
				mem_arr[idx]->now_capacity -= capacity;
				for(int i = 0; i < mem_arr[idx]->book_name.size(); i++) {
					if(mem_arr[idx]->book_name[i] == name) {
						mem_arr[idx]->book_name.erase(mem_arr[idx]->book_name.begin() + i);
						mem_arr[idx]->lent_date.erase(mem_arr[idx]->lent_date.begin() + i);
					}
				}
				ret_date_arr.erase(ret_date_arr.begin() + idx);
				mem_arr.erase(mem_arr.begin() + idx);
			}
			else
				idx++;
		}
	}
	void borrow_rsc(member* m, date now, date m_date, string origin_name) {
		m->book_name.push_back(name); //borrow_rsc!!
		m->lent_date.push_back(now);
		mem_arr.push_back(m);
		ret_date_arr.push_back(date_plus(now, m->max_lent - 1));
		m->now_capacity += capacity;
	}
	bool matching_user(member* m, date m_date, string origin_name) {
		for(int i = 0; i < m->book_name.size(); i++) {
			if(name == m->book_name[i])
				return true;
		}
		return false;
	}
	void return_rsc(member* m, date now, date m_date, string origin_rsc_name, string rsc_name, int bidx) {
		m->book_name.erase(m->book_name.begin() + bidx);
		m->lent_date.erase(m->lent_date.begin() + bidx);
		m->now_capacity -= capacity;
		for(int i = 0; i < mem_arr.size(); i++) {
			if(mem_arr[i]->name == m->name) {
				ret_date_arr.erase(ret_date_arr.begin() + i);
				mem_arr.erase(mem_arr.begin() + i);
				break;
			}
		}
	}
};

#endif

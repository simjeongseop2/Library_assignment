#ifndef __LIBRARY_H__
#define __LIBRARY_H__
#include <fstream>
#include <vector>
#include <string>
#include "date.h"
#include "member.h"
#include "resource.h"
#include "space.h"
using namespace std;

class library {
public:
	vector<member*> mem;
	vector<resource*> rsc;
	vector<space*> spc;
	library();
	int CHARtoINT(const string& str);
	char* INTtoSTRING(int n);
	date make_date(const string& str);
	date make_space_date(const string& str);
	string DATEtoSTRING(date& dat);
	date date_plus(date today, int p);
	int date_diff(date dat1, date dat2);
	void Borrow_rsc(ofstream& output,string rsc_type, string rsc_name, string mem_type, string mem_name, date dat, int cnt);
	void Return_rsc(ofstream& output, string rsc_type, string rsc_name, string mem_type, string mem_name, date dat, int cnt);
	void Borrow_spc(ofstream& output, string spc_type, string mem_type, string mem_name,
			int spc_num, int num_of_mem, int borrow_time, date dat, int cnt);
	void REC_spc(ofstream& output, string oper, string spc_type, string mem_type, string mem_name,
					int spc_num, date dat, int cnt);
	void process();
	void ThrowFunc(string spc_type, string mem_type, string mem_name, string oper, date dat, int borrow_time);
};

#endif
#include "library.h"

library::library() {
	mem.resize(0); rsc.resize(0);
	ifstream source;
	source.open("resource.dat");
	string str;
	string before = "NULL_Dump";
	for(int i = 0; i < 2; i++) { source >> str; } //get dump
	while(1) {
		source >> str;
		if(source.eof() || before == str)
			break;
		if(str == "Book") {
			source >> str;
			book* temp = new book(str);
			rsc.push_back(temp);
		}
		else if(str == "Magazine") {
			source >> str;
			magazine* temp = new magazine(str);
			rsc.push_back(temp);
		}
		else {	//E-book name + capacity -> okay
			source >> str;
			e_book* temp = new e_book(str);
			rsc.push_back(temp);
		}
		before = str;
	}
	source.close();
	spc.resize(13);
	for(int i = 0; i < 10; i++)
		spc[i] = new study_room;
	spc[10] = new seat(0, 24);
	spc[11] = new seat(9, 21);
	spc[12] = new seat(9, 18);
}
int library::CHARtoINT(const string& str) {
	return (str[0] - '0') * 10 + (str[1] - '0');
}
char* library::INTtoSTRING(int n) {
	char* ret = new char[3];
	ret[0] = ((n / 10) % 10) + '0';
	ret[1] = (n % 10) + '0';
	ret[2] = '\0';
	return ret;
}
date library::make_date(const string& str) {
	date ret;
	ret.y = CHARtoINT(str.substr(0, 2));
	ret.m = CHARtoINT(str.substr(3, 2));
	ret.d = CHARtoINT(str.substr(6, 2));
	ret.t = 0;
	return ret;
}
date library::make_space_date(const string& str) {
	date ret;
	ret.y = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + CHARtoINT(str.substr(2, 2));
	ret.m = CHARtoINT(str.substr(5, 2));
	ret.d = CHARtoINT(str.substr(8, 2));
	ret.t = CHARtoINT(str.substr(11, 2));	
	return ret;
}
string library::DATEtoSTRING(date& dat) {
	char y[3], m[3], d[3];
	y[0] = (dat.y / 10) + '0'; y[1] = (dat.y % 10) + '0'; y[2] = '\0';
	m[0] = (dat.m / 10) + '0'; m[1] = (dat.m % 10) + '0'; m[2] = '\0';
	d[0] = (dat.d / 10) + '0'; d[1] = (dat.d % 10) + '0'; d[2] = '\0';
	string y1(y), m1(m), d1(d);
	string slash = "/";
	string ret = y1 + slash + m1 + slash + d1;
	return ret;
}
date library::date_plus(date today, int p) {
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
int library::date_diff(date dat1, date dat2) { //dat1 > dat2
	int n1 = dat1.y * 360 + dat1.m * 30 + dat1.d;
	int n2 = dat2.y * 360 + dat2.m * 30 + dat2.d;
	return n1 - n2;
}
void library::Borrow_rsc(ofstream& output,string rsc_type, string rsc_name,
						string mem_type, string mem_name, date dat, int cnt) {
	for(int i = 0; i < rsc.size(); i++)
		rsc[i]->update(dat);
	int idx = -1;
	date m_date;
	string origin_rsc_name = rsc_name;
	if(rsc_type == "Magazine") {
		int i = 0;
		for(i = 0; i < rsc_name.size(); i++)
			if(rsc_name[i] == '[')
				break;
		m_date.y = CHARtoINT(rsc_name.substr(i+1, 2));
		m_date.m = CHARtoINT(rsc_name.substr(i+4, 2));
		rsc_name = rsc_name.substr(0, i); 
	}
	for(int i = 0; i < rsc.size(); i++) {		//Magazine name! if 1 year differ idx = -1 break;
		if(rsc[i]->type == rsc_type && rsc[i]->isSame(rsc_name, dat, m_date)) {
			idx = i; break;
		}
	}
	if(idx == -1) {
		output << cnt << "\t1\tNon exist resource.\n"; 
		return;
	}
	member* m = NULL;
	for(int i = 0; i < mem.size(); i++)
		if(mem[i]->name == mem_name && mem[i]->type == mem_type) {
			m = mem[i]; break;
		}
	if(m == NULL) {
		if(mem_type == "Undergraduate")
			mem.push_back(m = new undergraduate(mem_name));
		else if(mem_type == "Graduate")
			mem.push_back(m = new graduate(mem_name));
		else
			mem.push_back(m = new faculty(mem_name));
	}
	if(m->max_num == m->book_name.size() && rsc_type != "E-book") {
		output << cnt << "\t2\tExceeds your possible number of borrow. Possible # of borrows: " << m->max_num << endl;
		return;
	} //if e-book, return code 15 -> "Exceeds your storage capacity"
	for(int i = 0; i < m->book_name.size(); i++) {
		if(rsc[idx]->isSame(m->book_name[i], dat, m_date) && rsc[idx]->already_borrow(m, m_date)) { //if magazine, check public_date!
			output << cnt << "\t4\tYou already borrowed this book at " << DATEtoSTRING(m->lent_date[i]) << endl;
			return;
		}
	}
	if(rsc[idx]->return_isborrowed(m_date) && rsc_type != "E-book") { //if magazine, check public_date!
		date return_date = rsc[idx]->find_return_date(m_date, origin_rsc_name);
		output << cnt << "\t5\tOther member already borrowed this book. This book will be returned at " << DATEtoSTRING(return_date) << endl;
		return;
	}
	if(!m->is_able(dat)) {
		output << cnt << "\t6\tRestricted member until " << DATEtoSTRING(m->disable) << endl;
		return;
	}
	if(rsc_type == "E-book" && (m->now_capacity + rsc[idx]->capacity > m->max_capacity)) {
		output << cnt << "\t15\tExceeds your storage capacity." << endl;
		return;
	}
	for(int bidx = 0; bidx < m->lent_date.size(); bidx++) {
		if(dat > date_plus(m->lent_date[bidx], m->max_lent - 1)) { ////if Magazin
			output << cnt << "\t16\tPreviously borrowed books are overdue, so borrow is limited." << endl;
			return;
		}
	}
	rsc[idx]->borrow_rsc(m, dat, m_date, origin_rsc_name);
	output << cnt << "\t0\tSuccess.\n";
	return;
}
void library::Return_rsc(ofstream& output, string rsc_type, string rsc_name,
			string mem_type, string mem_name, date dat, int cnt) {
	//rsc update!!!
	for(int i = 0; i < rsc.size(); i++)
		rsc[i]->update(dat);
	int idx = -1;
	date m_date;
	string origin_rsc_name = rsc_name;
	if(rsc_type == "Magazine") {
		int i = 0;
		for(i = 0; i < rsc_name.size(); i++)
			if(rsc_name[i] == '[')
				break;
		m_date.y = CHARtoINT(rsc_name.substr(i+1, 2));
		m_date.m = CHARtoINT(rsc_name.substr(i+4, 2));
		rsc_name = rsc_name.substr(0, i); 
	}
	for(int i = 0; i < rsc.size(); i++) {//Magazine name! if 1 year differ idx = -1 break;
		if(rsc[i]->type == rsc_type && rsc[i]->isSame(rsc_name, dat, m_date)) {
			idx = i; break;
		}
	}
	member* m = NULL;
	for(int i = 0; i < mem.size(); i++)
		if(mem[i]->name == mem_name && mem[i]->type == mem_type) {
			m = mem[i]; break;
		}
	if(m == NULL) {
		if(mem_type == "Undergraduate")
			mem.push_back(m = new undergraduate(mem_name));
		else if(mem_type == "Graduate")
			mem.push_back(m = new graduate(mem_name));
		else
			mem.push_back(m = new faculty(mem_name));
	}
	int bidx = -1;		/////return_rsc!!
	for(int i = 0; i < m->book_name.size(); i++)
		if(m->book_name[i] == origin_rsc_name) {
			bidx = i; break;
		}
	if(idx == -1 && bidx == -1) {
		output << cnt << "\t1\tNon exist resource.\n"; 
		return;
	}
	for(int i = 0; i < rsc.size(); i++) {//Magazine name! if 1 year differ idx = -1 break;
		if(rsc[i]->type == rsc_type && rsc[i]->name == rsc_name) {
			idx = i; break;
		}
	}
	if(rsc[idx]->matching_user(m, m_date, origin_rsc_name) == false) { //rsc[idx]->matching_user(mem_name)
		output << cnt << "\t3\tYou did not borrow this book.\n";
		return;
	}
	if(dat > date_plus(m->lent_date[bidx], m->max_lent - 1) &&  rsc_type != "E-book") { ////if Magazin
		int diff = date_diff(dat, date_plus(m->lent_date[bidx], m->max_lent - 1));
		date disable = date_plus(dat, diff);
		if(disable > m->disable)
			m->disable = disable;
		output << cnt << "\t7\tDelayed return. You'll be restricted until " << DATEtoSTRING(disable) << endl;
	}
	else
		output << cnt << "\t0\tSuccess.\n";
	rsc[idx]->return_rsc(m, dat, m_date, origin_rsc_name, rsc_name, bidx);
}

void library::Borrow_spc(ofstream& output, string spc_type, string mem_type, string mem_name,
			int spc_num, int num_of_mem, int borrow_time, date dat, int cnt) {
	spc_num--;
	if(spc_type == "Seat") { spc_num += 10; }
	if((spc_type == "StudyRoom" && (spc_num < 0 || spc_num >= 10)) ||
		(spc_type == "Seat" && (spc_num < 10 || spc_num >= 13))) {
		output << cnt << "\t8\tInvalid space id." << endl; return;
	}
	if(dat.t >= spc[spc_num]->close_time || dat.t < spc[spc_num]->open_time) {
		output << cnt << "\t9\tThis space is not available now. Available from " << INTtoSTRING(spc[spc_num]->open_time)
		 << " to " << INTtoSTRING(spc[spc_num]->close_time) << ".\n";
		return;
	}	
	for(int i = 0; i < spc.size(); i++)
		spc[i]->update(dat);
	bool already_borrow = false;
	int sidx = 10, fidx = 12;
	if(spc_type == "StudyRoom") {
		sidx = 0; fidx = 9;
	}
	for(int i = sidx; i <= fidx; i++)
			if(spc[i]->isThereUser(mem_name))
				already_borrow = true;
	if(already_borrow) {
		output << cnt << "\t11\tYou already borrowed this kind of space." << endl; return;
	}
	if(num_of_mem > spc[spc_num]->max_num || (spc_type == "Seat" && num_of_mem > 1)) { /////////////////////////////////////////////////
		output << cnt << "\t12\tExceed available number." << endl; return;
	}
	bool time_exceed = false;
	if(spc_type == "Seat" && borrow_time > 3)
		time_exceed = true;
	if(time_exceed || borrow_time > spc[spc_num]->max_time) { 
		output << cnt << "\t13\tExceed available time." << endl; return;
	}
	bool nospace = false, notime = false;
	if(spc_type == "StudyRoom") {
		if(spc[spc_num]->user.size() != 0)
			nospace = true;
	}
	else if(spc_type == "Seat") {
		if(spc[spc_num]->empty_num < num_of_mem)
			nospace = true;
	}
	if(dat.t + borrow_time > spc[spc_num]->close_time)
		notime = true;
	if(nospace) {
		output << cnt << "\t14\tThere is no remain space. This space is available after "
		 << spc[spc_num]->return_available_time(dat.t, num_of_mem) <<".\n"; return;
	}
	if(notime) {
		borrow_time = spc[spc_num]->close_time - dat.t; 
	}
	spc[spc_num]->borrow_space(mem_name , num_of_mem, dat, borrow_time);
	output << cnt << "\t0\tSuccess." << endl;
}

void library::REC_spc(ofstream& output, string oper, string spc_type, string mem_type, string mem_name,
							int spc_num, date dat, int cnt) {
	spc_num--;
	for(int i = 0; i < spc.size(); i++)
		spc[i]->update(dat);
	if(spc_type == "Seat") { spc_num += 10; }
	if((spc_type == "StudyRoom" && (spc_num < 0 || spc_num >= 10)) ||
		(spc_type == "Seat" && (spc_num < 10 || spc_num >= 13))) {
		output << cnt << "\t8\tInvalid space id." << endl; return;
	}
	if(!spc[spc_num]->isThereUser(mem_name)) {
		output << cnt << "\t10\tYou did not borrow this space." << endl; return;
	}
	if(oper == "R")
		spc[spc_num]->return_space(mem_name);
	else if(oper == "E")
		spc[spc_num]->empty_space(mem_name, dat);
	else if(oper == "C")
		spc[spc_num]->comback_space(mem_name);
	output << cnt << "\t0\tSuccess." << endl;
}

void library::ThrowFunc(string spc_type, string mem_type, 
					string mem_name, string oper, date dat, int borrow_time) {
	date cut_line;
	cut_line.y = 2009; cut_line.m = 12; cut_line.d = 30;
	if(cut_line > dat || cut_line == dat)
		throw 0;
	else if(spc_type != "Seat" && spc_type != "StudyRoom")
		throw 1;
	else if(oper != "R" && oper != "E" && oper != "C" && oper != "B")
		throw 2;
	else if(mem_type != "Undergraduate" && mem_type != "Graduate" && mem_type != "Faculty")
		throw 3;
	for(int i = 0; i < mem_name.size(); i++) {
		if(mem_name[i] >= '0' && mem_name[i] <= '9')
			throw 4;
	}
	if(borrow_time < 0)
		throw 5;

}
						
void library::process() {
	ifstream input;
	input.open("input.dat");
	ifstream space;
	space.open("space.dat");
	ofstream output; 
	output.open("output.dat");
	output << "Op_#\tReturn_code\tDescription\n";
	string str;
	for(int i = 0; i < 6; i++) { input >> str;} //get dump
	for(int i = 0; i < 8; i++) { space >> str; } //get dump
	int cnt = 1;
	date dat1, dat2;
	bool input_finished = false;
	bool space_finished = false;
	bool input_received = false;
	bool space_received = false;
	while(1) {
		if(input_finished == false && input_received == false) {
			input >> str;
			if(!input.eof() && (str[0] >= '0' && str[0] <= '9')) {
				dat1 = make_date(str);
				dat1.y += 2000;
				input_received = true;
			}
			else
				input_finished = true;
		}
		if(space_finished == false && space_received == false) {
			space >> str;
			if(!space.eof() && (str.size() >= 12)) {
				dat2 = make_space_date(str);
				space_received = true;
			} 
			else
				space_finished = true;
		}
		if(input_finished && space_finished)
			break;
		if(space_finished || (!input_finished && (dat2 > dat1 || dat1 == dat2))) {
			input_received = false;
			dat1.y -= 2000;
			string rsc_type, rsc_name, oper , mem_type, mem_name;
			input >> rsc_type >> rsc_name >> oper >> mem_type >> mem_name;
			if(oper == "B")
				Borrow_rsc(output, rsc_type, rsc_name, mem_type, mem_name, dat1, cnt);
			else
				Return_rsc(output, rsc_type, rsc_name, mem_type, mem_name, dat1, cnt);
		}
		else {
			try {
				space_received = false;
				string spc_type, oper, mem_type, mem_name;
				int spc_num, num_of_mem, borrow_time;	
				space >> spc_type >> spc_num >> oper >> mem_type >> mem_name;
				if(oper == "B") {
					space >> num_of_mem >> borrow_time;
					ThrowFunc(spc_type, mem_type, mem_name, oper, dat2, borrow_time);
					Borrow_spc(output, spc_type, mem_type, mem_name,
								spc_num, num_of_mem, borrow_time, dat2, cnt);
				}
				else {
					ThrowFunc(spc_type, mem_type, mem_name, oper, dat2, borrow_time);
					REC_spc(output, oper, spc_type, mem_type, mem_name,
								spc_num, dat2, cnt);
				}
			} catch(int expn) {
				if(expn == 0)
					output << cnt << "\t-1\tDate out of range" << endl;
				else if(expn == 1)
					output << cnt << "\t-1\tNon-exist space type" << endl;
				else if(expn == 2)
					output << cnt << "\t-1\tNon-exist operation" << endl;
				else if(expn == 3)
					output << cnt << "\t-1\tNon-exist member type" << endl;
				else if(expn == 4)
					output << cnt << "\t-1\tMember name with numbers" << endl;
				else if(expn == 5)
					output << cnt << "\t-1\tNegative time" << endl;

			}
		}
		cnt++;
	}
	input.close(); output.close(); space.close();
}
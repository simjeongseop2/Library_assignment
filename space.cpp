#include "space.h"

space::space(int mn, int mt, int ot, int ct) : max_num(mn), max_time(mt), open_time(ot), close_time(ct) {
	num = 0; empty_num = max_num;
	user.resize(0);
}
bool space::isThereUser(string name) {
	for(int i = 0 ; i < user.size(); i++)
		if(user[i].name == name)
			return true;
	return false;
}
void space::borrow_space(string name, int n, date dat, int borrow_time) {
	user.push_back(user_info(name, n, dat, borrow_time));
	num += n;	empty_num -= n;
}
void space::return_space(string name) {
	for(int i = 0; i < user.size(); i++)
		if(user[i].name == name) {
			num -= user[i].num;	empty_num += user[i].num;
			user.erase(user.begin() + i);
			break;
		}
}
void space::empty_space(string name, date dat) {
	for(int i = 0; i < user.size(); i++)
		if(user[i].name == name) {
			user[i].isEmpty = true;
			user[i].empty_time = dat.t;
			break;
		}
}
void space::comback_space(string name) {
	for(int i = 0; i < user.size(); i++)
		if(user[i].name == name) {
			user[i].isEmpty = false;
			break;
		}
}

study_room::study_room() : space(6, 3, 9, 18) {}
void study_room::update(date d) {
	int idx = 0;
	while(idx < user.size()) {
		if(d > user[idx].end || d.t >= user[idx].end.t) {
			num -= user[idx].num; empty_num += user[idx].num;
			user.erase(user.begin() + idx);
		}
		else
			idx++;
	}
}
int study_room::return_available_time(int t, int n) {
	return user[0].end.t;
}

seat::seat(int ot, int ct) : space(50, 3, ot, ct) {}
void seat::update(date d) {
	int idx = 0;
	while(idx < user.size()) {
		if(d > user[idx].end || d.t >= user[idx].end.t || (user[idx].isEmpty && d.t > user[idx].empty_time)) {
			num -= user[idx].num; empty_num += user[idx].num;
			user.erase(user.begin() + idx);
		}
		else
			idx++;
	}
}
int seat::return_available_time(int t, int n) {
	for(int avt = t; avt < close_time; avt++) {
		int available_space = empty_num;
		for(int i = 0; i < user.size(); i++) {
			if(avt >= user[i].end.t)
				available_space += user[i].num;
		}
		if(available_space >= n)
			return avt;
	}
	return close_time;
}
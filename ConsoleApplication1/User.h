#pragma once
#include<ctime>
#include<fstream>
#include <iostream>
#include "AbstractUser.h"
class content {
	
	vector<string> answer;
	int visits;
	
public:
	int id;
	string question;
	content (const content&  co):question(co.question),id(co.id),visits(0){}
	content(string a,int c):question(a),visits(0),id(c){}
	void printanswer() {
		if (answer.size() == 0)cout << "Not answered" << endl;
		else {
			int h = answer.size();
			for (int i = 0; i < h;i++) {
				cout << answer[i] << endl;
			}
		}
	}
	void printquestion() {
		cout << question << endl;
	}
	void addvisit() {
		visits++;
	}
	int getvisits() {
		return visits;
	}
	void answer1(string s) {
		answer.push_back(s);
	}
	int getid() {
		return id;
	}
	void update(string s) {
		question = s;
	}

};
class User : public AbstractUser {
public:
	User(string username, string password, string email, UserType type);
	int getsize();
	static void init(const string &salt);
	void logger2(ofstream& a);
public:
	void addq(string s, int b);
	void set_password(string password);
	bool check_password(string password);
	void updateq(int index,string ups);
public:
	bool authenticate(string username, string password);
	void deleteAccount();
	void printquestions();
	void deleteq(int index);
public:
	static User& login(string username, string password);
	static User& signup(string username, string password, string email);
	
private:
	vector<content> userquestions;
	static string salt;
	static vector<User> users;
	

};
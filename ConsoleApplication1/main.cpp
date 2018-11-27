#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include<fstream>
#include<ctime>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


enum MenuState {
	START,
	LOGGED_IN,
	MY_QUESTIONS,
	END,VIEW
	
};

int main() {

	int idgen = 0;

	ifstream flogcount("logcounter.txt");

	int logcounter;
	flogcount >> logcounter;
	flogcount.close();
	string logger = "logx.txt";
	logger[3] = '0'+(char)logcounter;
	
	ofstream logger1(logger);

	
	//vector<content> questions;
	//int global_question_counter = 0;
	User::init("SECRET_KEY");
	User * loggedInUser = nullptr;
	MenuState menuState = MenuState::START;
	string last_message;


	char choice;
	while (menuState != MenuState::END) {
		system(CLEAR);
		if (!last_message.empty())
			cout << last_message << endl;
		last_message = "";
		switch (menuState) {
		case MenuState::START: {
			cout << "1. login\n2. signup\ne. exit\n";
			cin >> choice;
			switch (choice) {
			case '1': { // login
				try {
					string username, password;
					cout << "Enter Username: ";
					cin >> username;
					cout << "Enter Password: ";
					cin >> password;
					loggedInUser = &User::login(username, password);
					loggedInUser->logger2(logger1);
					menuState = MenuState::LOGGED_IN;
					
				}
				catch (WrongUsernameOrPasswordException &e) {
					last_message = e.what();
				}
				break;
			}
			case '2': { // signup
				try {
					string username, password, email;
					cout << "Enter Email: ";
					cin >> email;
					cout << "Enter Username: ";
					cin >> username;
					cout << "Enter Password: ";
					cin >> password;
					loggedInUser = &User::signup(username, password, email);
					loggedInUser->logger2(logger1);
					menuState = MenuState::LOGGED_IN;
					
					last_message = "User signed up!\n";
				}
				catch (UsernameAlreadyExistsException &e) {
					last_message = e.what();
					break;

				}
				catch (EmailAlreadyExistsException &e) {
					last_message = e.what();
				}
				break;
			}
			case 'e': { // exit
				menuState = MenuState::END;
				break;
			}
			default: { // unknown input
				last_message = "Unknown Input\n";
				break;
			}
			}
			break;
		}
	
		case MenuState::LOGGED_IN: {
			cout << "d.delete account\nl. logout\ne. exit\n"<<"m.my questions\n";
			cin >> choice;
			switch (choice) {
			case 'd': {
				try {
					loggedInUser->deleteAccount();
					cout << "Account successfully deleted\n";
					loggedInUser = nullptr;
					menuState = MenuState::START;
				}
				catch (DeleteAdminException &e) {
					last_message = e.what();
				}
				break;
			}
			case 'l': { // logout
				loggedInUser = nullptr;
				menuState = MenuState::START;
				last_message = "GOOD BYE\n";
				break;
			}
			case 'm': {
				menuState = MenuState::MY_QUESTIONS;
				break;
			}
			case 'e': { // exit
				menuState = MenuState::END;
				break;
			}
			
			default: { // unknown input
				last_message = "Unknown Input\n";
				break;
			}
					 
			}
			break;
		}
		case MenuState::VIEW: {
			int dc;
			loggedInUser->printquestions();
			cout << "what do you want to do?\nu.update question\nd.delet question\nl. logout\ne.exit\n";
			cin >> choice;
			
			switch (choice)
			{
			case'e': {
				menuState = MenuState::END;
				break;
			}
			case'l': {
				loggedInUser = nullptr;
				menuState = MenuState::START;
				last_message = "GOOD BYE\n";
				break;
			}
			case 'd':{
				cout << "choose the number of question:";
				cin >> dc;
				loggedInUser->deleteq(dc - 1);
				last_message = "Question deleted\n";
				break;
				}
			case 'u': {
				cout << "choose the number of question:";
				cin >> dc;
				string s1;
				cout << "type your question: ";
				cin >> ws;
				getline(cin, s1);
				loggedInUser->updateq(dc-1, s1);
				last_message = "Question updated\n";
				break;
			}
			default:
				last_message = "Unknown Input\n";
				break;
			}
			
			//system("PAUSE");
			break;
		}
		case MenuState::MY_QUESTIONS: {
			cout << "a.add question\np.view questions\n";
			cin >> choice;
			string dr2;
			switch (choice)
			{
			case 'p':{
				menuState = MenuState::VIEW;

				break;
				}
			case 'a': {
				cin >> ws;
				getline(cin,dr2);
				cout << dr2;
				loggedInUser->addq(dr2, idgen);
				idgen++;
				menuState = MenuState::MY_QUESTIONS;
				last_message = "Question added\n";
				break; }
			default: {
				last_message = "Unknown Input\n";
				break; }
				}
			break;
			}
			break;
		
		}
		}
	
	system(CLEAR);
	cout << "GOODBYE" << endl;
	ofstream flo("logcounter.txt");
	flo.clear();
	flo << logcounter + 1;
	flo.close();
	logger1.close();
	return 0;
}
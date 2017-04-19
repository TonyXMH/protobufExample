/*************************************************************************
	> File Name: WriteMessage.cpp
	> Author: tony
	> Mail: 445241843@qq.com 
	> Created Time: 2017年04月19日 星期三 10时09分02秒
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include"addressbook.pb.h"
using namespace std;
//This function fill in a Person message base on user input

void PromptForAddress(tutorial::Person *person) {

	cout << "Enter person ID number:";
	int nId;
	cin >> nId;
	person->set_id(nId);
	cin.ignore(256, '\n');

	cout << "Enter name:";
	getline(cin, *person->mutable_name());

	cout << "Enter email address (blank for none)";
	string szEmail;
	getline(cin, szEmail);
	if(!szEmail.empty()){
		person->set_email(szEmail);
	}

	while(true) {
		cout << "Enter a phone number (or leave blank to finish)";
		string szNumber;
		getline(cin, szNumber);
		if(szNumber.empty()) {
			break;
		}
		tutorial::Person::PhoneNumber *phone_number = person->add_phones();
		phone_number->set_number(szNumber);

		cout << "Is this a mobile, home, or work phone?";
		string szType;
		getline(cin, szType);
		if(szType == "mobile") {
			phone_number->set_type(tutorial::Person::MOBILE);
		} else if(szType == "home") {
			phone_number->set_type(tutorial::Person::HOME);
		} else if(szType == "work") {
			phone_number->set_type(tutorial::Person::WORK);
		} else {
			cout << "Unknown Phone type. Using default." << endl;
		}		
	}
}

int main(int argc, char *argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
		return -1;
	}
	tutorial::AddressBook address_book;
	{
		fstream input(argv[1], ios::in | ios::binary);
		if(!input) {
			cout << argv[1] << ": File not found. Creating a new file." << endl;
		} else if(!address_book.ParseFromIstream(&input)) {
			cerr << "Failed to parse address book." << endl;
			return -1;
		}

	}

	PromptForAddress(address_book.add_people());

	{
		fstream output(argv[1], ios::out | ios::trunc | ios::binary);
		if(!address_book.SerializeToOstream(&output)) {
			cerr << "Failed to write address book. " << endl;
			return -1;
		}
	}

	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}



#include <iostream>
#include <vector>
#include <string>
#include "Database.h"
#include "Table.h"
#include "Record.h"

using namespace std;

#define maxOption		10
#define minOption		1

void displayMenu() {

	cout << endl << endl;
	cout << "Enter number of desired option." << endl;
	cout << "Options: " << endl;
	cout << "1)\tExit Application" << endl;
	cout << "2)\tList Businesses" << endl;
	cout << "3)\tBusiness Attributes" << endl;
	cout << "4)\tBusiness Description" << endl;
	cout << "5)\tList Users" << endl;
	cout << "6)\tUser Attributes" << endl;
	cout << "7)\tUser Description" << endl;
	cout << "8)\tJoin Tables" << endl;
	cout << "9)\tBusiness Review" << endl;
	cout << "10)\tCustom Query" << endl;
	cout << endl;
}

bool errorCheck(int choice) {

	return (choice < minOption || choice > maxOption);
}

void listBusinesses(Database data) {

	Table* bizTable = new Table(data.query("name", "business", ""));
	std::cout << "TEST" << std::endl;
	//std::cout << "Number of entries: " << bizTable->count_entries() << std::endl;//

}

void bizAttributes(Database data) {
	/*
	int bizIndex = 0;
	bool tableNotFound = true;

	vector<string> names = data.listTable();
	vector<Table> tables = data.getTables();

	for (int i = 0; i < names.size(); i++) {

		if ("business" == names.at(i)) {

			bizIndex = i;
			tableNotFound = false;
			break;
		}
	}

	if (tableNotFound) {

		cout << "Error: Business table not found" << endl;
		return;
	}

	Table* bizTable = &(tables.at(bizIndex));

	cout << bizTable->attributes_str() << endl;
	*/
}


void listUsers(Database db) {

	//std::vector<std::string> 

}

int main() {

	int option = 0;

	Database db;
	cout << "Loading business table\n";
	db.load("business_output.txt");

	cout << "Loading review table\n";
	db.load("review_output.txt");

	cout << "Loading user table\n";
	db.load("user_output.txt");

	while (true) {

		displayMenu();

		vector <string> tables = db.listTable();

		for (int i = 0; i < tables.size(); i++) {

			cout << "Table " << i << ": " << tables.at(i) << endl;
		}

		cin >> option;

		if (errorCheck(option)) {

			cout << endl << "User input is not a given option" << endl;
			continue;
		}

		if (option == 1) {

			break;
		}

		switch (option) {

		case 2:
			listBusinesses(db);
			break;

		case 3:

			break;

		case 4:

			break;

		case 5:

			break;

		case 6:

			break;

		case 7:

			break;

		case 8:

			break;

		case 9:

			break;

		case 10:

			break;

		case 11:

			break;

		default:

			cout << "Error in selection" << endl;
			break;
		}
		
	}

	cout << "\n\nClosing...";
}

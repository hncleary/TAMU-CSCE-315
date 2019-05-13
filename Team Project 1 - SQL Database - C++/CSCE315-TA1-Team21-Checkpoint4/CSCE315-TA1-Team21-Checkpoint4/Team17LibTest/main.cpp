#include <iostream>
#include <vector>
#include <string>
#include "Database.h"
#include "Table.h"
#include "Record.h"

using namespace std;

#define maxOption		11
#define minOption		1

void displayMenu() {

	cout << endl << endl;
	cout << "Enter number of desired option." << endl;
	cout << "Options: " << endl;
	cout << "1)\tExit Application" << endl;
	cout << "2)\tList Businesses" << endl;
	cout << "3)\tBusiness Description" << endl;
	cout << "4)\tList Users" << endl;
	cout << "5)\tUser Description" << endl;
	cout << "6)\tUser Attributes" << endl;
	cout << "7)\tBusiness Attributes" << endl;
	cout << "8)\tJoin Tables" << endl;
	cout << "9)\tBusiness Review" << endl;
	cout << "10)\tCustom Query" << endl;
	cout << endl;
}

// Replace a given character with a new character.
string replace(string str, char old_char, char new_char) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == old_char) {
			str[i] = new_char;
		}
	}

	return str;
}

bool errorCheck(int choice) {

	return (choice < minOption || choice > maxOption);
}

// List businesses
void listNames(Database data, string name) {
	
	int bizIndex = 0;
	bool tableNotFound = true;

	vector<string> names = data.listTable();
	vector<Table> tables = data.getTables();

	for (int i = 0; i < names.size(); i++) {

		if (name == names.at(i)) {

			bizIndex = i;
			tableNotFound = false;
			break;
		}
	}

	if (tableNotFound) {

		cout << "Error: " << name << " table not found" << endl;
		return;
	}

	Table tb = tables.at(bizIndex);

	int max_num;
	cout << "How many do you want to list?: ";
	cin >> max_num;

	cout << name << " names:" << endl;
	auto iter = tb.begin();
	for (int i = 0; (i < max_num) && (iter != tb.end()); i++) {

		Record current_rec = *iter;
		string name = current_rec.get(1);
		name = replace(name, '.', ',');
		name = replace(name, '_', ' ');

		cout << name << endl;
		iter++;

	}

	

}

void listAttributes(Database data, std::string name) {

	int bizIndex = 0;
	bool tableNotFound = true;

	vector<string> names = data.listTable();
	vector<Table> tables = data.getTables();

	for (int i = 0; i < names.size(); i++) {

		if (name == names.at(i)) {

			bizIndex = i;
			tableNotFound = false;
			break;
		}
	}

	if (tableNotFound) {

		cout << "Error: " << name << " table not found" << endl;
		return;
	}

	Table* bizTable = &(tables.at(bizIndex));

	string attributes = bizTable->attributes_str();
	attributes = replace(attributes, ' ', ',');
	attributes = replace(attributes, '_', ' ');

	cout << attributes << endl;
}

void description(Database data, string name) {

	vector<Table> tables = data.getTables();
	vector<string> names = data.listTable();

	int index = 0;
	bool notFound = true;

	for (int i = 0; i < tables.size(); i++) {

		if (names.at(i) == name) {
			index = i;
			notFound = false;
		}

	}

	if (notFound) {
		cout << name << "table not found." << endl;
		return;
	}


	Table tb = tables.at(index);

	string id;
	cout << "Enter " << name << " ID: ";
	cin >> id;


	for (auto iter = tb.begin(); iter != tb.end(); iter++) {

		Record rc = *iter;

		if (rc.get(0) == id) {

			vector<string> attributes = tb.get_attributes();

			for (int i = 0; i < attributes.size(); i++) {
				
				string attribute = attributes.at(i);
				attribute = replace(attribute, '.', ',');
				attribute = replace(attribute, '_', ' ');

				string value = rc.get(i);
				value = replace(value, '.', ',');
				value = replace(value, '_', ' ');

				cout << attribute << ": " << value << endl;

			}

			return;

		}

	}

	cout << "No " << name << " with ID " << id << " found." << endl;
	return;


}

void businessReview(Database data) {

	string business_id;
	cout << "Enter business ID: ";
	cin >> business_id;


	int bizIndex = 0;
	bool tableNotFound = true;

	vector<string> names = data.listTable();
	vector<Table> tables = data.getTables();

	for (int i = 0; i < names.size(); i++) {

		if ((names.at(i).length() >= 6) && ("review" == names.at(i).substr(names.at(i).length() - 6, names.at(i).length()))) {

			bizIndex = i;
			tableNotFound = false;
			break;
		}
	}

	if (tableNotFound) {

		cout << "Error: business table not found" << endl;
		return;
	}

	Table tb = tables.at(bizIndex);


	for (auto iter = tb.begin(); iter != tb.end(); iter++) {

		Record rc = *iter;

		if (rc.get(2) == business_id) {

			string stars = rc.get(3);
			string useful = rc.get(4);
			string funny = rc.get(5);
			string cool = rc.get(6);
			string text = rc.get(7);
			string date = rc.get(8);

			stars = replace(stars, '.', ',');
			stars = replace(stars, '_', ' ');

			text = replace(text, '.', ',');
			text = replace(text, '_', ' ');

			date = replace(date, '_', ' ');

			cout << "Stars: " << stars << endl;
			cout << "Useful: " << useful << endl;
			cout << "Funny: " << funny << endl;
			cout << "Cool: " << cool << endl;
			cout << "Text: " << text << endl;
			cout << "Date: " << date << endl;

			return;

		}

	}

	cout << "Business ID not found." << endl;



}


// Not functioning correctly:
void joinTables(Database data) {

	vector<string> table_names = data.listTable();
	cout << "TABLES:" << endl;
	for (int i = 0; i < table_names.size(); i++) {
		cout << table_names.at(i) << endl;
	}

	string name1, name2, key1, key2, output_name;

	cout << "Table 1: ";
	cin >> name1;
	cout << "Key for Table 1: ";
	cin >> key1;

	cout << "Table 2: ";
	cin >> name2;
	cout << "Key for Table 2: ";
	cin >> key2;

	cout << "Name of joined table: ";
	cin >> output_name;

	int index1 = 0;
	int index2 = 0;

	bool table1NotFound = true;
	bool table2NotFound = true;

	vector<string> names = data.listTable();
	vector<Table> tables = data.getTables();

	for (int i = 0; i < names.size(); i++) {

		if (name1 == names.at(i)) {
			index1 = i;
			table1NotFound = false;
		}

		if (name2 == names.at(i)) {

			index2 = i;
			table2NotFound = false;
		}
	}

	if (table1NotFound) {

		cout << "Error: " << name1 << " table not found" << endl;
		return;
	}
	if (table2NotFound) {
		cout << "Error: " << name2 << " table not found" << endl;
	}

	Table table1 = tables.at(index1);
	Table table2 = tables.at(index2);

	table1.assign_key(key1);
	table2.assign_key(key2);

	
	vector<string> attr1 = table1.get_attributes();
	vector<string> attr2 = table2.get_attributes();
	
	
	Table* output;
	if (key1 == key2) {
		output = natural_join(table1, table2);
	}
	else {
		output = cross_join(table1, table2);
	}
	

	output->printTable();
	
}


void customQuery(Database data) {

	string select, from, where, name;
	cout << "Select: ";
	cin >> select;

	cout << "From: ";
	cin >> from;

	cout << "Where: ";
	cin >> where;

	Table* new_tb = data.query(select, from, where);
	
	new_tb->printTable();




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
			listNames(db, "business");
			break;

		case 3:
			description(db, "business");
			break;

		case 4:
			listNames(db, "user");
			break;

		case 5:
			description(db, "user");
			break;

		case 6:
			listAttributes(db, "user");
			break;

		case 7:
			listAttributes(db, "business");
			break;

		case 8:
			joinTables(db);
			break;

		case 9:
			businessReview(db);
			break;

		case 10:
			customQuery(db);
			break;

		default:

			cout << "Error in selection" << endl;
			break;
		}
		
	}
}

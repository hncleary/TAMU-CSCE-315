#pragma once

#include "Table.h"
#include <string>

using namespace std;

class Database {
public:
	Database();
	void add(Table* tb, std::string name);
	void drop(std::string name);
	void save(std::string fileName);
	void load(std::string fileName);
	std::vector<std::string> listTable();
	std::vector<Table> getTables();
	Table* query(std::string select, std::string from, std::string where);

	void all_functions();

	//Helper functions for save/load
	string print_tables(int index);
	string parse_name(string &line);
	vector<string> parse_attributes(string &line);
	vector<string> parse_records(string &line);
	Record make_parsed_record(string &line);
	void replace_commas(string &line);

private:
	std::vector<Table*> tableList;
	std::vector<std::string> tableNames;

	std::vector<std::string> selectParser(std::string selectArgs);
	std::vector<std::vector<std::string>> whereParser(std::string whereArgs);
	bool isStringComparison(std::string s);
	Table* whereQuery(Table* tab, vector<string> beforeOp, vector<string> afterOp, string op);
	Table* AND(Table* tab, vector<string> beforeOp, vector<string> afterOp, string op);
	Table* OR(Table* tab, vector<string> beforeOp, vector<string> afterOp, string op);
	Table* NOT(Table* tab, vector<string> beforeOp, vector<string> afterOp, string op);
};

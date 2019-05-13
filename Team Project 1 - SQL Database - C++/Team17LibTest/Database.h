#pragma once

//Needs to include table
#include "Table.h"
#include <string>

class Database {
public:
	Database();
	void add(Table tb, std::string tableName);
	void drop(std::string tableName);
	void save(std::string fileName);
	void load(std::string fileName);
	std::vector<std::string> listTable();
	std::vector<Table> getTables();
	Table query(std::string select, std::string from, std::string where);

	void all_functions();

private:
	std::vector<Table> tableList;
	std::vector<std::string> tableNames;
};

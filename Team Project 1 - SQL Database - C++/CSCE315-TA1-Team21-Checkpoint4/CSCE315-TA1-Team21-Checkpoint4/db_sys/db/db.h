#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace database {

	/**************

	Record class

	**************/

	class record {
	private:

		std::vector<std::string> rec;

	public:

		record() {};

		record(int size);

		//number of entries in the record
		int sizeofRecord();

		int capacity();

		std::string getEntry(int index);

		void setEntry(int index, std::string entry);

		void addEntry(std::string entry);

		// Todo: Remove after testing.
		void print();
	};


	/**************

	Table class

	**************/

	class table {

	/**********************************************
	
	After creating a table, the rquired attributes
	should be added before the records.  

	**********************************************/

	private:

		std::vector <std::string> attributes;
		std::vector <record*> records;
		std::vector <int> keys;

	public:
		table() {};

		table(std::vector <std::string> names);

		void addAttribute(std::string attribute);

		void removeAttribute(std::string attribute);

		void addRecord(record* rec);

		//returns list of all attributes in table
		std::vector <std::string> getAttributes();

		int numberOfAttributes();

		//returns total number of records in table
		int numberOfRecords();

		record* getSpecificRecord(int index);

		//designate a single attribute as a key for a table
		void attributeKey(std::string attribute);

		//takes two tables as input and produces one table as output
		table* crossJoin(table table2);

		//both tables should have matching attribute keys
		table* naturalJoin(table table2);

		//returns the count based on a certain attribute
		int count(std::string attribute);

		//returns the index of the min based on a certain attribute
		int min(std::string attribute);

		//returns the index of the max based on a certain attribute
		int max(std::string attribute);

		// Todo: Remove after testing.
		void print();
		//
	};

	/**************

	database class

	**************/

	class db {
	private:
		std::vector<table*> tables;
		std::vector<std::string> names;

	public:
		db() {};
		//~db();

		void addTable(table* table1, std::string tableName);

		void dropTable(std::string tableName);

		void saveDatabase(std::string fileName);

		void loadDatabase(std::string fileName);

		std::vector<std::string> listTables();

		std::vector<table*> getTables();


		//SELECT, FROM, WHERE,
		table* query(std::vector<std::string> names, std::string tableName, std::string where);

		bool whereFunction(int index, table* fromTable, std::string input);
		bool evaluateComparison(int index, table* fromTable, std::string input);
		bool evaluateConditional(std::string conditional, std::string leftBool, std::string rightBool);
		std::vector<std::string> finalBool(std::vector<std::string> theTruth);


	};
}


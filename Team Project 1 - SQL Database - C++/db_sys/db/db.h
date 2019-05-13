#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <iostream>

namespace database {
	class table;
	class db {
	private:
		std::vector<table*> tables;
		std::vector<std::string> names;

	public:
		db();
		//~db();

		void addTable(table table1, std::string tableName);
		void dropTable(std::string tableName);
		void saveDatabase(std::string fileName);
		void loadDatabase(std::string fileName);

		std::vector<std::string> listTables();
		std::vector<table*> getTables();


		//SELECT, FROM, WHERE,
		table query(std::vector<std::string> names, std::string tableName, std::string where);

	};
	class record {
	private:
		//std::string name;
		std::vector<std::string> set;
		int numEntries;
	public:
		record(int size);
		int sizeofRecord(); //number of entries in the record
		std::string getEntry(int index);
		void setEntry(int index, std::string entry);

		void addElement(std::string element);
		void deleteElement(std::string element);
		// Todo: Remove after testing.
		void print();
		//
	};
	class table {


	private:
		int num_attr;
		std::map<std::string, int> attr_index;
		std::vector<record> records;
		std::vector<int*> keys;
	public:
		table();
		table(std::vector<std::string> names);
		void addAttribute(std::string attribute);
		void removeAttribute(std::string attribute);
		void addRecord(record rec);
		std::vector<std::string> getAttributes(); //returns list of all attributes in table

		int numberOfAttributes();
		int numberOfRecords(); //returns total number of records in table

		record getSpecificRecord(int index);

		void attributeKey(int index); //designate a single attribute as a key for a table

		//void renameAttribute(std::string name1, std::string name2);    //renames the attribute of name1 with name2

		//void specifyKey(std::string name); //takes in all attributes to create a key for the table

		void crossJoin(table secondTable); //takes two tables as input and produces one table as output

		void naturalJoin(table table2); //both tables should have matching attribute keys

		void attributeStats(std::string attribute);
		//returns min, max, count based on a certain attribute




		typedef std::vector<record>::iterator iterator;
		iterator begin();
		iterator end();

		// Todo: Remove after testing.
		void print();
		//
	};
}

#pragma once
#include "Record.h"
#include <iostream>
#include <vector>
#include <map>


class Table
{
	private:	
		std::vector<std::string> attributes;
		std::map<std::string, Record> records;
		std::vector<std::string> keys;
	public:
		Table();
		Table(std::vector<std::string> &_attributes);
		~Table();

		void add_attribute(std::string _attribute);
		void delete_attribute(std::string _attribute);
		void add_record(Record _record);

		const std::vector<std::string> &get_attributes() const;
		int get_table_size();

		typedef std::map<std::string, Record>::const_iterator recordIterator;
		recordIterator begin() const;
		recordIterator end() const;

		Record& find_record(std::string key);
		void assign_key(std::string _attribute);

		double count_entries(std::string _attribute);
		double min(std::string _attribute);
		double max(std::string _attribute);
		
};

Table * cross_join(Table &_table1, Table &_table2);
Table * natural_join(Table &_table, Table &_table2);

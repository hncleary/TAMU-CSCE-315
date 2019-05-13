#include "db.h"
#include <iostream>
#include <tuple>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>


namespace database {
	//database functions

	database::db::db()
	{
	}

	std::vector<std::string> database::db::listTables()
	{
		return this->names;
	}
	std::vector<table*> database::db::getTables()
	{
		return this->tables;
	}

	void database::db::addTable(table table1, std::string tableName)
	{
		std::cout << "Add a table" << std::endl;
		if (this->names.size() != this->tables.size()) {

			//Error should never occur
			//Code structure should prevent this error
			std::cout << "Error: Mismatched tables and names!" << std::endl;
			return;
		}
		//create pointer to table input
		table *tablepointer;
		tablepointer = &table1;

		this->names.push_back(tableName);
		this->tables.push_back(tablepointer);
	}
	void database::db::dropTable(std::string tableName)
	{
		std::cout << "delete a table from the database" << std::endl;
		int index = 0;
		bool nameFound = false;

		if (this->names.size() != this->tables.size()) {
			//Error should not occur
			//Code structure should prevent this error
			std::cout << "Error: Mismatched tables and names!" << std::endl;
			return;
		}
		for (index = 0; index < this->names.size(); index++) {

			if (this->names.at(index) == tableName) {

				nameFound = true;
				break;
			}
		}
		if (nameFound) {
			this->names.erase(this->names.begin() + index);
			this->tables.erase(this->tables.begin() + index);
		}
		else {

			std::cout << "Error: Table not found!" << std::endl;
		}
	}
	void database::db::saveDatabase(std::string fileName) {
		int rows = 0;
		int columns = 0;

		record* rec;

		std::vector <std::string> attributes;
		std::ofstream saveFile;

		saveFile.open(fileName);

		if (!saveFile.is_open()) {

			std::cout << "Error: File failed to open!" << std::endl;
			return;
		}

		for (int i = 0; i < this->names.size(); i++) {

			saveFile << "TABLE START," << names.at(i) << ",";

			rows = this->tables.at(i)->numberOfRecords();

			saveFile << rows << ",";

			columns = this->tables.at(i)->numberOfAttributes();

			saveFile << columns << "\n";

			table* t = ( this->tables.at(i) ) ;

			attributes = (* (this->tables.at(i)) ).getAttributes();

			for (int j = 0; j < attributes.size(); j++) {

				saveFile << attributes.at(i);

				if ((j + 1) != attributes.size()) {

					saveFile << ",";
				}
				else {

					saveFile << "\n";
				}
			}

			for (int k = 0; k < rows; k++) {

				rec = &(this->tables.at(i)->getSpecificRecord(k));

				for (int l = 0; l < columns; l++) {

					saveFile << rec->getEntry(l);

					if ((l + 1) != columns) {

						saveFile << ",";
					}
					else {

						saveFile << "\n";
					}
				}
			}

			saveFile << "TABLE END\n";
		}

		saveFile.close();
	}

	void database::db::loadDatabase(std::string fileName) {

		std::ifstream loadFile;

		loadFile.open(fileName);

		if (!loadFile.is_open()) {

			std::cout << "Error: File failed to open!" << std::endl;
			return;
		}

		tables.clear();
		names.clear();

		table* loadTable;
		record* loadRecord;

		int index = 0;
		int iRows;
		int iColumns;
		std::string buffer;
		std::string tableName;
		std::string sRows;
		std::string sColumns;
		std::string attribute;

		while (!loadFile.eof()) {

			loadTable = new table;

			//Following line unnecessary if table headers are removed
			getline(loadFile, buffer, ',');

			//Acquiring name of table
			getline(loadFile, tableName, ',');
			names.push_back(tableName);

			getline(loadFile, sRows, ',');
			iRows = stoi(sRows);

			getline(loadFile, sColumns);
			iColumns = stoi(sColumns);

			//Entering attributes of table
			for (int i = 0; i < iColumns; i++) {

				if (i + 1 != iColumns) {

					getline(loadFile, attribute, ',');
					loadTable->addAttribute(attribute);
				}
				else {

					getline(loadFile, attribute);
					loadTable->addAttribute(attribute);
				}
			}

			for (int i = 0; i < iRows; i++) {

				loadRecord = new record(iColumns);

				for (int j = 0; j < iColumns; j++) {

					if (j + 1 != iColumns) {

						getline(loadFile, attribute, ',');
						loadRecord->setEntry(j, attribute);
					}
					else {

						getline(loadFile, attribute);
						loadRecord->setEntry(j, attribute);
					}
				}
				//record loadedRecord();

				loadTable->addRecord(*loadRecord);
			}

			tables.push_back(loadTable);

			getline(loadFile, buffer);
			index++;
		}


		loadFile.close();
	}
	
	table database::db::query(std::vector<std::string> names, std::string tableName, std::string where)
	{
		std::cout << "Query the database" << std::endl;
		//select functionality
		if (names.at(0) == "*") {
			//keep all names
		}
		else if ( names.at(0) != "*") {
			//vector is the attributes to keep
		}
		//from functionalty
		//for (int i = 0; i < this->getTables.size(); i++) {}

		//where functionality

		return table();
	}

	//record functions
	record::record(int size) {
		std::vector<std::string> v;
		for (int i = 0; i < size; i++) {
			v.push_back("");
		};
		this->set = v;
		//outputs if the vector wasn't set to the correct size
		if (this->set.size() == size) {
			std::cout << "Record has been set to size " << this->set.size() << "." << std::endl;
		}
		else {
			std::cout << "There was an error setting the record class to size" << size << "." << std::endl;
		}
	}
	int record::sizeofRecord() {
		//std::cout << "Return the size of record" << std::endl;
		//return private member numEntries
		return this->numEntries;
		return 0;
	}
	std::string database::record::getEntry(int index)
	{
		std::cout << "Returned Entry from Position " << index << ": " << std::endl;
		return this->set.at(index);
	}

	void database::record::setEntry(int index, std::string entry)
	{
		// set entry at index
		std::cout << "Setting entry to " << entry << " at index " << index << "." << std::endl;
		this->set.at(index) = entry;
		this->numEntries = this->numEntries + 1;
		/*
		if (index == 0) {
			this->name = entry;
		}
		*/
	}

	void database::record::addElement( std::string element)
	{
		this->set.push_back(element);
		numEntries++;
		std::cout << "Pushed back element " << element << " to the end of the record." << std::endl;
		std::cout << "The record set is now size " << this->set.size() << ". " << std::endl;

	}

	void database::record::deleteElement(std::string element)
	{
		//removes an element from the record
		std::vector<std::string> v = this->set;
		bool deleted = false;
		int index;
		for (int i = 0; i < v.size(); i++) {
			if (v.at(i) == element) {
				this->set.at(i) = "";
				deleted = true;
				index = i;
				/*
				if (i == 0) {
					this->name = "";
				}
				*/
				break;
			}
		}
		if (deleted) {
			this->numEntries = this->numEntries - 1;
			std::cout << "Entry " << element << " was deleted from the record at index " << index << ". There are now " << this->numEntries << " entries in the record. " << std::endl;
		}
		else {
			std::cout << "The entry was not in the record and therefore was not deleted." << " There are now " << this->numEntries << " entries in the record. " << std::endl;
		}

	}

	void database::record::print() {
		for (int i = 0; i < set.size(); i++) {
			std::cout << set.at(i) << "	";
		}
		std::cout << std::endl;
	}


	//table functions
	database::table::table()
	{
		num_attr = 0;
	}
	database::table::table(std::vector<std::string> names)
	{

		for (int i = 0; i < names.size(); i++) {
			this->attr_index[names.at(i)] = num_attr;
			num_attr++;
		}
	}
	void database::table::addAttribute(std::string attribute)
	{
		std::cout << "add attribute to table" << std::endl;
		attr_index[attribute] = num_attr;
		num_attr++;

		for (int i = 0; i < records.size(); i++) {
			records.at(i).addElement("");
		}

	}
	void database::table::removeAttribute(std::string attribute)
	{
		std::cout << "remove attribute from the table" << std::endl;
		

		if (attr_index.count(attribute) != 0) {
			int index = attr_index[attribute];

			// Check that the index is not a key.
			for (int i = 0; i < keys.size(); i++) {

				if (*keys.at(i) == index) {
					throw std::runtime_error("Attribute is a key.");
				}

			}

			for (int i = 0; i < records.size(); i++) {
				record* current_rec = &records.at(i);
				current_rec->deleteElement(current_rec->getEntry(index));
			}

			for (std::map<std::string, int>::iterator iter = attr_index.begin(); iter != attr_index.end(); iter++) {
				if (iter->second > index) {
					iter->second--;
				}
			}

			attr_index.erase(attribute);

		}

	}
	void database::table::addRecord(record rec)
	{
		std::cout << "add a record" << std::endl;

		if (rec.sizeofRecord() > num_attr) {
			for (int i = 0; i < records.size(); i++) {
				for (int j = 0; j < (rec.sizeofRecord() - num_attr); j++) {
					records.at(i).addElement("");
				}
			}
		}
		else if (rec.sizeofRecord() < num_attr) {
			for (int i = 0; i < num_attr; i++) {
				rec.addElement("");
			}
		}

		records.push_back(rec);

	}
	std::vector<std::string> database::table::getAttributes()
	{
		std::cout << "Get the Attributes in the table" << std::endl;
		//return std::vector<std::string>();
		std::vector<std::string> attributes(attr_index.size());
		for (std::map<std::string, int>::iterator iter = attr_index.begin(); iter != attr_index.end(); iter++) {
			//attributes.push_back(iter->first);
			attributes.at(iter->second) = iter->first;
		}

		return attributes;
	}
	int database::table::numberOfAttributes() {
		return num_attr;
	}
	int database::table::numberOfRecords()
	{
		std::cout << "Function to get number of records" << std::endl;
		//return 0;

		return records.size();
	}
	record database::table::getSpecificRecord(int index)
	{
		std::cout << "Find Record in Specific Index" << std::endl;

		//return record(0);
		return records.at(index);
	}
	void database::table::attributeKey(int index)
	{
		std::cout << "assign attribute key" << std::endl;
		

		// Check that there are no repeated elements.
		std::vector<std::string> elements;
		for (int i = 0; i < records.size(); i++) {
			elements.push_back(records.at(i).getEntry(index));
		}
		std::sort(elements.begin(), elements.end());

		for (int i = 0; i < elements.size() - 1; i++) {
			if (elements.at(i) == elements.at(i + 1)) {
				throw std::runtime_error("Elements are not unique.");
			}
		}

		// If there are no repeated elements, add the index to the keys vector.
		for (auto iter = attr_index.begin(); iter != attr_index.end(); iter++) {
			if (iter->second == index) {
				keys.push_back(&(iter->second));
				return;
			}
		}

		// If the index was not found, throw an error.
		throw std::runtime_error("Attribute index not valid.");
	}
	void database::table::crossJoin(table secondTable)
	{
		//add clause that btoh tables must not have alike attributes


		// Add attributes.
		std::vector<std::string> second_attr = secondTable.getAttributes();
		std::vector<std::string> firstAtttributes = this->getAttributes();
		bool compatible = true;
		
		for (int i = 0 ; i < second_attr.size(); i++) {
			for (int j = 0 ; j < firstAtttributes.size(); j++) {
				std::cout << i << j << std::endl;
				if (firstAtttributes.at(j) == second_attr.at(i)) {
					compatible = false;
				}
			}
		}
		
	if(compatible) {

		int attr_i = num_attr;
		for (int i = 0; i < second_attr.size(); i++) {
			attr_index[second_attr.at(i)] = attr_i;
			attr_i++;
		}

		// Add records
		std::vector<record> new_records;
		for (int i = 0; i < records.size(); i++) {
			for (table::iterator iter = secondTable.begin(); iter != secondTable.end(); iter++) {
				record rc0 = records.at(i);

				for (int j = 0; j < iter->sizeofRecord(); j++) {
					rc0.addElement(iter->getEntry(j));
				}

				new_records.push_back(rc0);
			}
		}
		records.clear();
		for (int i = 0; i < new_records.size(); i++) {
			records.push_back(new_records.at(i));
		}
	}
	else {
		std::cout << "Cannot cross join tables with a set of equal attributes" << std::endl;
	}

	}

	void database::table::naturalJoin(table table2)
	{
		std::cout << "Natural Join Function" << std::endl;

		// Contains the initial version of attr_index. This will be used later.
		std::map<std::string, int> initial_index = attr_index;

		// Find common attributes.

		std::vector<std::string> other_attr = table2.getAttributes();

		std::vector<std::string> common;
		for (std::map<std::string, int>::iterator iter = attr_index.begin(); iter != attr_index.end(); iter++) {

			for (int i = 0; i < other_attr.size(); i++) {

				if (attr_index.count(other_attr.at(i)) != 0) {
					common.push_back(other_attr.at(i));
				}

			}

		}

		// Set up map containing elements of second table.
		std::map<std::string, int> table2_map;
		for (int i = 0; i < other_attr.size(); i++) {
			table2_map[other_attr.at(i)] = i;
		}





		// Add attributes.
		std::vector<std::string> second_attr = table2.getAttributes();

		for (int i = 0; i < second_attr.size(); i++) {

			std::cout << "ATTRIBUTE: " << second_attr.at(i) << std::endl;
			if (attr_index.count(second_attr.at(i)) == 0) {
				attr_index[second_attr.at(i)] = num_attr;
				num_attr++;
			}
		}

		// Add records
		std::vector<record> new_records;

		for (int i = 0; i < records.size(); i++) {

			for (table::iterator iter = table2.begin(); iter != table2.end(); iter++) {

				record rc0 = records.at(i);

				for (int j = 0; j < iter->sizeofRecord(); j++) {

					// Check that attribute is not common.

					if (initial_index.count(other_attr.at(j)) == 0) {
						rc0.addElement(iter->getEntry(j));
					}

				}

				// Check that common attributes return the same value.
				bool push = true;

				for (int j = 0; j < common.size(); j++) {

					if (rc0.getEntry(attr_index[common.at(j)]) != iter->getEntry(table2_map[common.at(j)])) {
						push = false;
					}

				}


				if (push) {
					new_records.push_back(rc0);
				}

			}


		}

		records.clear();
		for (int i = 0; i < new_records.size(); i++) {
			records.push_back(new_records.at(i));
		}




	}

	void database::table::attributeStats(std::string attribute)
	{
		std::cout << "Get stats for attributes" << std::endl;
		int index = attr_index[attribute];

		std::string min = records.at(0).getEntry(index);
		std::string max = records.at(0).getEntry(index);
		int count = 0;

		for (int i = 1; i < records.size(); i++) {
			if (records.at(i).getEntry(index) < min) {
				min = records.at(i).getEntry(index);
			}
			if (records.at(i).getEntry(index) > max) {
				max = records.at(i).getEntry(index);
			}
			if (records.at(i).getEntry(index) != "") {
				count++;
			}
		}

		std::cout << "Min: " << min << std::endl;
		std::cout << "Max: " << max << std::endl;
		std::cout << "Count: " << count << std::endl;

	}

	table::iterator database::table::begin() {
		return records.begin();
	}
	table::iterator database::table::end() {
		return records.end();
	}

	void database::table::print() {
		std::cout << "=============================================" << std::endl;
		std::vector<std::string> attr_names(attr_index.size());

		for (std::map<std::string, int>::iterator iter = attr_index.begin(); iter != attr_index.end(); iter++) {
			//std::cout << iter->first << "	";
			attr_names.at(iter->second) = iter->first;
		}

		for (int i = 0; i < attr_names.size(); i++) {
			std::cout << attr_names.at(i) << "	";
		}
		std::cout << std::endl;

		for (int i = 0; i < records.size(); i++) {
			records.at(i).print();
		}

		std::cout << "=============================================" << std::endl;

	}
}

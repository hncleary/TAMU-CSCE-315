#include "db.h"
#include <boost/regex.hpp>
#include <sstream>



namespace database {

	/******************************************

	Record class

	******************************************/

	record::record(int size) {

		for (int i = 0; i < size; i++) {

			rec.push_back("");
		}
	}

	int record::sizeofRecord() {

		int entries = 0;

		for (int i = 0; i < rec.size(); i++) {

			if (rec.at(i) != "") {

				entries++;
			}
		}

		return entries;
	}

	int record::capacity() {

		return rec.size();
	}

	std::string record::getEntry(int index) {

		if (index < rec.size()) {

			return rec.at(index);
		}
		else {

			std::cout << "Entry out of range." << std::endl;
			return "";
		}
	}

	void record::setEntry(int index, std::string entry) {

		if (index < rec.size()) {

			rec.at(index) = entry;
		}
		else {

			std::cout << "Index out of range." << std::endl;
		}
	}

	void record::addEntry(std::string entry) {

		rec.push_back(entry);
	}

	void record::print() {

		for (int i = 0; i < rec.size(); i++) {

			std::cout << rec.at(i) << "/t";
		}

		std::cout << std::endl << std::endl;
	}

	/******************************************

	Table class

	******************************************/

	table::table(std::vector <std::string> names) {

		for (int i = 0; i < names.size(); i++) {

			attributes.push_back(names.at(i));
		}
	}

	void table::addAttribute(std::string attribute) {

		attributes.push_back(attribute);

		for (int i = 0; i < records.size(); i++) {

			records.at(i)->addEntry("");
		}
	}

	void table::removeAttribute(std::string attribute) {

		for (int i = 0; i < attributes.size(); i++) {

			if (attributes.at(i) == attribute) {

				attributes.erase(attributes.begin() + i);
				break;
			}
		}
	}

	void table::addRecord(record* rec) {

		records.push_back(rec);
	}

	std::vector <std::string> table::getAttributes() {

		return attributes;
	}

	int table::numberOfAttributes() {

		return attributes.size();
	}

	int table::numberOfRecords() {

		return records.size();
	}

	record* table::getSpecificRecord(int index) {

		if (records.size() <= index) {

			std::cout << "Error: requested record is out of range." << std::endl;
			std::cout << "Returning an empty record" << std::endl;
			return new record;
		}

		return records.at(index);
	}

	void table::attributeKey(std::string attribute) {

		for (int i = 0; i < attributes.size(); i++) {

			if (attributes.at(i) == attribute) {

				keys.push_back(i);
				return;
			}
		}
	}

	table* table::crossJoin(table table2) {

		
		table* crossTable = new table;

		std::vector <std::string> table2Attr = table2.getAttributes();
		std::vector <std::string> table1Attr = this->getAttributes();

		bool compatible = true;

		for (int i = 0; i < table2Attr.size(); i++) {

			for (int j = 0; j < table1Attr.size(); j++) {

	
				if (table1Attr.at(j) == table2Attr.at(i)) {

					compatible = false;
				}
			}
		}

		if (!compatible) {

			std::cout << "Returning empty table, tables are not compatible." << std::endl;

			return crossTable;
		}

		//Adding all attributes
		for (int i = 0; i < attributes.size(); i++) {

			crossTable->addAttribute (attributes.at(i));
		}

		for (int i = 0; i < table2.numberOfAttributes(); i++) {

			crossTable->addAttribute (table2Attr.at(i));
		}

		//Creating space for required records
		for (int i = 0; i < (table2.numberOfRecords() * this->numberOfRecords()); i++) {

			crossTable->addRecord(new record);
		}

		//Adding all records to crossTable
		record* oldRecord;
		int index = 0;

		for (int i = 0; i < this->numberOfRecords(); i++) {

			for (int j = 0; j < table2.numberOfRecords(); j++) {

				oldRecord = records.at(i);

				for (int k = 0; k < oldRecord->capacity(); k++) {

					crossTable->getSpecificRecord(index)->addEntry(oldRecord->getEntry(k));
				}

				oldRecord = table2.getSpecificRecord(j);

				for (int k = 0; k < oldRecord->capacity(); k++) {

					crossTable->getSpecificRecord(index)->addEntry(oldRecord->getEntry(k));
				}

				index++;
			}
		}

		return crossTable;
	}

	table* table::naturalJoin(table table2) {

		return new table;
	}

	int table::count(std::string attribute) {

		int index = 0;
		int count = 0;
		bool attributeNotFound = true;

		for (int i = 0; i < attributes.size(); i++) {

			if (attributes.at(i) == attribute) {

				attributeNotFound = false;
				index = i;
				break;
			}
		}

		if (attributeNotFound) {

			std::cout << "No such attribute." << std::endl;
			return -1;
		}

		for (int i = 0; i < records.size(); i++) {

			if (records.at(i)->getEntry(index) != "") {

				count++;
			}
		}

		return count;
	}

	int table::min(std::string attribute) {

		int index;
		int minIndex = 0;
		std::string  minVal;
		bool attributeNotFound = true;

		for (int i = 0; i < attributes.size(); i++) {

			if (attributes.at(i) == attribute) {

				attributeNotFound = false;
				index = i;
				break;
			}
		}

		if (attributeNotFound) {

			std::cout << "No such attribute." << std::endl;
			return -1;
		}

		if (records.size() == 0) {

			std::cout << "No records." << std::endl;
			return -1;
		}

		minVal = records.at(0)->getEntry(index);

		for (int i = 0; i < records.size(); i++) {

			if (records.at(i)->getEntry(index) < minVal && records.at(i)->getEntry(index) != "") {

				minVal = records.at(i)->getEntry(index);
				minIndex = i;
			}
		}

		return minIndex;
	}

	int table::max(std::string attribute) {

		int index;
		int maxIndex = 0;
		std::string  maxVal;
		bool attributeNotFound = true;

		for (int i = 0; i < attributes.size(); i++) {

			if (attributes.at(i) == attribute) {

				attributeNotFound = false;
				index = i;
				break;
			}
		}

		if (attributeNotFound) {

			std::cout << "No such attribute." << std::endl;
			return -1;
		}

		if (records.size() == 0) {

			std::cout << "No records." << std::endl;
			return -1;
		}

		maxVal = records.at(0)->getEntry(index);

		for (int i = 0; i < records.size(); i++) {
			
			if (records.at(i)->getEntry(index) > maxVal && records.at(i)->getEntry(index) != "") {

				maxVal = records.at(i)->getEntry(index);
				maxIndex = i;
			}
		}

		return maxIndex;
	}

	void table::print() {

		for (int i = 0; i < attributes.size(); i++) {

			std::cout << attributes.at(i) << "    ";
		}

		std::cout << std::endl;

		for (int i = 0; i < records.size(); i++) {

			for (int j = 0; j < records.at(i)->capacity(); j++) {

				std::cout << records.at(i)->getEntry(j) << "    ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;
	}

	/******************************************

	Database class

	******************************************/

	void db::addTable(table* table, std::string tableName) {

		tables.push_back(table);
		names.push_back(tableName);
	}

	void db::dropTable(std::string tableName) {

		for (int i = 0; i < names.size(); i++) {

			if (tableName == names.at(i)) {

				names.erase(names.begin() + i);
				tables.erase(tables.begin() + i);
			}

			break;
		}
	}

	void db::saveDatabase(std::string fileName) {

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

			table* t = (this->tables.at(i));

			attributes = (*(this->tables.at(i))).getAttributes();

			for (int j = 0; j < attributes.size(); j++) {

				saveFile << attributes.at(j);

				if ((j + 1) != attributes.size()) {

					saveFile << ",";
				}
				else {

					saveFile << "\n";
				}
			}

			for (int k = 0; k < rows; k++) {

				rec = this->tables.at(i)->getSpecificRecord(k);

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

	void db::loadDatabase(std::string fileName) {

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

		while (getline(loadFile, buffer, ',')) {

			loadTable = new table;
			
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

				loadTable->addRecord(loadRecord);
			}

			tables.push_back(loadTable);

			getline(loadFile, buffer);
			index++;
		}


		loadFile.close();
	}

	std::vector <std::string> db::listTables() {

		return names;
	}

	std::vector<table*> db::getTables() {

		return tables;
	}

	table* db::query(std::vector <std::string> names, std::string tableName, std::string where) {

		table* queryTable = new table;
		table* fromTable;

		bool tableNotFound = true;
		int tableIndex;


		//FROM ARGUMENT

		//Determining index of table that contains the data to be queried
		for (int i = 0; i < this->names.size(); i++) {

			if (this->names.at(i) == tableName) {

				tableIndex = i;
				tableNotFound = false;
				break;
			}
		}

		//Error checking
		if (names.size() == 0 || tableNotFound) {

			//Returning an empty table
			std::cout << "Error: Empty table returned due to either select or from arguments." << std::endl;
			std::cout << "The table to be queried may not exist or no select arguments were passed in." << std::endl;
			return queryTable;
		}

		fromTable = tables.at (tableIndex);

		//SELECT ARGUMENT
		if (names.at(0) == "*") {

			std::vector <std::string> allAttributes = fromTable->getAttributes();

			for (int i = 0; i < allAttributes.size(); i++) {

				queryTable->addAttribute (allAttributes.at(i));
			}
		}
		else {

			for (int i = 0; i < names.size(); i++) {

				queryTable->addAttribute (names.at(i));
			}
		}
		/*
		o	Comparisons of =, <>, >, <, >=, <= (string comparisons)
		o   AND, OR, and NOT
		o	Parentheses. Parentheses can be nested.
		*/

		//WHERE ARGUMENT
		//need to utilize comparators on records within fromTable
		std::string input = where;
		int i = 0;
		while (i < input.size()) {
			if (input[i] == '(' || input[i] == ')')
			{
				input.erase(i, 1);
			}
			else {
				i++;
			}
		}

		bool keep = false;
		for (int i = 0; i < fromTable->numberOfRecords() ; i++) {
			keep = this->whereFunction(i, fromTable, input);
			//if true, keep --> else false, don't keep
			if (keep) {
				queryTable->addRecord(fromTable->getSpecificRecord(i));
			}
			else {
				//don't keep record lol
			}

		}



		return queryTable;
	}

	bool database::db::whereFunction(int index, table* fromTable, std::string input)
	{
		if (input == "") {
			return true;
		}
		//tokenize input
		std::vector<std::string> tokens;
		std::stringstream check1(input);
		std::string intermediate;
		while (getline(check1, intermediate, ' '))
		{
			tokens.push_back(intermediate);
		}
		//evaluate all comparisons
		std::vector<std::string> truthVector;

		for (int i = 0; i < tokens.size(); i++) {
			bool notAND = (tokens.at(i) != "AND" && tokens.at(i + 1) != "AND" && tokens.at(i + 2) != "AND");
			bool notOR = (tokens.at(i) != "OR" && tokens.at(i + 1) != "OR" && tokens.at(i + 2) != "OR");
			bool notNOT = (tokens.at(i) != "NOT" && tokens.at(i + 1) != "NOT" && tokens.at(i + 2) != "NOT");
			if (notAND && notOR && notNOT) {
				std::string compareTokens = tokens.at(i) + " " + tokens.at(i + 1) + " " + tokens.at(i + 2);
				bool evaluation = evaluateComparison(index, fromTable, compareTokens);
				if (evaluation) {
					truthVector.push_back("true");
				}
				else {
					truthVector.push_back("false");
				}
				//tokens.erase(tokens.begin() + i + 1, tokens.begin() + i + 2);
				i = i + 2;
			}
			if (tokens.at(i) == "AND") {
				truthVector.push_back("AND");
			}
			else if (tokens.at(i) == "NOT") {
				truthVector.push_back("NOT");

			}
			else if (tokens.at(i) == "OR") {
				truthVector.push_back("OR");
			}

		}
		//evaluate all NOTS
		std::vector<std::string> truthVector2;
		for (int j = 0; j < truthVector.size(); j++) {
			if (truthVector.at(j) == "NOT") {
				if (truthVector.at(j + 1) == "false") {
					truthVector2.push_back("true");
				}
				else if (truthVector.at(j + 1) == "true") {
					truthVector2.push_back("false");
				}
				j++;
			}
			else {
				truthVector2.push_back(truthVector.at(j));
			}
		}
		//evaluate remaining conditionals
		std::vector<std::string> finalTruthVector = finalBool(truthVector2);
		
		if (finalTruthVector.size() != 1) {
			std::cout << "There was a fatal error in the query function" << std::endl;	
		}
		else if (finalTruthVector.size() == 1) {
			if (finalTruthVector.at(0) == "true") {
				return true;
			}
			else if (finalTruthVector.at(0) == "false") {
				return false;
			}
			else {
				std::cout << "There was a fatal error in the query function" << std::endl;
			}
		}
	//default return
		return false;
	}
	std::vector<std::string> database::db::finalBool(std::vector<std::string> theTruth) {
		//recursive exit
		if (theTruth.size() == 1) {
			return theTruth;
		}
		//find first conditional
		std::vector<std::string> theNewTruth;
		for (int i = 0; i < theTruth.size(); i++) {
			bool firstBoolExists;
			bool secondBoolExists;
			bool conditionalExists;
			if (theTruth.at(i) == "false" || theTruth.at(i) == "true") {
				firstBoolExists = true;
			}
			else {firstBoolExists = false;}
			if (theTruth.at(i + 2) == "false" || theTruth.at(i + 2) == "true") {
				secondBoolExists = true;
			}
			else {secondBoolExists = false;}
			if (theTruth.at(i + 1) == "AND" || theTruth.at(i + 1) == "OR") {
				conditionalExists = true;
			}
			else {conditionalExists = false;}
			if (conditionalExists && firstBoolExists && secondBoolExists) {
				bool conditionalEval = evaluateConditional(theTruth.at(i + 1), theTruth.at(i), theTruth.at(i + 2));
				if (conditionalEval) {
					theNewTruth.push_back("true");
				}
				else {
					theNewTruth.push_back("false");
				}
				i = i + 2;
			}
			else {
				theNewTruth.push_back(theTruth.at(i));
			}
		}
		return finalBool(theNewTruth);
	}

	bool database::db::evaluateConditional(std::string conditional, std::string leftBool, std::string rightBool) {
		bool left;
		bool right;
		bool evaluation;
		if (leftBool == "false") {
			left = false;
		}
		else {
			leftBool = "true";
		}
		if (rightBool == "false") {
			right = false;
		}
		else {
			right = "true";
		}
		
		if (conditional == "AND") {
			evaluation = (left && right);
		}
		else if (conditional == "OR") {
			evaluation = (left || right);
		}
		return evaluation;
	}


	bool database::db::evaluateComparison(int index, table* fromTable, std::string input) {
		std::vector<std::string> tokens;
		std::stringstream check1(input);
		std::string intermediate;
		while (getline(check1, intermediate, ' '))
		{
			tokens.push_back(intermediate);
		}

		//get attribute index
		int attrIndex = 0;
		std::vector<std::string> listAttr = fromTable->getAttributes();
		for (int i = 0; i < listAttr.size(); i++) {
			if (listAttr.at(i) == tokens.at(0)) {
				attrIndex = i;
				break;
			}
		}

		if(tokens.at(1) == "<") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) < tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (tokens.at(1) == ">") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) > tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (tokens.at(1) == "=") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) == tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (tokens.at(1) == "<>") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) != tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (tokens.at(1) == ">=") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) >= tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (tokens.at(1) == "<=") {
			if (fromTable->getSpecificRecord(index)->getEntry(attrIndex) <= tokens.at(2)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

	}
}

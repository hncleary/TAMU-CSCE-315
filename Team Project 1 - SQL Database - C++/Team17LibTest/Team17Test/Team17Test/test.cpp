#include <iostream>
#include <cassert> 
#include <string>


#include "Record.h"
#include "Table.h"
#include "Database.h"

using namespace std;

class test_record {

public:
	test_record() {
	
	}


	void test_size() {

		int rSize = 10;

		Record r1;
		Record r2= Record(rSize);

		cout << "Testing size for a default constructor" << endl;
		assert(r1.size() == 0);

		cout << "Testing size for the constructor with a size passed in." << endl;
		assert(r2.size() == rSize);
	}

	void test_set_and_get() {

		int index = 2;
		string value = "test";

		Record r(10);
		r.set(index, value);

		string newVal = r.get(index);

		cout << "Testing set value compared to get value" << endl;
		assert(newVal == value);
	}
};

class test_table {

public:
	test_table() {

	}

	Table test;

	void test_add_delete_attribute(std::string _attribute) {

		Table test_table;

		test_table.add_attribute(_attribute);
		double one = 1;
		double zero = 0;
		assert( test_table.count_entries(_attribute) == one );

		test_table.delete_attribute(_attribute);
		assert( test_table.count_entries(_attribute) == zero );

	}


	void test_add_record(Record _record) {

		string attribute = "attribute";
		int init_count = test.count_entries(attribute);
		test.add_record(_record);

		assert(test.count_entries(attribute) == init_count + 1);

	}


	void test_get_table_size() {

		Table temp_table;
		Record temp_record;

		temp_table.add_record(temp_record);
		assert(temp_table.get_table_size() == 1);

	}

	void test_iterator() {

		Table test_table;

		auto begin_iter = test_table.begin();
		auto end_iter = test_table.end();

		assert(begin_iter == end_iter);


		Record test_record;
		test.add_record(test_record);

		begin_iter = test_table.begin();
		end_iter = test_table.end();

		assert(begin_iter != end_iter);


	}

	void test_find_record() {

		Table test_table;
		Record test_record;
		test_record.set(0, "test");
		test_table.add_record(test_record);

		Record& found = test_table.find_record("test");
		assert( test_record.get(0) == found.get(0) );

	}

	void test_assign_key(std::string key) {


		Table test_table;
		Database db;
		db.add(test_table, "Test");



	}


	void test_count_entries() {

		Table test_table;
		test_table.add_attribute("attribute");
		Record test_record;

		test_table.add_record(test_record);

		assert(test_table.count_entries("attribute") == 1);
	

	}

	void test_min_max(string attribute) {

		double test_min = test.min(attribute);
		double test_max = test.max(attribute);

		assert(test_min <= test_max);

	}
	
	void test_cross_join(Table test1, Table test2) {

		Table * test3 = cross_join(test1, test2);
		int i = test1.get_table_size();
		int j = test2.get_table_size();
		assert(table3.get_table_size() == i * j);

	}

	void test_natural_join(Table test1, Table test2) {

		Table * test3 = natural_join(test1, test2);
		int i = test1.get_table_size();
		int j = test1.get_table_size();
		assert(test3.get_table_size() == i + j);

	}
	


};


int main() {
	Record record1;

	//table tests
	test_table testTable;
	testTable.test_add_delete_attribute("attribute");
	testTable.test_add_record(record1);
	testTable.test_get_table_size();
	testTable.test_iterator();
	testTable.test_find_record();
	testTable.test_assign_key("key");
	testTable.test_count_entries();
	testTable.test_min_max("attriute");

	//database tests 

	return 0;
}

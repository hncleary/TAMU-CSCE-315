#include "Record.h"
#include "Table.h"
#include "Database.h"

#include <vector>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

class test_Database {
public:
	void test_add_and_getTables() {
		
		string rt = "test";
		string rt1 = "test1";
		string rt2 = "test2";
		string rt3 = "test3";
		string key1 = "key1";
		string key2 = "key2";
		
		Database db;
		
		Record r(2);
		r.set(0, rt);
		r.set(1, rt1);
		
		Record r1(2);
		r1.set(0, rt2);
		r1.set(1, rt3);
		
		Table t;
		
		t.add_record(r);
		t.assign_key(key1);
		
		t.add_record(r1);
		t.assign_key(key2);
		
		cout << "Table added" << endl;
		
		db.add(t, "table");
		
		cout << "getTables called" << endl;
		vector<Table> tables = db.getTables();
		
		cout << "Testing size of vector" << endl;
		assert(tables.size() == 1);
		
		cout << "Testing record 1 entry 0" << endl;
		assert(tables.at(0).find_record(key1)->get(0) == rt);
		
		cout << "Testing record 1 entry 1" << endl;
		assert(tables.at(0).find_record(key1)->get(1) == rt1);
		
		cout << "Testing record 2 entry 0" << endl;
		assert(tables.at(0).find_record(key2)->get(0) == rt2);
		
		cout << "Testing record 2 entry 0" << endl;
		assert(tables.at(0).find_record(key2)->get(1) == rt3);
		
		cout << "add and getTables of class Database work!" << endl;
	}
	
	void test_drop() {
		
		string rt = "test";
		string rt1 = "test1";
		string rt2 = "test2";
		string rt3 = "test3";
		string key1 = "key1";
		string key2 = "key2";
		
		Database db;
		
		Record r(2);
		r.set(0, rt);
		r.set(1, rt1);
		
		Record r1(2);
		r1.set(0, rt2);
		r1.set(1, rt3);
		
		Table t;
		
		t.add_record(r);
		t.assign_key(key1);
		
		t.add_record(r1);
		t.assign_key(key2);
		
		cout << "Table added" << endl;
		
		db.add(t, "table");
		
		cout << "Table dropped" << endl;
		
		db.drop("table");
		
		vector<Table> tables = db.getTables();
		
		assert(tables.size() == 0);
		
		cout << "Table dropped properly" << endl;
	}
	
	void test_save_and_load() {
		
		string rt = "test";
		string rt1 = "test1";
		string rt2 = "test2";
		string rt3 = "test3";
		string key1 = "key1";
		string key2 = "key2";
		
		Database db;
		Database db1;
		
		string file = "test.csv";
		ifstream saveFile;
		
		Record r(2);
		r.set(0, rt);
		r.set(1, rt1);
		
		Record r1(2);
		r1.set(0, rt2);
		r1.set(1, rt3);
		
		Table t;
		
		t.add_record(r);
		t.assign_key(key1);
		
		t.add_record(r1);
		t.assign_key(key2);
		
		db.add(t, "table");
		db1.add(t, "table");
		
		cout << "Testing save" << endl;
		
		db.save(file);
		
		saveFile.open(file);
		
		assert(!saveFile.fail());
		
		cout << "File created" << endl;
		
		cout << "Testing load" << endl;
		
		db.drop("table");
		
		db.load(file);
		
		vector<Table> tables1 = db.getTables();
		vector<Table> tables2 = db1.getTables();
		
		assert(tables1.size() == 1);
		assert(tables2.at(0).find_record (key1)->get(0) == tables1.at(0).find_record (key1)->get(0));
		
		cout << "Load succeeded" << endl;
	}
	
	void test_listTable() {
		
		string rt = "test";
		string rt1 = "test1";
		string rt2 = "test2";
		string rt3 = "test3";
		string key1 = "key1";
		string key2 = "key2";
		
		Database db;
		
		Record r(2);
		r.set(0, rt);
		r.set(1, rt1);
		
		Record r1(2);
		r1.set(0, rt2);
		r1.set(1, rt3);
		
		Table t;
		
		t.add_record(r);
		t.assign_key(key1);
		
		t.add_record(r1);
		t.assign_key(key2);
		
		db.add(t, "table");
		
		std::cout << "Testing listTable" << endl;
		
		vector<string> tables = db.listTable();
		
		assert(tables.size() == 0);
		assert(tables.at(0) == "table");
		
		std::cout << "listTable succeeded" << endl;
	}
	
	void test_query() {
		
		string r1t1 = "Hicham";
		string r1t2 = "Noureddine";
		string r1t3 = "Steve";
		
		string r2t1 = "1";
		string r2t2 = "2";
		string r2t3 = "3";
		
		string key1 = "Name";
		string key2 = "Place";
		
		string tableKey = "1600m";
		
		Record r1(3);
		Record r2(3);
		
		Table t;
		Database db;
		
		r1.set(0, r1t1);
		r1.set(1, r1t2);
		r1.set(2, r1t3);
		
		r2.set(0, r2t1);
		r2.set(1, r2t2);
		r2.set(2, r2t3);
		
		t.add_record(r1);
		t.assign_key(key1);
		
		t.add_record(r2);
		t.assign_key(key2);
		
		db.add(t, tableKey);
		
		
		Table newTable;
		
		newTable = db.query("Name, Place", tableKey, "");
		
		cout << "Query test 1" <<endl;
		
		assert(newTable == t);
		
		newTable = db.query("Name", tableKey, "Place = 1");
		
		Record r3(1);
		r3.set(0, r1t1);
		
		Table t1;
		t1.add_record(r3);
		t1.assign_key(key1);
		
		cout << "Query test 2" <<endl;
		
		assert(t1 == newTable);
		
		newTable = db.query("*", tableKey, "Place >= 1");
		
		cout << "Query test 3" <<endl;
		
		assert(newTable == t);
		
		newTable = db.query("*", tableKey, "Place > 1");
		
		Record r4(2);
		r4.set(0, r1t2);
		r4.set(1, r1t3);
		
		Record r5(2);
		r5.set(0, r2t2);
		r5.set(1, r2t3);
		
		Table t2;
		t2.add_record(r4);
		t2.assign_key(key1);
		t2.add_record(r5);
		t2.assign_key(key2);
		
		cout << "Query test 4" <<endl;
		
		assert(t2 == newTable);
		
		newTable = db.query("Name, count_entries(*)", tableKey, "Place < 3");
		
		Record r6(2);
		r6.set(0, r1t1);
		r6.set(1, r1t2);
		
		Record r7(2);
		r7.set(0, "1");
		r7.set(1, "1");
		
		Table t3;
		t2.add_record(r6);
		t2.assign_key(key1);
		t2.add_record(r7);
		t2.assign_key("count_entries");
		
		cout << "Query test 5" <<endl;
		
		assert(t2 == newTable);
		
		newTable = db.query("*", tableKey, "Place <= 3");
		
		cout << "Query test 6" <<endl;
		
		assert(t == newTable);
		
		cout << "Query testing finished" <<endl;
	}
};

int main() {
	
	test_Database tests;
	
	tests.test_add_and_getTables();
	
	tests.test_drop();
	
	tests.test_save_and_load();
	
	tests.test_listTable();
	
	tests.test_query();
}

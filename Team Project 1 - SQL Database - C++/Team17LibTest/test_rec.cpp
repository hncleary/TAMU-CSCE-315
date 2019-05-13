#include <iostream>
#include <cassert> 
#include <string>

#include "Record.h"

using namespace std;

class test_record {

public:
	test_record() {

	}


	void test_size() {

		int rSize = 10;

		Record r1;
		Record r2 = Record(rSize);

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

int main() {
	
	//record tests
	//in test_rec.cpp
	test_record tests;
	Record record1;
	tests.test_size();
	tests.test_set_and_get();
}

#include "db.h"
#include "stdlib.h"
#include <iostream>

using namespace database;
int main() {
	// First table.
	table students;
	students.addAttribute("Name");
	students.addAttribute("School");


	record rc0(2);
	rc0.setEntry(0, "Joe Smith");
	rc0.setEntry(1, "Rice");

	record rc1(2);
	rc1.setEntry(0, "Jill Smith");
	rc1.setEntry(1, "LSU");

	record rc2(2);
	rc2.setEntry(0, "Sam Jones");
	rc2.setEntry(1, "Texas A&M");

	record rc3(2);
	rc3.setEntry(0, "Sue Jones");
	rc3.setEntry(1, "Rice");

	students.addRecord(rc0);
	students.addRecord(rc1);
	students.addRecord(rc2);
	students.addRecord(rc3);

	students.print();

	// Second table.
	table schoolLocations ;
	schoolLocations.addAttribute("School");
	schoolLocations.addAttribute("City");

	record rc4(2);
	rc4.setEntry(0, "Texas A&M");
	rc4.setEntry(1, "College Station");

	record rc5(2);
	rc5.setEntry(0, "Rice");
	rc5.setEntry(1, "Houston");

	record rc6(2);
	rc6.setEntry(0, "LSU");
	rc6.setEntry(1, "Baton Rouge");

	schoolLocations.addRecord(rc4);
	schoolLocations.addRecord(rc5);
	schoolLocations.addRecord(rc6);

	schoolLocations.print();

	students.naturalJoin(schoolLocations);
	students.print();

	db database;

	database.addTable(students, "students");
	database.dropTable("students");
	
	database.addTable(students, "students");
	database.addTable(schoolLocations, "schoolLocations");

	std::vector<std::string> v = database.listTables();
	std::vector<table*> t = database.getTables();

	std::cout << v.size() << "==" << t.size() << std::endl;

	for (int i = 0; i < v.size(); i++) {
		std::cout << i + 1 << ": " << v.at(i) << std::endl;
	}
	
	//database.saveDatabase("dbfile.csv");

	 //record r = database.getTables().at(1)->getSpecificRecord( 0 );

	 /*
	std::cout << test.size() << std::endl;
	for (int i = 0; i < test.size(); i++) {
		std::cout << test.at(i) << std::endl;
	}
	*/


	system("pause");
}

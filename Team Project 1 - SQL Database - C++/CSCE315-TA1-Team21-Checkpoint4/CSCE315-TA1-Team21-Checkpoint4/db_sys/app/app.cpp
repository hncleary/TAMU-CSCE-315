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

	students.addRecord(&rc0);
	students.addRecord(&rc1);
	students.addRecord(&rc2);
	students.addRecord(&rc3);

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

	schoolLocations.addRecord(&rc4);
	schoolLocations.addRecord(&rc5);
	schoolLocations.addRecord(&rc6);

	schoolLocations.print();

	students.naturalJoin(schoolLocations)->print();
	students.print();

	db database;
	db database2;

	database.addTable(&students, "students");
	database.dropTable("students");
	
	database.addTable(&students, "students");
	database.addTable(&schoolLocations, "schoolLocations");
	
	database.saveDatabase("dbfile.csv");

	database2.loadDatabase("dbfile.csv");
	database2.saveDatabase("db2file.csv");

	 /*
	std::cout << test.size() << std::endl;
	for (int i = 0; i < test.size(); i++) {
		std::cout << test.at(i) << std::endl;
	}
	*/

	students.print();

	std::vector<std::string> names = students.getAttributes();
	table* testQuery = database.query(names, "students", "City = Houston AND NOT City = Houston");
	table* testQuery2 = database.query(names, "students", "NOT School = Rice");

	testQuery->print();
	testQuery2->print();

	system("pause");
}

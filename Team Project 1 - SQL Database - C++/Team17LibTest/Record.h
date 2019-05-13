#pragma once

#include <string>
#include <vector>

class Record
{
private:
	std::vector<std::string> entries;
public:
	Record();
	Record(int size);
	~Record();
	int size();
	void set(int entry, std::string value);
	std::string get(int entry);
};

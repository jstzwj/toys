#pragma once

#include<map>
#include<string>
#include"sqlite3.h"
class dictionary
{
public:
	void readFromFile(const std::string & filepath);
	std::wstring search(const std::wstring & word);
public:
	dictionary();
	~dictionary();
private:
	sqlite3 * handle;
};


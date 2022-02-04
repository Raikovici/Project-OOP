#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
class iQuery;
class QueryResult;
class Parser
{
private:
	std::map<iQuery*, QueryResult*> results;
	Parser();
	virtual ~Parser(){}

	static Parser* instance;
public:
	static Parser& getInstance(){}
	void print(){}
	void addPair(){}
	static void destroyInstance(){}
};


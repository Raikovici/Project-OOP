#pragma once
#include "CQuery.h"
#include "QueryWithoutCondition.h"
#include <string>
#include <vector>

using namespace std;
//DROP DATABASE/TABLE <name>
class CDataBase;

class QueryDrop : public QueryWithoutCondition
{
private:
	std::string typeStructure;
	
	
	void setTypeStr(std::string name) { typeStructure = name; }
	std::string getTypeStr() { return typeStructure; }

public:
	QueryDrop(std::string query = "") : QueryWithoutCondition(query) {}
	QueryDrop(string s, vector<string> tokens) : QueryWithoutCondition(s, tokens) {}

	void additionals(){}
	void interpret() override {}
	string executee(vector<CDataBase*> vect_bd, string databaseName);
	void executeDropTabel(CDataBase* bd, string tabelName);

	QueryResult* execute() override { return nullptr; }
    
	virtual ~QueryDrop() {}
};


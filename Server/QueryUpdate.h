#pragma once

//UPDATE table_name
//SET column1 = value, column2 = value2, ...
//WHERE some_column = some_value
#include "QueryWithCondition.h"
using namespace std;
class CDataBase;
class iField;

class QueryUpdate: public QueryWithCondition
{
private:
	std::vector<iField*> fields;
	std::vector<std::string> values;
public:
	QueryUpdate(std::string s = "") : QueryWithCondition(s){}
	QueryUpdate(string s, vector<string> tokens) : QueryWithCondition(s, tokens) {}
	QueryResult* execute() override { return nullptr; }
	void executee(CDataBase* bd, string tableName);
	void alterTable(CDataBase* bd, string tableName);
	void interpret() override {}
	void additionals() override {}
	virtual ~QueryUpdate(){}
};


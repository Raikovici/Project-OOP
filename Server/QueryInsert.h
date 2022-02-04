#pragma once
#include "QueryWithoutCondition.h"
#include <vector>
#include <string>
using namespace std;

//INSET INTO table_name (field1, field2, field3, ...)
//VALUES (value1, value2, value3, ...)

class iField;
class CDataBase;
class CTable;

class QueryInsert : public QueryWithoutCondition
{
private:
	std::vector<iField*> fields;
	std::vector<std::string> values;
public:
	QueryInsert(std::string s = "") : QueryWithoutCondition(s){}
	QueryInsert(string s, vector<string> tokens) : QueryWithoutCondition(s, tokens) {}
	QueryResult* execute() override { return nullptr; }

	void executee(CDataBase* bd, string numeTable);
	void interpret() override{}
	void additionals() override{}
	virtual ~QueryInsert(){}
};


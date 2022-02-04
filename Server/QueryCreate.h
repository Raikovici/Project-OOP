#pragma once
#include "QueryWithoutCondition.h"


class QueryCreate : public QueryWithoutCondition
{
protected:
	std::string typeStructure;
	void setFileByStructure(){}
	void setTypeStr(std::string name) { typeStructure = name; }
	std::string getTypeStr() { return typeStructure; }
public:
	QueryCreate() {};
	QueryCreate(std::string query) : QueryWithoutCondition(query) {}
	QueryCreate(string s, vector<string> tokens) : QueryWithoutCondition(s, tokens) {}

	void additionals(){}
	virtual ~QueryCreate(){}
};


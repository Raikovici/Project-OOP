#pragma once
#include "CQuery.h"
#include "QueryWithCondition.h"
using namespace std;

//#include "Condition.h"
//DELETE FROM <table_name> WHERE <condition>
class Condition;
class CDataBase;

class QueryDelete : public QueryWithCondition
{
private:

public:
	QueryDelete(std::string s = "") : QueryWithCondition(s) { ; }
	QueryDelete(string s, vector<string> tokens) : QueryWithCondition(s, tokens) {}
	void interpret() override{}
	QueryResult* execute() override{ return nullptr; }
	void executee(CDataBase* bd, string numeTabela);
	void additionals() override {}

	virtual ~QueryDelete(){}
};


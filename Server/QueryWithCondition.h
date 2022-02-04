#pragma once
#include "CQuery.h"
#include <string>
#include <vector>
using namespace std;

class Condition;
class QueryWithCondition : public CQuery
{
protected:

	std::string condition;
	Condition* C;

public:
	QueryWithCondition(std::string s = "") : CQuery(s) { ; }
	QueryWithCondition(string s, vector<string> tokens) : CQuery(s, tokens) {}

	void setCondition() {}

	virtual ~QueryWithCondition(){}
};


#pragma once
#include "CQuery.h"
#include <string>
#include <vector>
using namespace std;

class QueryWithoutCondition : public CQuery
{
protected:

public:
	QueryWithoutCondition() {}
	QueryWithoutCondition(std::string s) : CQuery(s){}

	QueryWithoutCondition(string s, vector<string> tokenss) : CQuery(s, tokenss){}



	virtual ~QueryWithoutCondition(){}
};


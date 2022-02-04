#pragma once
#include "iQuery.h"
#include "QueryResult.h"
#include <vector>
#include <string>
using namespace std;

class CQuery : public iQuery
{
protected:
	std::string query;
	std::vector<std::string> tokens;

	std::string nameTable;
	QueryResult* R;
public:
	CQuery();
	CQuery(std::string s);
	CQuery(string s, vector<string> tokenss);

	void setName(std::string s) override;
	std::string getName() override;

	// Neimplementate
	string getPartOfQuery(int i) override;
	virtual QueryResult* execute() override { return nullptr; }
	virtual void interpret () override {}
	virtual void additionals() override {}


	
	void tokenize() override;
	void print() override;
	std::vector<std::string> getTokens() override { return this->tokens; }

	virtual void setNameTable(std::string s) { this->nameTable = s; }
	
	virtual ~CQuery(){}
};


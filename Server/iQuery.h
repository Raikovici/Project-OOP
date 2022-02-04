#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <iostream>
#include <string>
using namespace std;

class QueryResult;
class CDataBase;
class iQuery
{
public:
	virtual void setName(std::string s) = 0;
	virtual string getName() = 0;
	virtual QueryResult* execute() = 0;
	virtual string getPartOfQuery(int i) = 0;

	virtual void tokenize() = 0;
	virtual void print() = 0;
	virtual void interpret() = 0;
	virtual void additionals() = 0;
	virtual vector<string> getTokens() = 0;
};


class GenerateQueries
{
public:
	static iQuery* getSelectQuery(std::string s, CDataBase* C);

	static iQuery* getInsertQuery(std::string s, vector<string> tokens);
	static iQuery* getCreateDBQuery(std::string s, vector<string> tokens);
	static iQuery* getCreateTableQuery(std::string s, vector<string> tokens);
	static iQuery* getUpdateQuery(std::string s, vector<string> tokens);
	static iQuery* getDeleteQuery(std::string s, vector<string> tokens);
};
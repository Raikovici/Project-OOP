#pragma once
#include "QueryCreate.h"
#include <string>
#include <iostream>

using namespace std;

class CDataBase;

//CREATE DATABASE <name>
class QueryCreateDB : public QueryCreate
{

public:
	QueryCreateDB() { this->query = "nimic"; }
	QueryCreateDB(string s, vector<string> tokens) : QueryCreate(s, tokens) {}

	QueryResult* execute() override { return nullptr; };
	CDataBase* executee();

	void interpret() override;

	virtual ~QueryCreateDB(){}
};


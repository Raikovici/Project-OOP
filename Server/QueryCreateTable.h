#pragma once
#include "QueryCreate.h"

//CREATE TABLE <name> (
// field_1 type_field constraint,
// field_2 type_field constraint,
// field_3 type_field constraint,
// ..
// ..
// field_n type_field constraint)

#include <string>
#include <vector>
using namespace std;

class iField;
class CTable;
class CDataBase;

class QueryCreateTable : public QueryCreate
{
private:
	std::vector<iField*> fields; //setare de valoare, tip, constrangere
	int nrFields;
	
	void addField(iField*){}
	int getNrFields() { return nrFields; }

public:
	QueryCreateTable(std::string s = "") : QueryCreate(s) { nrFields = 0; }
	QueryCreateTable(string s, vector<string> tokenss) : QueryCreate(s, tokenss) { nrFields = 0; }
	
	QueryResult* execute() override;
	CTable* executee(CDataBase* bd);
	void interpret() override {}

	virtual ~QueryCreateTable() {}

};


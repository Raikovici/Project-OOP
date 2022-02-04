#pragma once
#include "QueryWithCondition.h"
#include "Condition.h"
//SELECT <cols> FROM <table> WHERE <condition> ORDER BY <order>

class QueryResult;
class CTable;
class CDataBase;

class QuerySelect : public QueryWithCondition
{
private:
	std::vector<std::string> vectCols;
	std::vector<std::string> clauses;
	std::string orderMode;
	CTable* tableForSelect;
	CDataBase* usedDB;

	std::string colForOrder;
	std::string order;
	void setCols();
	void setTable();
	void setCondition();
	void setOrder();
	void setClauses();
	std::string getAny(std::string example, std::string s1, std::string s2);
	std::string getfinal(std::string example, std::string wanted);
	bool respectCondition(std::string s, string type);

public:
	QuerySelect(std::string query, CDataBase* D);
	void interpret() override;
	QueryResult* execute() override;
	void additionals() override {}
	virtual ~QuerySelect() {}
};


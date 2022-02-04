#include "iQuery.h"
#include "QuerySelect.h"
#include "QueryCreateDB.h"
#include "QueryCreateTable.h"
#include "QueryInsert.h"
#include "QueryDelete.h"
#include "QueryUpdate.h"


iQuery* GenerateQueries::getSelectQuery(std::string s, CDataBase* C)
{
	return new QuerySelect(s, C);
}

iQuery* GenerateQueries::getInsertQuery(std::string s, vector<string> tokens)
{
	return new QueryInsert;
}

iQuery* GenerateQueries::getCreateDBQuery(std::string s, vector<string> tokens )
{
	return new QueryCreateDB(s,tokens);
}

iQuery* GenerateQueries::getCreateTableQuery(std::string s, vector<string> tokens)
{
	return new QueryCreateTable(s, tokens);
}

iQuery* GenerateQueries::getUpdateQuery(std::string s, vector<string> tokens)
{
	return new QueryUpdate;
}

iQuery* GenerateQueries::getDeleteQuery(std::string s, vector<string> tokens)
{
	return new QueryDelete;
}

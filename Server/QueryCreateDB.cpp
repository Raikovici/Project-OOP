#include "QueryCreateDB.h"
#include "CDataBase.h"
#include <fstream>
using namespace std::string_literals;

CDataBase* QueryCreateDB::executee()
{
	string nameDB = this->getPartOfQuery(2);

	CDataBase* BD = new CDataBase(nameDB);

	BD->createFile();

	return BD;
}

void QueryCreateDB::interpret()
{

}
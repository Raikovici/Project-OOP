#include "CRelationship.h"
#include "CTable.h"
#include "CField.h"
CRelationship::CRelationship()
{
	this->foreignTable = new CTable();
	this->foreign = new CField();
}

CRelationship::CRelationship(CTable* t, CField* f)
{
	this->foreignTable = new CTable(*t);
	this->foreign = new CField(*f);
}

CTable* CRelationship::getTable()
{
	return this->foreignTable;
}

CField* CRelationship::getField()
{
	return this->foreign;
}

CRelationship::~CRelationship()
{
	if (!this->foreign)
		delete this->foreign;
	if (!this->foreignTable)
		delete this->foreignTable;
}

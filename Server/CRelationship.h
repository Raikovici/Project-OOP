#pragma once
class CTable;
class CField;
class CRelationship
{
private:
	CField* foreign;
	CTable* foreignTable;
public:
	CRelationship();
	CRelationship(CTable* t, CField* f);
	CTable* getTable();
	CField* getField();
	virtual ~CRelationship();
};


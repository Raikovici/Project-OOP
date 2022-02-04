#include "CField.h"
//int CField::increment = 1;

CField::CField(std::string name, TipCamp tip)
{
	this->nume = name;
	this->tip = tip;
	this->not_allow_Null = false;
	this->foreignKey = false;
	this->primaryKey = false;
	this->size_fix = false;
	this->auto_increment = false;
	this->size = 0;
	this->increment = 1;
}

CField::CField(string name)
{
	this->nume = name;

	this->not_allow_Null = false;
	this->foreignKey = false;
	this->primaryKey = false;
	this->size_fix = false;
	this->auto_increment = false;
	this->size = 0;
	this->increment = 1;
}

CField::CField(const CField& C)
{
	this->nume = C.nume;
	this->not_allow_Null = C.not_allow_Null;
	this->foreignKey = C.foreignKey;
	this->primaryKey = C.primaryKey;
	this->tip = C.tip;
	this->size_fix = C.size_fix;
	this->size = C.size;
	this->increment = C.increment;
}

void CField::setSize(int s)
{
	this->size = s;
}

void CField::setPrimaryKey()
{
	this->primaryKey = true;
}

void CField::setForeignKey()
{
	this->foreignKey = true;
}

void CField::setNotAllowNull()
{
	this->not_allow_Null = true;
}

void CField::setAutoIncrement()
{
	this->auto_increment = true;
}
void CField::AddIncrement()
{
	this->increment++;
}

void CField::setTip(std::string tip)
{
	if (tip == "VARCHAR" || tip == "varchar")
	{
		this->tip = TipCamp::varchar;
	}
	if (tip == "INT" || tip == "int")
	{
		this->tip = TipCamp::integer;
	}
	if (tip == "DATA" || tip == "data")
	{
		this->tip = TipCamp::datatype;
	}
	if (tip == "DOUBLE" || tip == "double")
	{
		this->tip = TipCamp::cuVirgula;
	}
	if (tip == "INTEGER" || tip == "integer")
	{
		this->tip = TipCamp::integer;
	}
}

void CField::setNume(std::string nume)
{
	this->nume = nume;
}

bool CField::getPrimaryKey()
{
	return this->primaryKey;
}

bool CField::getForeignKey()
{
	return this->foreignKey;
}
bool CField::getAutoIncremet()
{
	return auto_increment;
}
bool CField::getNotAllowNull()
{
	return this->not_allow_Null;
}

bool CField::getFixedSize()
{
	return this->size_fix;
}

std::string CField::getName()
{
	return this->nume;
}

int CField::getSize()
{
	return this->size;
}
int CField::getIncrement()
{
	return increment;
}
TipCamp CField::getCamp()
{
	return this->tip;
}

std::string CField::getTip()
{
	std::string s;
	if (tip == TipCamp::varchar)
	{
		s = "VARCHAR";
		return s;
	}
	if (tip == TipCamp::integer)
	{
		s = "INTEGER";
		return s;
	}
	if (tip == TipCamp::datatype)
	{
		s = "DATA";
		return s;
	}
	if (tip == TipCamp::cuVirgula)
	{
		s = "DOUBLE";
		return s;
	}
}

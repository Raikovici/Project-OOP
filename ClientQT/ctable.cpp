#include "ctable.h"

CTable::CTable()
{

}
CTable::CTable(const CTable& C)
{
    this->numeTabel = C.numeTabel;
    this->res = C.res;
    this->fields = C.fields;
}

void CTable::setNume(std::string s)
{
    this->numeTabel = s;
}

std::string CTable::getNume()
{
    return this->numeTabel;
}

void CTable::setRes(std::string s)
{
    this->res = s;
}

std::string CTable::getRes()
{
    return this->res;
}

void CTable::setFields(std::string s)
{
    this->fields = s;
}

std::string CTable::getFields()
{
    return this->fields;
}

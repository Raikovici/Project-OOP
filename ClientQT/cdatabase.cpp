#include "cdatabase.h"
#include "ctable.h"
#include <vector>
#include <string>

CDataBase::CDataBase()
{

}

void CDataBase::setName(std::string s)
{
    this->name = s;
}

void CDataBase::setLoc(std::string l)
{
    this->location = l;
}
void CDataBase::setPath(std::string s)
{
    this->filepath = s;
}

std::string CDataBase::getName()
{
    return this->name;
}

std::string CDataBase::getLoc()
{
    return this->location;
}
std::string CDataBase::getPath()
{
    return this->filepath;
}
void CDataBase::addTable(CTable *t)
{
    this->tables.push_back(t);
}

CTable* CDataBase::getTable(int pos)
{
    return this->tables[pos];
}

void CDataBase::deleteTable(std::string name)
{
    int i = 0, pos = 0;
    auto it = this->tables.begin();
    while(it != this->tables.end())
    {
        i = 0;
        if((*it)->getNume() == name)
        {
            pos = i;
        }
        i++;
        it++;
    }
    auto it1 = this->tables.begin();
    this->tables.erase(it1 + pos);
}

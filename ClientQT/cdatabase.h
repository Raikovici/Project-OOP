#ifndef CDATABASE_H
#define CDATABASE_H

#include <iostream>
#include <vector>
class CTable;
class CDataBase
{
private:
    std::string name;
    std::string location;
    std::vector<CTable*> tables;
    std::string filepath;
public:
    CDataBase();
    void setName(std::string s);
    void setPath(std::string s);
    void setLoc(std::string l);
    void addTable(CTable* t);
    CTable* getTable(int pos);
    void deleteTable(std::string name);
    std::string getName();
    std::string getLoc();
    std::string getPath();
};

#endif // CDATABASE_H

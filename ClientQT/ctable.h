#ifndef CTABLE_H
#define CTABLE_H

#include <iostream>
class CTable
{
private:
    std::string numeTabel;
    std::string res;
    std::string fields;
public:
    CTable();
    CTable(const CTable&);
    void setNume(std::string s);
    std::string getNume();
    void setRes(std::string s);
    std::string getRes();
    void setFields(std::string s);
    std::string getFields();
};

#endif // CTABLE_H

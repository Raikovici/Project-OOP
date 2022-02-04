#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef enum class TipCamp
{
	byDefault, varchar, integer, datatype, cuVirgula
};
class CField
{
private:
	std::string nume;
	bool primaryKey;
	bool foreignKey;
	bool not_allow_Null;
	int size;
	bool size_fix;
	bool auto_increment;
	//static int increment;
	int increment;
	TipCamp tip;

public:
	CField() : CField("NULL", TipCamp::byDefault) {}
	CField(std::string name, TipCamp tip);
	CField(string name);
	CField(const CField& C);


	void setSize(int s);
	void setPrimaryKey();
	void setForeignKey();
	void setNotAllowNull();
	void setAutoIncrement();
	void AddIncrement();
	void setTip(std::string tip);
	void setNume(std::string nume);

	bool getPrimaryKey();
	bool getForeignKey();
	bool getAutoIncremet();
	bool getNotAllowNull();
	bool getFixedSize();

	std::string getName();

	int getSize();
	int getIncrement();

	TipCamp getCamp();
	std::string getTip();

	virtual ~CField() {}

};


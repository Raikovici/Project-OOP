#pragma once
#include "IException.h"
class CException : public IException
{
protected:
	std::string name;
	int code;
	void setName(std::string) override {}
	void setCode(int i) override{}
	std::string getName() override{}
	int getCode() override{}
public:
	CException(){}
	virtual ~CException(){}
};


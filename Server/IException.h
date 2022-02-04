#pragma once
#include <iostream>
#include <string>
class IException
{
public:
	virtual void setName(std::string) = 0;
	virtual void setCode(int i) = 0;
	virtual std::string getName() = 0;
	virtual int getCode() = 0;
};


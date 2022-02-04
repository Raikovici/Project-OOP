#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
class Condition
{
private:
	std::string condition;
	std::string left, right, op;
public:

	Condition(std::string c = "") : condition(c) {}
	void setCond(std::string s);
	std::string getRight();
	std::string getLeft();
	std::string getOP();


	void setOperands();

	virtual ~Condition(){}
};


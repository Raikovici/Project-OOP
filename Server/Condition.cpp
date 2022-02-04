#include "Condition.h"
void Condition::setCond(std::string s)
{
	condition = s;
}
std::string Condition::getRight()
{
	return right;
}
std::string Condition::getLeft()
{
	return left;
}
std::string Condition::getOP()
{
	return op;
}
void Condition::setOperands()
{
	std::string token = "";
	std::string delim = " ";
	int i = 0;
	auto start = 0u;
	auto end = condition.find(delim);
	while (end != std::string::npos)
	{
		token = condition.substr(start, end - start);
		start = end + delim.length();
		end = condition.find(delim, start);
		if (token != "")
		{
			if (i == 0)
			{
				left = token;
			}
			if (i == 1)
			{
				op = token;
			}
			i++;
		}
	}
	if (condition[condition.size() - 1] == ' ')
	{
		if (token != "")
		{
			right = token;
		}
	}
	else
	{
		token = condition.substr(start, end);
		if (token != "")
		{
			right = token;
		}
	}
}

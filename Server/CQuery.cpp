#include "CQuery.h"
using namespace std;

CQuery::CQuery()
{
	R = new QueryResult();
}
CQuery::CQuery(std::string s)
{
	this->query = s;
}
CQuery::CQuery(string s, vector<string> tokenss)
{
	this->query = s;
	for (int i = 0; i < tokenss.size(); i++)
		this->tokens.push_back(tokenss[i]);

	R = new QueryResult();
}
void CQuery::setName(std::string s)
{
	this->query = s;
}
std::string CQuery::getName()
{
	return this->query;
}
string CQuery::getPartOfQuery(int i)
{
	return this->tokens[i];
}

void CQuery::tokenize()
{
	// Facem tot upper ca sa ne fie mai usor de verificat ce tip de interogare avem
	std::transform(this->query.begin(), this->query.end(), this->query.begin(),[](unsigned char c) { return std::toupper(c); });

	std::string delim = " ";
	std::string token = "";
	auto start = 0u;
	auto end = query.find(delim);
	while (end != std::string::npos)
	{
		token = query.substr(start, end - start);
		tokens.push_back(token);
		start = end + delim.length();
		end = query.find(delim, start);
	}
	token = query.substr(start, end);
	tokens.push_back(token);

	for (int k = 0; k < tokens.size(); k++)
		if (tokens[k] == "")
		{
			tokens.erase(tokens.begin() + k);
			k--;
		}
}

void CQuery::print()
{
	for (auto it = tokens.begin(); it != tokens.end(); it++)
	{
		std::cout << *it << " ";
	}
}

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>
using namespace std;

class QueryResult     
{
private:
	std::string mesaj_succes;
	std::vector<std::vector<std::string>> result;
	int codeSucceded;

	int lines;
public:

	QueryResult() { lines = 0, codeSucceded = 0; }
	QueryResult(std::vector<std::vector<std::string>> res);
	QueryResult(string msj) { this->mesaj_succes = msj; }

	void setCode(int t) { codeSucceded = t; }
	std::vector<std::vector<std::string>> getContinut() { return result; }
	int getCode() { return codeSucceded; }
	string getMesajSucces() { return mesaj_succes; }
	virtual ~QueryResult() { ; }
};


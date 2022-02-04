#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
using namespace std;
class CTable;

class CDataBase
{
private:
	std::vector<CTable*> tables;
	std::string name;
	std::string filename;
	int nr;
public:
	CDataBase() : CDataBase(""){}
	CDataBase(std::string name);
	void rename(std::string newName);
	void addTable(CTable* tabel);
	void deleteTable(CTable* tabel);
	void printFile();
	void createFile();
	void deleteFile();
	string getName() { return this->name; }
	void setName(std::string s);
	std::vector<CTable*> getTabele();
	CTable* getCertainTable(string name);
	bool ExistsTable(string name);
	void loadDB();
	virtual ~CDataBase();
};


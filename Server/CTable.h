#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CField;
class CRelationship;

class CTable
{
private:
	std::string tableName;
	std::string filename;
	std::vector<CField*> fields;
	std::vector<CRelationship*> relations;
	std::vector<vector<std::string>> records;
	int lines = 0;
	int nrFields = 0;
public:
	CTable() : CTable(""){}
	CTable(std::string name);
	CTable(const CTable& T);

	std::string getName();
	void deleteFile();
	void addField(CField* C);
	void addFieldNou(string numeField, string numeTipCamp);
	void deleteField(CField* C);
	void addRelation(CTable* T, CField* F);
	void deleteRelation(CTable* T, CField* F);
	void deleteRecord(int i);
	void addRecord(std::vector<std::string> record);
	void updateRecord(int indexRecord, int indexField, string semn, string newValue);
	void printInFile();
	void deleteFieldName(string name);
	CField* getCertainField(string numeField);
	bool searchExistaValoareIntrodusa(int nrCamp, string valoare);
	void loadTable();
	vector<vector<string>> getRecords() { return records; }
	string getFileName() { return filename; }
	int getNrFields() { return nrFields; }
	vector<CField*> getFields() { return fields; }
	int getSize() { return records.size(); }
	virtual ~CTable();
};


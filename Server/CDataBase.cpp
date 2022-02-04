#include "CDataBase.h"
#include "CTable.h"
#include <fstream>

CDataBase::CDataBase(std::string name)
{
	this->name = name;
	this->filename = this->name + ".txt";
	this->nr = 0;
}

void CDataBase::rename(std::string newName)
{
	this->name = newName;
}

void CDataBase::addTable(CTable* tabel)
{
	this->tables.push_back(tabel);

	this->printFile();
}

void CDataBase::deleteTable(CTable* tabel)
{
	int pos = 0;
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i]->getName() == tabel->getName())
			pos = i;
	}
	tables.erase(tables.begin() + pos);
}

void CDataBase::printFile()
{
	ofstream outfile;
	outfile.open(this->filename);

	for (int i = 0; i < tables.size(); i++)
	{
		if(tables[i]->getFileName() != "")
		outfile << tables[i]->getFileName() << endl;
	}
	
	outfile.close();
}

void CDataBase::createFile()
{
	ofstream file(name + ".txt");
	file.close();
}

void CDataBase::deleteFile()
{

	int a = remove(filename.c_str());
	if (a == 1)
	{
		cout << "Fisierul bazei de date: " + filename + " nu s-a putut sterge!\n";
	}
	else
	{
		cout << "Fisierul bazei de date: " + filename + " s-a sters cu succes!\n";
	}
}
void CDataBase::setName(std::string s)
{
	this->name = s; this->filename = s + ".txt";
}
std::vector<CTable*> CDataBase::getTabele()
{
	return this->tables;
}

CTable* CDataBase::getCertainTable(string name)
{
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i]->getName() == name)
			return tables[i];
	}
	return nullptr;
}

bool CDataBase::ExistsTable(string name)
{
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i]->getName() == name)
			return true;
	}
	return false;
}

void CDataBase::loadDB()
{
	std::ifstream file;
	file.open(filename);
	string line = "";
	int nrLines = 0;
	while (!file.eof())
	{
		getline(file, line);
		if (line != "")
		{
			int pos = line.find('.');
			string s = line.substr(0, pos);
			CTable* tab = new CTable(s);
			tab->loadTable();
			tables.push_back(tab);
		}
	}
}

CDataBase::~CDataBase()
{
	for (int i = 0; i < tables.size(); i++)
		if (tables[i] != nullptr)
		{
			tables[i]->deleteFile();
			tables[i]->~CTable();
			delete tables[i];
			tables[i] = nullptr;
		}

	this->tables.clear();

}

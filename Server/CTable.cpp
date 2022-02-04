#include "CTable.h"
#include "CField.h"
#include "CRelationship.h"
#include <fstream>
#include <vector>
#include <iomanip>

CTable::CTable(std::string name)
{
	this->tableName = name;
	this->lines = 0;
	this->nrFields = 0;
	this->filename = this->tableName + ".txt";
	std::cout << "\nTabel nou creat!\n";
}

CTable::CTable(const CTable& T)
{
	this->filename = T.filename;
	this->lines = T.lines;
	this->tableName = T.tableName;
	for (int i = 0; i < T.relations.size(); i++)
	{
		this->relations[i] = T.relations[i];
	}
	this->records.resize(T.records.size());
	for (int i = 0; i < T.records.size(); i++)
	{
		for (int j = 0; j < T.records[j].size(); j++)
		{
			this->records[i][j] = T.records[i][j];
		}
	}
}

std::string CTable::getName()
{
	return this->tableName;
}

void CTable::deleteFile()
{
	int a = remove(filename.c_str());
	if (a == 1)
	{
		cout << "Fisierul " + filename + " nu s-a putut sterge!\n";
	}
	else
	{
		cout << "Fisierul " + filename + " s-a sters cu succes!\n";
	}
}

void CTable::addField(CField* C)
{
	this->fields.push_back(C);
	this->nrFields++;
}

void CTable::addFieldNou(string numeField, string numeTipCamp)
{
	CField* field_nou = nullptr;

	if (numeTipCamp == "INTEGER" || numeTipCamp == "INT")
		field_nou = new CField(numeField, TipCamp::integer);

	if (numeTipCamp == "DOUBLE")
		field_nou = new CField(numeField, TipCamp::cuVirgula);

	if (numeTipCamp == "VARCHAR")
		field_nou = new CField(numeField, TipCamp::varchar);

	if (numeTipCamp == "DATATYPE")
		field_nou = new CField(numeField, TipCamp::datatype);

	if (field_nou != nullptr)
	{
		this->fields.push_back(field_nou);
		this->nrFields++;
	}
}

void CTable::deleteField(CField* C)
{
	int pos = 0;
	for (int i = 0; i < fields.size(); i++)
	{
		if (fields[i]->getName() == C->getName())
		{
			pos = i;
		}
	}
	fields.erase(fields.begin() + pos);

}

void CTable::addRelation(CTable* T, CField* F)
{
	CRelationship* R = new CRelationship(T, F);
	relations.push_back(R);
}

void CTable::deleteRelation(CTable* T, CField* F)
{
	int pos = 0;
	for (int i = 0; i < relations.size(); i++)
	{
		if (relations[i]->getTable()->getName() == T->getName() && relations[i]->getField()->getName() == F->getName())
		{
			pos = i;
		}
	}
	relations.erase(relations.begin() + pos);
}

void CTable::deleteRecord(int i)
{
	this->records.erase(records.begin() + i);
}

void CTable::addRecord(std::vector<std::string> record)
{
	records.push_back(record);
}

void CTable::updateRecord(int indexRecord, int indexField, string semn, string newValue)
{

	if (semn == "=")
	{
		this->records[indexRecord][indexField] = newValue;

	}

	if (semn == "+=" || semn == "=+")
	{
		if (this->fields[indexField]->getCamp() == TipCamp::integer)
		{
			int newValInt = stoi(newValue);
			int oldValInt = stoi(records[indexRecord][indexField]);
			int val = newValInt + oldValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}


		if (this->fields[indexField]->getCamp() == TipCamp::cuVirgula)
		{
			float newValInt = stof(newValue);
			float oldValInt = stof(records[indexRecord][indexField]);
			float val = newValInt + oldValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}

	}

	if (semn == "-=" || semn == "=-")
	{
		if (this->fields[indexField]->getCamp() == TipCamp::integer)
		{
			int newValInt = stoi(newValue);
			int oldValInt = stoi(records[indexRecord][indexField]);
			int val = oldValInt - newValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}


		if (this->fields[indexField]->getCamp() == TipCamp::cuVirgula)
		{
			float newValInt = stof(newValue);
			float oldValInt = stof(records[indexRecord][indexField]);
			float val = oldValInt - newValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}
	}

	if (semn == "*=" || semn == "=*")
	{
		if (this->fields[indexField]->getCamp() == TipCamp::integer)
		{
			int newValInt = stoi(newValue);
			int oldValInt = stoi(records[indexRecord][indexField]);
			int val = oldValInt * newValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}


		if (this->fields[indexField]->getCamp() == TipCamp::cuVirgula)
		{
			float newValInt = stof(newValue);
			float oldValInt = stof(records[indexRecord][indexField]);
			float val = oldValInt * newValInt;

			this->records[indexRecord][indexField] = to_string(val);
			
		}
	}

	if (semn == "/=" || semn == "=/")
	{
		if (this->fields[indexField]->getCamp() == TipCamp::integer)
		{
			int newValInt = stoi(newValue);
			int oldValInt = stoi(records[indexRecord][indexField]);
			int val = oldValInt / newValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}


		if (this->fields[indexField]->getCamp() == TipCamp::cuVirgula)
		{
			float newValInt = stof(newValue);
			float oldValInt = stof(records[indexRecord][indexField]);
			float val = oldValInt / newValInt;

			this->records[indexRecord][indexField] = to_string(val);
		}
	}

}

void CTable::printInFile()
{
	ofstream outfile(filename);


	for (int i = 0; i < nrFields - 1; i++)
		outfile << fields[i]->getName() << "     "; // 5 spatii intre campuri

	outfile << fields[nrFields - 1]->getName() << "\n";


	for (int i = 0; i < records.size(); i++)
	{
		for (int j = 0; j < records[i].size() - 1; j++)
			outfile << records[i][j] << "     "; // 5 spatii intre inregistrari


		outfile << records[i][records[i].size()-1] << "\n";
	}

	outfile.close();
}

void CTable::deleteFieldName(string name)
{
	int ok = 0;
	for (int i = 0; i < fields.size(); i++)
		if (fields[i]->getName() == name)
		{
			delete fields[i];
			fields.erase(fields.begin() + i);
			ok = 1;
			this->nrFields--;
			if (i < records[0].size())
			{
				for (int j = 0; j < records.size(); j++)  /// stergem si inregistrarea din dreptul campului respectiv
					records[j].erase(records[j].begin() + i);
			}
			break;
		}
	if (ok == 0)
		cout << "Campul " + name + " nu face parte din aceasta tabela!\n"; // throw exception
}

CField* CTable::getCertainField(string numeField)
{
	for (int i = 0; i < fields.size(); i++)
		if (fields[i]->getName() == numeField)
			return fields[i];

	return nullptr;
}

bool CTable::searchExistaValoareIntrodusa(int nrCamp, string valoare)
{
	for (int i = 0; i < this->records.size(); i++)
	{
		if (records[i][nrCamp] == valoare)
			return true;
	}
	return false;
}

void CTable::loadTable()
{
	std::ifstream file;
	file.open(filename);
	string token = "", delim = "     ", line = "";
	int nrLines = 0;
	while (!file.eof())
	{
		getline(file, line);
		if(line != "")
			nrLines++;
	}
	this->records.resize(nrLines - 1);
	file.clear();
	file.seekg(0);
	int i = 0, j = 0;
	line = "";
	while (!file.eof())
	{
		getline(file, line);
		if (line != "")
		{
			int pos = line.find(delim);
			while (pos != string::npos)
			{
				token = line.substr(0, pos);
				if (i == 0)
				{
					CField* fiel = new CField();
					fiel->setNume(token);
					fiel->setTip("varchar");
					this->addField(fiel);
				}
				else
				{
					records[j].push_back(token);

				}
				line.erase(0, pos + delim.length());
				pos = line.find(delim);
			}
			if (i == 0)
			{
				CField* fiel = new CField();
				fiel->setNume(line);
				fiel->setTip("varchar");
				this->addField(fiel);
			}
			else
			{
				records[j].push_back(line);
				j++;
			}
			i++;
			
		}
	}
}

CTable::~CTable()
{
	for (int i = 0; i < fields.size(); i++)
		if (fields[i] != nullptr)
		{
			delete fields[i];
			fields[i] = nullptr;
		}

	this->nrFields = 0;
	this->lines = 0;

	for (int i = 0; i < relations.size(); i++)
		if (relations[i] != nullptr)
		{
			delete relations[i];
			relations[i] = nullptr;
		}

	//cout << "Destructor table apelat!" << endl;

	records.clear();
	fields.clear();
	relations.clear();

}

#include "QueryCreateTable.h"
#include "CDataBase.h"
#include "CTable.h"
#include "CField.h"
#include <fstream>

QueryResult* QueryCreateTable::execute()
{
	

	return nullptr;
}

CTable* QueryCreateTable::executee(CDataBase* bd)
{
	
	string tmp = this->getPartOfQuery(2) + " " + this->getPartOfQuery(3) + " " + this->getPartOfQuery(4);
	
	if (tmp == "IF NOT EXISTS")
	{
		string numeTabela = this->getPartOfQuery(5);

		if (bd->ExistsTable(numeTabela) == true)
		{
			//throw exception
			cout << "Tabela deja exista!" << endl;
			
		}
		else
		{
			
			CTable* tabela = new CTable(numeTabela);

			for (int i = 6; i < this->tokens.size(); i++)
			{
				string token = this->getPartOfQuery(i);
				string keywords = "INTEGER DOUBLE NOT NULL VARCHAR DATE PRIMARY KEY";

				if (keywords.find(token) == string::npos)		// daca nu-l gaseste ca si cuvant cheie, atunci e NumeCamp
				{
					CField* temp = new CField(token);
					tabela->addField(temp);

				}
				else
				{
					if (token == "INTEGER")
						(tabela->getFields())[tabela->getNrFields() - 1]->setTip("int");
					
					if (token == "DOUBLE")
						(tabela->getFields())[tabela->getNrFields() - 1]->setTip("double");

					if (token == "VARCHAR")
						(tabela->getFields())[tabela->getNrFields() - 1]->setTip("VARCHAR");

					if (token == "DATE")
						(tabela->getFields())[tabela->getNrFields() - 1]->setTip("data");

					if(token == "NOT")
						(tabela->getFields())[tabela->getNrFields() - 1]->setNotAllowNull();
					
					if (token == "PRIMARY")
					{
						(tabela->getFields())[tabela->getNrFields() - 1]->setPrimaryKey();
						(tabela->getFields())[tabela->getNrFields() - 1]->setNotAllowNull();
						(tabela->getFields())[tabela->getNrFields() - 1]->setAutoIncrement();
					}

					// mai putem adauga aici si ca field-ul sa aiba obligatoriu o anumita dimensiune
					// doar mai adaug un if + inca un KeyWord
				}

			}

			// creeaza fisierul tabelei !!
			tabela->printInFile();

			return tabela;
		}
		

	}
	else
	{
		//Throw exception
		cout << "Something is wrong with this Query, check the sintax near IF NOT EXISTS!" << endl;
	}

	return nullptr;
}

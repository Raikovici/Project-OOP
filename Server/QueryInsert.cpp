#include "QueryInsert.h"
#include "CTable.h"
#include "CDataBase.h"
#include "CField.h"

void QueryInsert::executee(CDataBase* bd, string numeTable)
{

	if (bd->ExistsTable(numeTable) == false)
		cout << "Tabela " + numeTable + " nu exista!\n"; // THROW exception!!
	else
	{
		CTable* temp = bd->getCertainTable(numeTable);
		vector<string> inregistrare;

		vector<string> coloane;
		vector<string> valori;

		int ok = 0;  // nu s-a gasit VALUES
		for (int i = 3; i < this->tokens.size(); i++)
		{
			if (this->getPartOfQuery(i) != "VALUES" && ok == 1)
				valori.push_back(this->getPartOfQuery(i));

			if (this->getPartOfQuery(i) != "VALUES" && ok == 0)
				coloane.push_back(this->getPartOfQuery(i));
				
			
			if (this->getPartOfQuery(i) == "VALUES")
				ok = 1;

		}

		for (int i = 0; i < temp->getFields().size(); i++)
		{
			inregistrare.push_back("    ");   // 4 spatii


			if (((temp->getFields()[i])->getAutoIncremet() == true) && ( (temp->getFields()[i]->getCamp()) == TipCamp::integer))
			{
				int inc = temp->getFields()[i]->getIncrement();
				temp->getFields()[i]->AddIncrement();

				inregistrare[i] = to_string(inc);
				continue;
			}


			for (int j = 0; j < coloane.size(); j++)
			{
				if ((temp->getFields()[i])->getName() == coloane[j])
				{
					if (temp->getFields()[i]->getPrimaryKey() == true)
					{
						if (temp->searchExistaValoareIntrodusa(i, valori[j]) == true)
						{
							cout << "Atentie!! " << valori[j] << " a mai fost introdusa, nu respecta conditia de PK!!\n" << endl;
							break;
						}
						else
						{
							inregistrare[i] = valori[j];
							break;
						}

					}
					else
					{
						inregistrare[i] = valori[j];
						break;
					}


					//if (temp->getFields()[i]->getCamp() == (TipCamp)'1' || temp->getFields()[i]->getCamp() == (TipCamp)'3')
						///inregistrare[i] = valori[j];

					//if (temp->getFields()[i]->getCamp() == (TipCamp)'4')
				}

				if ((temp->getFields()[i])->getName() != coloane[j] && temp->getFields()[i]->getNotAllowNull()==true && inregistrare[i] =="    "  && j == coloane.size()-1 )
				{
					cout << "ATENTIE!! Campul " << temp->getFields()[i]->getName() << " nu permite NULL!!" << endl; /// throw exception!!
					break;
				}
			}
		}

		temp->addRecord(inregistrare);

		temp->printInFile();

	}



}

#include "QueryUpdate.h"
#include "CDataBase.h"
#include "CTable.h"
#include "CField.h"
#include <vector>
#include <utility>
#include <iostream>

void QueryUpdate::executee(CDataBase* bd, string tableName)
{
	vector<pair<string, string>> camp_newVal;   // field + noua lui valoare in inregistrare
	vector<pair<string, string>> camp_oldVal;   // field + vechea lui valoare in inregistrare

	//vector<string> valori_vechi;

	//vector<string> valori_noi;
	//vector<string> campuri;

	vector<string> semne;
	vector<int> pozitii;
	int poz_where = 0;

	for (int i = 4; i < this->tokens.size(); i++)
		if (tokens[i] == "WHERE")
			poz_where = i;

	int nr_valori = (poz_where - 3) / 3;

	for (int i = 0; i < nr_valori; i++)
	{
		pair<string, string> newOne;
		newOne.first = tokens[3 + i * 3];
		semne.push_back(tokens[4 + i * 3]);
		newOne.second = tokens[5 + i * 3];

		camp_newVal.push_back(newOne);
	}

	for (int i = poz_where + 1; i < tokens.size(); i=i+4)
	{
		pair<string, string> newOne;
		newOne.first = tokens[i];
		newOne.second = tokens[i+2];
		camp_oldVal.push_back(newOne);

	}

	CTable* tmp = bd->getCertainTable(tableName);

	bool ok = 0;
	for (int i = 0; i < camp_oldVal.size(); i++)    // verific daca gaseste toate campurile
	{
		ok = 0;

		for (int k = 0; k < tmp->getFields().size(); k++)
			if (tmp->getFields()[k]->getName() == camp_oldVal[i].first)
			{
				ok = 1;
				pozitii.push_back(k);
			}

		if (ok == 0)
		{
			cout << "Campul: " + camp_oldVal[i].first + " nu face parte din aceasta tabela!\n" << endl;
			break;
		}
	}

	if (ok == 1)
	{
		for (int i = 0; i < tmp->getRecords().size(); i++)
		{
			bool ko = 1;

			for (int j = 0; j < camp_oldVal.size(); j++)
			{
				if (camp_oldVal[j].second != tmp->getRecords()[i][pozitii[j]] && tmp->getFields()[pozitii[j]]->getCamp() != TipCamp::cuVirgula)
					ko = 0;

				if (tmp->getFields()[pozitii[j]]->getCamp() == TipCamp::cuVirgula)
				{
					float a = stof(camp_oldVal[j].second);
					float b = stof(tmp->getRecords()[i][pozitii[j]]);

					if (a != b)
						ko = 0;
				}
			}


			if (ko == true)
			{
				for (int j = 0; j < camp_newVal.size(); j++)
				{
					for (int m = 0; m < tmp->getFields().size(); m++)
					{
						if (tmp->getFields()[m]->getName() == camp_newVal[j].first)
							tmp->updateRecord(i, m, semne[j], camp_newVal[j].second);
					}
				}
			}

		}
	}

	camp_newVal.clear();
	camp_oldVal.clear();
	semne.clear();
	pozitii.clear();

	tmp->printInFile();
}

void QueryUpdate::alterTable(CDataBase* bd, string tableName)
{
	string tipAlter = this->tokens[3];

	if (tipAlter == "ADD")
	{
		string numeField = tokens[4];
		string numeTipCamp = tokens[5];
		
		bd->getCertainTable(tableName)->addFieldNou(numeField,numeTipCamp);
	}

	if (tipAlter == "DROP")
	{
		string numeField = tokens[5];
		bd->getCertainTable(tableName)->deleteFieldName(numeField);
	}

	if (tipAlter == "MODIFY")
	{
		string numeField = tokens[5];
		string nouTipCamp = tokens[6];
		bd->getCertainTable(tableName)->getCertainField(numeField)->setTip(nouTipCamp);
	}

	bd->getCertainTable(tableName)->printInFile();
}
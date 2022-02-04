#include "QueryDelete.h"
#include "CDataBase.h"
#include "CTable.h"
#include "CField.h"
#include <utility>

void QueryDelete::executee(CDataBase* bd, string numeTabela)
{
	vector<string> valori;
	vector<string> campuri;
	vector<int> pozitii;
	int nr_and = 0;

	for (int i = 4; i < this->tokens.size(); i++)
		if (tokens[i] == "AND")
			nr_and++;
		

	campuri.push_back(tokens[4]);
	valori.push_back(tokens[6]);

	for (int i = 0; i < nr_and; i++)
	{
		campuri.push_back(tokens[8+i*4]);
		valori.push_back(tokens[10+i*4]);

	}

	CTable* tmp = bd->getCertainTable(numeTabela);

	bool ok = 0;
	for (int i = 0; i < campuri.size(); i++)    // verific daca gaseste toate campurile
	{
		ok = 0;

		for (int k = 0; k < tmp->getFields().size(); k++)
			if (tmp->getFields()[k]->getName() == campuri[i])
			{
				ok = 1;
				pozitii.push_back(k);
			}
			
		if (ok == 0)
		{
			cout << "Campul: " + campuri[i] + " nu face parte din aceasta tabela!\n" << endl;
			break;
		}
	}

	if (ok == 1)
	{
		for (int i = 0; i < tmp->getRecords().size(); i++)
		{
			bool ko = 1;

			for (int j = 0; j <valori.size(); j++)
				if (valori[j] != tmp->getRecords()[i][pozitii[j]])
					ko = 0;
				

			if (ko == true)
				tmp->deleteRecord(i);
				
		}
	}
	pozitii.clear();
	valori.clear();
	campuri.clear();

	tmp->printInFile();

}

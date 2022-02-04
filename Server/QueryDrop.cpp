#include "QueryDrop.h"
#include "CDataBase.h"
#include "CTable.h"

string QueryDrop::executee(vector<CDataBase*> vect_bd, string databaseName)
{
	for (int i = 0; i < vect_bd.size(); i++)
	{
		if (vect_bd[i]->getName() == databaseName)
		{
			vect_bd[i]->deleteFile();
			delete(vect_bd[i]);
			vect_bd.erase(vect_bd.begin() + i);
			i--;
			return "succes";

		}
	}
	return "Baza de date " + databaseName + " nu a fost gasita!\n";

}

void QueryDrop::executeDropTabel(CDataBase* bd, string tabelName)
{
	for (int i = 0; i < bd->getTabele().size(); i++)
	{
		if ((bd->getTabele()[i])->getName() == tabelName)
		{
			(bd->getTabele()[i])->deleteFile();
			bd->getTabele()[i]->~CTable();
			bd->getTabele()[i] = nullptr;
			i--;
			break;
		}
	}
	bd->printFile();
}

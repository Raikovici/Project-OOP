#include "QuerySelect.h"
#include "CTable.h"
#include "CDataBase.h"
#include "Condition.h"
#include "QueryResult.h"
#include "CField.h"
#include <algorithm>
using namespace std::string_literals;
QuerySelect::QuerySelect(std::string query, CDataBase* D) : QueryWithCondition(query)
{
	setClauses();
	usedDB = new CDataBase(*D);
	std::transform(this->query.begin(), this->query.end(), this->query.begin(), [](unsigned char c) { return std::toupper(c); });
}

void QuerySelect::setClauses()
{
	clauses.push_back("SELECT");
	clauses.push_back("FROM");
	clauses.push_back("WHERE");
	clauses.push_back("ORDER BY");
}

std::string QuerySelect::getAny(std::string example, std::string s1, std::string s2)
{
	std::string any = "(.*)";
	std::regex cols(s1 + any + s2);
	std::smatch match;
	std::string matched;
	if (std::regex_search(example, match, cols))
	{
		if (match.size() == 2)
			matched = match[1].str();
	}
	return matched;
}

std::string QuerySelect::getfinal(std::string example, std::string wanted)
{
	int pos = example.find(wanted);
	std::string last = example.substr(pos + wanted.length(), query.size());
	return last;
}
void QuerySelect::setTable()
{
	string name;
	if (query.find(clauses[2]) != std::string::npos)
	{
		std::string matched = getAny(query, clauses[1], clauses[2]);
		name = matched;
		name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
		this->nameTable = name;
	}
	else
	{
		name = getfinal(query, clauses[1]);

		int pos = name.find(clauses[3]);

		if (pos != std::string::npos)
		{
			string str;
			str = name.substr(0, pos);
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
			this->nameTable = str;
		}
		else
		{
			name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
			this->nameTable = name;
		}
	}


	tableForSelect = usedDB->getCertainTable(nameTable);
}
void QuerySelect::setCols()
{
	std::string cols = getAny(this->query, clauses[0], clauses[1]);
	if (cols.find("*") != std::string::npos)
	{
		for (int i = 0; i < tableForSelect->getNrFields(); i++)
		{
			vectCols.push_back(tableForSelect->getFields()[i]->getName());
		}
	}
	else
	{
		std::string token = "", delim = " ";
		auto start = 0u;
		auto end = cols.find(delim);
		while (end != std::string::npos)
		{
			token = cols.substr(start, end - start);
			token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
			token.erase(std::remove(token.begin(), token.end(), ','), token.end());
			if (token != "")
			{
				vectCols.push_back(token);
			}
			start = end + delim.length();
			end = cols.find(delim, start);
		}
		token = cols.substr(start, end);
		if (token != "")
		{
			vectCols.push_back(token);
		}

	}
}
void QuerySelect::setCondition()
{

	if (query.find(clauses[3]) != std::string::npos)
	{
		std::string matched = getAny(query, clauses[2], clauses[3]);
		this->condition = matched;
	}
	else
	{
		this->condition = getfinal(query, clauses[2]);
	}
	C = new Condition();
	C->setCond(condition);
	C->setOperands();
}
void QuerySelect::setOrder()
{
	this->orderMode = getfinal(query, clauses[3]);
	std::string token = "", delim = " ";
	auto start = 0u;
	auto end = orderMode.find(delim);
	while (end != std::string::npos)
	{
		token = orderMode.substr(start, end - start);
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		if (token != "")
		{
			colForOrder = token;
		}
		start = end + delim.length();
		end = orderMode.find(delim, start);
	}
	token = orderMode.substr(start, end);
	if (token != "")
	{
		order = token;
	}
}



void QuerySelect::interpret()
{
	this->setTable();			// seteaza nume tabel, ia tot ce gaseste intre where si from
	this->setCols();
	if (query.find(clauses[2]) != std::string::npos) //daca exista WHERe
	{
		this->setCondition();
	}
	if (query.find(clauses[3]) != std::string::npos)
	{
		this->setOrder();
	}

	/*for (auto it = vectCols.begin(); it != vectCols.end(); it++)
	{
		std::cout << *it << " ";
	}*/
	std::cout << "\n";
	std::cout << orderMode << "\n";

}

bool QuerySelect::respectCondition(std::string s, string type)
{
	std::string operat = C->getOP();
	if (type == "INT" || type == "INTEGER")
	{
		if (operat == ">")
		{
			if (std::stoi(s) > std::stoi(C->getRight()))
				return true;
		}
		else if (operat == "<")
		{
			if (std::stoi(s) < std::stoi(C->getRight()))
				return true;
		}
		else if (operat == "=")
		{
			if (std::stoi(s) == std::stoi(C->getRight()))
				return true;
		}
		else if (operat == "!=")
		{
			if (std::stoi(s) != std::stoi(C->getRight()))
				return true;
		}
		else if (operat == ">=")
		{
			if (std::stoi(s) >= std::stoi(C->getRight()))
				return true;
		}
		else if (operat == "<=")
		{
			if (std::stoi(s) <= std::stoi(C->getRight()))
				return true;
		}
	}
	else if (type == "VARCHAR" || type == "varchar")
	{
		if (operat == "=")
		{
			if (s == C->getRight())
				return true;
		}
		else if (operat == "!=")
		{
			if (s != C->getRight())
				return true;
		}
		else if (operat == "<")
		{
			if (isdigit(s[0]))
			{
				if (s.find('.') != string::npos)
				{
					if (stod(s) < stod(C->getRight()))
						return true;
				}
				else
				{
					if (stoi(s) < stoi(C->getRight()))
						return true;
				}
				
			}
		}
		else if (operat == ">")
		{
			if (isdigit(s[0]))
			{
				if (s.find('.') != string::npos)
				{
					if (stod(s) > stod(C->getRight()))
						return true;
				}
				else
				{
					if (stoi(s) > stoi(C->getRight()))
						return true;
				}

			}
		}
		else if (operat == "<=")
		{
			if (s.find('.') != string::npos)
			{
				if (stod(s) <= stod(C->getRight()))
					return true;
			}
			else
			{
				if (stoi(s) <= stoi(C->getRight()))
					return true;
			}
		}
		else if (operat == ">=")
		{
			if (s.find('.') != string::npos)
			{
				if (stod(s) >= stod(C->getRight()))
					return true;
			}
			else
			{
				if (stoi(s) >= stoi(C->getRight()))
					return true;
			}
		}
	}
	else if (type == "DOUBLE" || type == "double")
	{
		if (operat == ">")
		{
			if (std::stod(s) > std::stod(C->getRight()))
				return true;
		}
		else if (operat == "<")
		{
			if (std::stod(s) < std::stod(C->getRight()))
				return true;
		}
		else if (operat == "=")
		{
			if (std::stod(s) == std::stod(C->getRight()))
				return true;
		}
		else if (operat == "!=")
		{
			if (std::stod(s) != std::stod(C->getRight()))
				return true;
		}
		else if (operat == ">=")
		{
			if (std::stod(s) >= std::stod(C->getRight()))
				return true;
		}
		else if (operat == "<=")
		{
			if (std::stod(s) <= std::stod(C->getRight()))
				return true;
		}
	}
}
template <class T>
void swappy(T* x, T* y)
{
	auto tmp = *x;
	*x = *y;
	*y = tmp;
}
QueryResult* QuerySelect::execute()
{
	//SELECT ... FROM ... WHERE ... ORDER BY...

	std::vector<int> indexes;

	std::vector<std::vector<std::string>> res = tableForSelect->getRecords();
	std::vector<CField*> fields = tableForSelect->getFields();
	std::vector<std::vector<std::string>> resNew;
	resNew.resize(res.size() + 1);
	int i = 0;
	auto it = fields.begin();
	while (it != fields.end())
	{
		for (int m = 0; m < vectCols.size(); m++)
		{
			if ((*it)->getName() == vectCols[m])
			{
				i++;
				indexes.push_back(i);
			}
		}
		it++;
	}
	int lines = tableForSelect->getSize();

	for (int i = 0; i < vectCols.size(); i++)
		resNew[0].push_back(vectCols[i]);
	//std::cout << vectCols[i] << " ";
//
	int l = 1;
	if (this->condition != "")
	{
		int col = 0;
		std::string type;
		for (int q = 0; q < fields.size(); q++)
		{
			if (fields[q]->getName() == C->getLeft())
			{
				col = q;
				type = fields[q]->getTip();
			}
		}

		l = 1;
		for (int k = 0; k < lines; k++)
		{

			if (respectCondition(res[k][col], type) == true)
			{
				for (int p = 0; p < vectCols.size(); p++)
				{
					for (int q = 0; q < fields.size(); q++)
					{
						if (fields[q]->getName() == vectCols[p])
						{
							resNew[l].push_back(res[k][q]);
							//std::cout << res[k][q] << " ";
						}
					}
				}
				l++;
			}

			//std::cout << "\n";
		}
	}
	else
	{
		l = 1;
		std::cout << "\n";
		for (int k = 0; k < lines; k++)
		{
			for (int p = 0; p < vectCols.size(); p++)
			{
				for (int q = 0; q < res[0].size(); q++)
				{
					if (fields[q]->getName() == vectCols[p])
					{

						//std::cout << res[k][q] << " ";
						resNew[l].push_back(res[k][q]);
					}
				}

			}
			l++;
			//std::cout << "\n";
		}
	}
	int linesss = l;
	if (this->orderMode != "")
	{
		int k = 0;
		for (int i = 0; i < vectCols.size(); i++)
		{
			if (vectCols[i] == colForOrder)
				k = i;
		}
		int flag = 0;
		std::string tipp;
		for (int i = 0; i < fields.size(); i++)
		{
			if (colForOrder == fields[i]->getName())
				tipp = fields[i]->getTip();
		}
		if (tipp == "INTEGER")
			flag = 1;
		else if (tipp == "VARCHAR")
			flag = 2;
		else if (tipp == "DOUBLE")
			flag = 3;
		if (order == "ASC")
		{
			if (flag == 1)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (std::stoi(resNew[p][k]) > std::stoi(resNew[q][k]))
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
					}
				}
			}
			else if (flag == 2)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (isdigit(resNew[p][k][0]))
						{
							if (resNew[p][k].find('.') != string::npos)
							{
								if (stod(resNew[p][k]) > stod(resNew[q][k]))
									swappy(&resNew[p], &resNew[q]);
							}
							else
							{
								if (stoi(resNew[p][k]) > stoi(resNew[q][k]))
									swappy(&resNew[p], &resNew[q]);
							}
						}
						else if (resNew[p][k] > resNew[q][k])
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
						/*if (resNew[p][k] > resNew[q][k])
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}*/
					}
				}
			}
			else if (flag == 3)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (std::stod(resNew[p][k]) > std::stod(resNew[q][k]))
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
					}
				}
			}
		}
		else if (order == "DESC")
		{
			if (flag == 1)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (std::stoi(resNew[p][k]) < std::stoi(resNew[q][k]))
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
					}
				}
			}
			else if (flag == 2)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (isdigit(resNew[p][k][0]))
						{
							if (resNew[p][k].find('.') != string::npos)
							{
								if (stod(resNew[p][k]) < stod(resNew[q][k]))
									swappy(&resNew[p], &resNew[q]);
							}
							else
							{
								if (stoi(resNew[p][k]) < stoi(resNew[q][k]))
									swappy(&resNew[p], &resNew[q]);
							}
						}
						else if (resNew[p][k] < resNew[q][k])
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
					}
				}
			}
			else if (flag == 3)
			{
				for (int p = 1; p < linesss - 1; p++)
				{
					for (int q = p + 1; q < linesss; q++)
					{
						if (std::stod(resNew[p][k]) < std::stod(resNew[q][k]))
						{
							if (resNew[p].size() != 0 || resNew[q].size() != 0)
								swappy(&resNew[p], &resNew[q]);
						}
					}
				}
			}
		}
	}

	QueryResult* Q = new QueryResult(resNew);
	return Q;
}

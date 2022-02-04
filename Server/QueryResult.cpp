#include "QueryResult.h"

QueryResult::QueryResult(std::vector<std::vector<std::string>> res)
{
	result.resize(res.size());
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
			result[i].push_back(res[i][j]);
	}
	this->codeSucceded = 1;
	this->lines = 0;
}

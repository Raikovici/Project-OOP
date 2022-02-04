#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "iTCPListener.h"
#include <iostream>
#include "winsock2.h"
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
class CDataBase;
class Server : public iTCPListener
{
private:
	Server() {}
	virtual ~Server() {}
	static Server* instance;
	static SOCKET sclient;
	static SOCKET servers;
	vector<string> files;
	CDataBase* c;
	string outfilename;
	ofstream outfile;
public:
	static Server& getInstance();
	void run() override;
	void init() override;
	void sendToClient() override;
	void close() override;
	static void destroyInstance();
	void setFiles();
};


#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include "winsock2.h"
#include <string.h>
#include <string>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
class iTCPListener
{
public:
	virtual void init() = 0;
	virtual void run() = 0;
	virtual void sendToClient() = 0;
	virtual void close() = 0;
};


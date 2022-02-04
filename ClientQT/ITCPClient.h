#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "winsock2.h"
#include <string>
#include <string.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
class ITCPClient
{
public:
	virtual void startClient() = 0;
    virtual void sendToServer(string s) = 0;
    virtual string getResponse() = 0;
    virtual void receiveFromServer() = 0;
};


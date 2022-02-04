#pragma once
#include "ITCPClient.h"

class Client : public ITCPClient
{
private:
	Client() {}
	virtual ~Client() {}
	static SOCKET client;
	static Client* instance;
    //char sendbuf[1024];
   // char recbuf[1024];
    string sendbuf, recbuf;
    //AES* encrpyt;
public:
	static Client& getInstance();
	void startClient() override;
    void sendToServer(string s) override;
    string getResponse() override;
    void receiveFromServer() override;
	static void destroyInstance();
};


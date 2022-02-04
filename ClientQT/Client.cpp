#include "Client.h"
#define _CRT_SECURE_NO_WARNINGS

Client* Client::instance = nullptr;

SOCKET Client::client = 0;

Client& Client::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Client();
		return *instance;
	}
}

void Client::startClient()
{
	//Initialize winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
        cout << "WSAStartup error!" << endl;
		exit(1);
	}
	//Create socket
    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET = IPV4, SOCK_STREAM = TCP protocol oriented, IPPROTO_TCP for TCP
                                                        //SOCK_DGRAM = UDP protocol oriented, IPPROTO_UDP for UDP
	if (client == INVALID_SOCKET)
	{
        cout << "Failed to create client socet!Error code:" << WSAGetLastError() << endl;
		WSACleanup();
		exit(1);
	}
    SOCKADDR_IN sin; //strucure for create a connection
    sin.sin_family = AF_INET; //IPV4
    sin.sin_port = htons(8888);//Port for connecting
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//Client IP
    if (connect(client, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        cout << "Failed to connect with server!Error code:" << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
}
string Client::getResponse()
{
    return recbuf;
}
void Client::sendToServer(string s)
{
    sendbuf = s;
    recbuf = "";
    for(int i = 0; i < 1; i++)
    {
        int res = send(client, sendbuf.c_str(), sendbuf.length(), 0);
        if (sendbuf == "bye")
			break;
		if (res == SOCKET_ERROR)
        {
			cout << "Failed to send message!Error code: " << WSAGetLastError() << endl;
			closesocket(client);
			WSACleanup();
			exit(1);
        }
    }
}
void Client::receiveFromServer()
{
        char rec[1024];
        int res = 0;
        res = recv(client, rec, 1024, 0);
		if (res > 0)
		{
            recbuf = string(rec);
            cout << "server:\n" << recbuf << endl;
            //string s = getResponse();
		}
		else
		{
			cout << "Failed to receive message from server!Error code:" << WSAGetLastError() << endl;
			closesocket(client);
		}

}
void Client::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

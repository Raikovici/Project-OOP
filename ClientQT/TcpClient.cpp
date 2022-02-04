//#include "TcpClient.h"
//#include <iostream>
//void TcpClient::sendToServer(int serverSocket, const string& msg)
//{
//	//try
//	//{

//		int sendresult = send(serverSocket, msg.c_str(), msg.size() + 1, 0);
//		if (sendresult == SOCKET_ERROR)
//		{
//			int lastError = WSAGetLastError();
//			closesocket(Socket);
//			//throw new ConnectException(lastError, "Proxy disconnected!\n");
//		}
//	//}
//	/*catch (ConnectException* e)
//	{
//		Log::getInstance().write("CONNECTION ERROR #" + to_string(e->getCode()) + ": " + e->getMessage() + "\n");
//		QMessageBox::critical(nullptr, "Connection Error", e->getError().c_str());
//		delete e;
//		exit(-1);
//	}*/
//}

//string TcpClient::getResponseFromServer()
//{
//	char buf[4096];
//	ZeroMemory(buf, 4096);
//	int bytesReceived = recv(Socket, buf, 4096, 0);
//	if (bytesReceived == SOCKET_ERROR)
//	{
//		int lastError = WSAGetLastError();
//		//throw new ConnectException(lastError, "Proxy disconnected!\n");
//	}
//	else if (bytesReceived == 0)
//		std::cout << "Nothing received!\n";//throw new ConnectException(-2, "Proxy disconnected!\n");
//	else
//	{
//		string reply = string(buf, 0, bytesReceived);
//		//string decrypt_reply = Base64::decode(reply);
//		return reply;
//	}
//}

//int TcpClient::startClient()
//{
//	//try
//	//{
//		// Initialize WinSock
//		WSAData data;
//		WORD ver = MAKEWORD(2, 2);
//		int wsResult = WSAStartup(ver, &data);
//		if (wsResult != 0)
//		{
//			std::cout << "No connection!\n";
//			//throw new ConnectException(wsResult, "Can't start Winsock!\n");
//		}

//		// Create socket
//		Socket = socket(AF_INET, SOCK_STREAM, 0);
//		if (Socket == INVALID_SOCKET)
//		{
//			int lastError = WSAGetLastError();
//			WSACleanup();
//			//throw new ConnectException(lastError, "Can't create socket!\n");
//		}
//		//return 0;
//	//}
//	/*catch (ConnectException* e)
//	{
//		Log::getInstance().write("CONNECTION ERROR #" + to_string(e->getCode()) + ": " + e->getMessage() + "\n");
//		QMessageBox::critical(nullptr, "Connection Error", e->getError().c_str());
//		delete e;
//	}*/
//	return 1;
//}


//void TcpClient::closeClientConnections()
//{
//	closesocket(Socket);
//	WSACleanup();
//}

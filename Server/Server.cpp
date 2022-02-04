#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include "iQuery.h"
#include "QueryResult.h"
#include "CQuery.h"
#include "QueryCreateDB.h"
#include "QueryUpdate.h"
#include "QueryCreateTable.h"
#include "QueryDrop.h"
#include "QueryInsert.h"
#include "QueryDelete.h"
#include "CDataBase.h"
#include "CTable.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "dirent.h"
using namespace std;


Server* Server::instance = nullptr;
SOCKET Server::sclient = 0;
SOCKET Server::servers = 0;

Server& Server::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Server();
        return *instance;
    }
}


void Server::init()
{
    //Initialize socket
    WSADATA wsaData;//The modified structure contains information implemented by winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStratup error!" << endl;
        exit(1);
    }
    //Create a socket
    servers = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servers == INVALID_SOCKET)
    {
        cout << "Failde to create server socet!Error code:" << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
    // Bind socket
    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(servers, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        cout << "Failed to bind server socket!Error code:" << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
    //Monitor socket
    if (listen(servers, 10) == SOCKET_ERROR)//The message waiting queue is 10
    {
        cout << "Failed to listen server socket!Error code:" << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
    outfilename = "Queries_And_Results.txt";
    outfile.open(outfilename);
    cout << "Server started successfully..." << endl;

}

void Server::run()
{

    SOCKADDR_IN clientAdd;
    int cAddlen = sizeof(clientAdd);
    sclient = accept(servers, (LPSOCKADDR)&clientAdd, &cAddlen);
    if (sclient == SOCKET_ERROR)
    {
        cout << "Failde to accept client!Error code:" << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
    cout << "Received a connection: " << inet_ntoa(clientAdd.sin_addr) << "\n";
    //Receive and send data

}
void Server::sendToClient()
{

    char buf[1024];//The buffer size is 255
    //char* sendbuf = (char*)malloc(sizeof(char)*1024);//Send buffer
    char sendbuf[1024];
    //char sendbuf[1024];

    vector<CDataBase*> vect_BD;
    CDataBase* bd_used = nullptr;
    
    while (true)
    {

        memset(buf, 0, sizeof(buf));
        memset(sendbuf, 0, sizeof(sendbuf));
        int res = recv(sclient, buf, sizeof(buf), 0);
        if (res > 0)
        {
            cout << "client:" << buf << endl;
        }
        else if (res == 0)
        {
            cout << "Connect close..." << endl;
            break;
        }
        else
        {
            cout << "Failed to receive message from client!Error code:" << WSAGetLastError() << endl;
            closesocket(sclient);
        }
        cout << "server:";

        if (res == SOCKET_ERROR)
        {
            cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
            closesocket(sclient);

        }
        //gets_s(sendbuf);
        string s(buf);

        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        s.erase(std::remove(s.begin(), s.end(), '('), s.end());
        s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
        s.erase(std::remove(s.begin(), s.end(), ';'), s.end());

        //iQuery* select = GenerateQueries::getSelectQuery(s);
        //std::transform(s.begin(), s.end(),s.begin(), [](unsigned char c) { return std::toupper(c); });

        iQuery* queryy = new CQuery(s);
        queryy->tokenize();
        string typee = queryy->getPartOfQuery(0);

        if (typee == "SELECT")
        {
            c = bd_used;
            iQuery* select = GenerateQueries::getSelectQuery(s, c);
            select->interpret();
            QueryResult* Q = select->execute();
            std::vector<std::vector<std::string>> ress = Q->getContinut();

            if (strcmp(sendbuf, "bye") == 0)
            {
                cout << "Client requests to close the connection..." << endl;
                break;
            }
            string ss;
            for (int i = 0; i < ress.size(); i++)
            {
                for (int j = 0; j < ress[i].size(); j++)
                {
                    if (j == ress[i].size() - 1)
                    {
                        ss += ress[i][j];
                        ss += '\n';
                    }
                    else
                    {
                        ss += ress[i][j];
                        ss += ' ';
                    }
                }
               // ss += '\n';

            }
            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);

            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        
        }

        else if (typee == "CREATE")
        {
            string TableOrDB = queryy->getPartOfQuery(1);

            if (TableOrDB == "DATABASE")
            {
                QueryCreateDB* createDB = new QueryCreateDB(s,queryy->getTokens());

                CDataBase* bd = createDB->executee();
                c = bd;
                vect_BD.push_back(bd);

                if (strcmp(sendbuf, "bye") == 0)
                {
                    cout << "Client requests to close the connection..." << endl;
                    break;
                }

                string ss = "Baza de date " + bd->getName() +  " a fost adaugata cu succes!\n";
               
                const char* bufaux = (char*)ss.c_str();
                strcpy(sendbuf, bufaux);
                res = send(sclient, sendbuf, strlen(sendbuf), 0);
                outfile << s << "\n" << ss << "\n---------------------------------------------\n";
                if (res == SOCKET_ERROR)
                {
                    cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                    closesocket(sclient);

                }
            }

            if (TableOrDB == "TABLE")
            {
                
                QueryCreateTable* createTable = new QueryCreateTable(s, queryy->getTokens());

                if (bd_used == nullptr)
                    cout << "Alegeti-va baza de date inainte!\n" << endl; // throw exception

                CTable* tabel = createTable->executee(bd_used);

                bd_used->addTable(tabel);

                string ss = "Tabela " + tabel->getName() + " a fost adaugata cu succes in " + bd_used->getName() + "!\n";

                const char* bufaux = (char*)ss.c_str();
                strcpy(sendbuf, bufaux);
                res = send(sclient, sendbuf, strlen(sendbuf), 0);
                outfile << s << "\n" << ss << "\n---------------------------------------------\n";
                if (res == SOCKET_ERROR)
                {
                    cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                    closesocket(sclient);

                }
            }
        }

        else if (typee == "DELETE")
        {

            string tableName = queryy->getPartOfQuery(2);
            
            QueryDelete* deleted = new QueryDelete(s, queryy->getTokens());

            deleted->executee(bd_used, tableName);

            string ss;
            
            ss = "Tabela " + queryy->getPartOfQuery(2) + " a suferit modificarile corespunzatoare!\n";

            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        }
        
        else if (typee == "INSERT")
        {
            string tableName = queryy->getPartOfQuery(2);

            QueryInsert* insert = new QueryInsert(s,queryy->getTokens());

            if (bd_used == nullptr)
                cout << "Alegeti-va baza de date inainte!\n" << endl; // throw exceptio

            insert->executee(bd_used, tableName);
        
            string ss = "Inregistrarea a fost adaugata cu succes in " + tableName + " din baza de date " + bd_used->getName() + "!\n";

            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        
        }

        else if (typee == "UPDATE")
        {
            string tableName = queryy->getPartOfQuery(1);

            QueryUpdate* update = new QueryUpdate(s, queryy->getTokens());

            update->executee(bd_used, tableName);

            string ss;

            ss = "Tabela " + queryy->getPartOfQuery(2) + " a suferit modificarile corespunzatoare!\n";

            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        
        
        }

        else if (typee == "ALTER")
        {
            string tableName = queryy->getPartOfQuery(2);

            QueryUpdate* alter = new QueryUpdate(s, queryy->getTokens());

            alter->alterTable(bd_used, tableName);

            string ss;

            ss = "Tabela " + queryy->getPartOfQuery(2) + " a suferit modificarile corespunzatoare!\n";

            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        }

        else if (typee == "USE")
        {
        
            int ok = 0;
            string DataBaseName = queryy->getPartOfQuery(1);
            for (int i = 0; i < vect_BD.size(); i++)
            {
                if (vect_BD[i]->getName() == DataBaseName)
                {
                    bd_used = vect_BD[i];
                    ok = 1;
                    break;
                }
            }
            if (ok == 0)
            {
                for (int i = 0; i < files.size(); i++)
                {
                    if (files[i] == DataBaseName)
                    {
                        bd_used = new CDataBase();
                        bd_used->setName(files[i]);
                        bd_used->loadDB();
                        vect_BD.push_back(bd_used);
                        ok = 1;
                        break;
                    }
                }
            }
            string ss;

            if (ok == 1)
                ss = "Lucrati in baza de date " + DataBaseName + ".\n";
            else
                ss = "Aceasta baza de date nu exista!\n";

            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        }

        else if (typee == "DROP")
        {
            string TableOrDB = queryy->getPartOfQuery(1);

            if (TableOrDB == "DATABASE")
            {
                QueryDrop* dropDB = new QueryDrop(s, queryy->getTokens());

                string msj = dropDB->executee(vect_BD, queryy->getPartOfQuery(2));

                

                if (strcmp(sendbuf, "bye") == 0)
                {
                    cout << "Client requests to close the connection..." << endl;
                    break;
                }

                string ss;
                if (msj == "succes")
                     ss = "Baza de date " + queryy->getPartOfQuery(2) + " a fost stearsa cu succes!\n";
                else
                     ss = msj;

                const char* bufaux = (char*)ss.c_str();
                strcpy(sendbuf, bufaux);
                res = send(sclient, sendbuf, strlen(sendbuf), 0);
                outfile << s << "\n" << ss << "\n---------------------------------------------\n";
                if (res == SOCKET_ERROR)
                {
                    cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                    closesocket(sclient);

                }
            }

            if (TableOrDB == "TABLE")
            {

                QueryDrop* dropTabel = new QueryDrop(s, queryy->getTokens());

                dropTabel->executeDropTabel(bd_used, queryy->getPartOfQuery(2));

                string ss = "Tabela " + queryy->getPartOfQuery(2) + " a fost stearsa cu succes\n ";

                const char* bufaux = (char*)ss.c_str();
                strcpy(sendbuf, bufaux);
                res = send(sclient, sendbuf, strlen(sendbuf), 0);
                outfile << s << "\n" << ss << "\n---------------------------------------------\n";
                if (res == SOCKET_ERROR)
                {
                    cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                    closesocket(sclient);

                }
            }        
        }
        else
        {
            string ss = "Invalid query!!! Please send a valid one";
            const char* bufaux = (char*)ss.c_str();
            strcpy(sendbuf, bufaux);
            res = send(sclient, sendbuf, strlen(sendbuf), 0);
            outfile << s << "\n" << ss << "\n---------------------------------------------\n";
            if (res == SOCKET_ERROR)
            {
                cout << "Failed to send message to client!Error code:" << WSAGetLastError() << endl;
                closesocket(sclient);

            }
        }
    }
}

void Server::close()
{
    closesocket(sclient);
    closesocket(servers);
    cout << "socket close..." << endl;
    WSACleanup();
}

void Server::destroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void Server::setFiles()
{
    DIR* d;
    char* p1, * p2;
    int ret;
    struct dirent* dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            p1 = strtok(dir->d_name, ".");
            p2 = strtok(NULL, ".");
            if (p2 != NULL)
            {
                ret = strcmp(p2, "txt");
                if (ret == 0)
                {
                    files.push_back(string(p1));
                }
            }

        }
        closedir(d);
    }
}

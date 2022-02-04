#include "CTable.h"
#include "CField.h"
#include "Server.h"
#include "iQuery.h"
void main()
{
	Server& S = Server::getInstance();
	S.init();
	S.run();
	S.setFiles();
	S.sendToClient();
	S.close();
	S.destroyInstance();
}
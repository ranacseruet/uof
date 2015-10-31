#include "UDPServer.h"

public class FTPServer
{
private:
	UDPServer* udpServer;
	FileHelper* fileHelper;
	Logger* logger;
public:
	FTPServer(UDPServer*, FileHelper*, Logger*);
	~FTPServer(void);

	void run(void);

	void get(Request);
	void put(Request);
	void del(void);
	void list(Request);
	void handshake(void);
};
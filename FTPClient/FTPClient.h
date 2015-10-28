#pragma once

#include "UDPClient.h"

class FTPClient 
{

private:
	UDPClient * uc;
	Request req;

public:
	FTPClient();

	void showMenu();
	int handshake();
	void list();
	void get();
	void put();
	void del();
	void rename();

	~FTPClient();
};
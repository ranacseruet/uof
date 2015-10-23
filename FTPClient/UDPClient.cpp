#include <windows.h>
#include <sys/types.h>

#include "Client.h"
#include <iomanip>
#include <iostream>
#include <string>

char buffer[BUFFER_LENGTH];

unsigned long getAddressByHost()
{
	struct hostent *host;            /* Structure containing host information */

	if ((host = gethostbyname("MDALIRANAEDAF")) == NULL)
	{
		return(1);
	}

	/* Return the binary, network byte ordered address */
	return *((unsigned long *)host->h_addr_list[0]);
}

UDPClient::UDPClient()
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);
}

UDPClient::~UDPClient()
{
	WSACleanup();
}



bool UDPClient::SendRequest(Request * req)
{
	int handle = socket(AF_INET, SOCK_DGRAM, 0);

	if (handle <= 0)
	{
		printf("failed to create socket\n");
		return false;
	}

	sockaddr_in address;
	int ServPort = 5001;
	memset(&address, 0, sizeof(address));     /* Zero out structure */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = getAddressByHost();
	address.sin_port = htons(ServPort);

	sockaddr_in myaddress;
	myaddress.sin_family = AF_INET;
	myaddress.sin_addr.s_addr = INADDR_ANY;
	myaddress.sin_port = htons((unsigned short)0);
	

	if (bind(handle, (const sockaddr*)&myaddress, sizeof(sockaddr_in)) < 0)
	{
		printf("failed to bind socket\n");
		return false;
	}

	printf("Size: %d", sizeof(req->filename));
	memset(buffer, '\0', BUFFER_LENGTH);
	memcpy(buffer, &req, sizeof(req));
	printf(buffer);

	printf("Size: %d" , sizeof(buffer));
	int sent_bytes = sendto(handle, (const char*)buffer, sizeof(buffer), 0, (sockaddr*)&address, sizeof(sockaddr_in));

	if (sent_bytes != sizeof(buffer))
	{
		printf("failed to send packet\n");
		return false;
	}

	closesocket(handle);
	return true;
};


bool UDPClient::SendDatat(Data data)
{
	return true;
};


void UDPClient::run()
{
	
	Request req;
	memset(&req, '\0', sizeof(req));
	req.type = 1;
	UDPClient::SendRequest(&req);
		
	
}

/*int main(void)
{
	UDPClient* client = new UDPClient();
	client->run();
	return 0;
}*/
/*
*
* 프로젝트 우클릭 -> 속성 -> 링커 -> 입력 -> 추가종속성에 WS2_32.lib 추가 후 빌드 !!!!
*
sendto function
The sendto function sends data to a specific destination.

```
int sendto(
  SOCKET         s,
  const char     *buf,
  int            len,
  int            flags,
  const sockaddr *to,
  int            tolen
);
```
*/

#include <Windows.h>
#include <iostream>
#include <winsock.h>

using namespace std;

int main() {
	cout << "\t\t------UDP CLIENT------" << endl;

	// Local Variable
	WSADATA		WinSockData;
	int			iWsaStartup;
	int			iWsaCleanup;

	SOCKET		UDPSocketClient;
	struct		sockaddr_in		UDPServer;

	char		Buffer[512] = "Hello from Client!";
	int			iSendto;

	int			iBufferLen = strlen(Buffer) + 1;
	int			iUDPServerLen = sizeof(UDPServer);
	int			iCloseSocket;


	// STEP-1 Initialization of Winsock 
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
	if (iWsaStartup != 0) {
		cout << "WsaStartup() Failed & Error no - " << iWsaStartup << endl;
	}
	cout << "WSAStartup() Success" << endl;


	// STEP-2 Fill the UDPServer Structure
	UDPServer.sin_family		= AF_INET;
	UDPServer.sin_addr.s_addr	= inet_addr("127.0.0.1");
	UDPServer.sin_port			= htons(8001);


	// STEP-3 Socket Creation
	UDPSocketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocketClient == INVALID_SOCKET) {
		cout << "UDP Socket creation Failed = " << WSAGetLastError() << endl;
	}
	cout << "socket() Success!" << endl;


	// STEP-4 sendto()
	iSendto = sendto(
		UDPSocketClient,
		Buffer,
		iBufferLen,
		MSG_DONTROUTE,
		(SOCKADDR*)&UDPServer,
		sizeof(UDPServer));

	if (iSendto == SOCKET_ERROR) {
		cout << "sendto() Faield & Error no - " << WSAGetLastError() << endl;
	}
	cout << "sendto() Success" << endl;


	// STEP-5 closesocket() 
	iCloseSocket = closesocket(UDPSocketClient);
	if (iCloseSocket == SOCKET_ERROR) {
		cout << "closesocket() Faield = " << WSAGetLastError() << endl;
	}
	cout << "claosesocket() Success" << endl;

	// STEP-6 WSACleanUp() for Terminating from Winsock DLL
	iWsaCleanup = WSACleanup();
	if (iWsaStartup == SOCKET_ERROR) {
		cout << "WSACleanup() Failed = " << WSAGetLastError() << endl;
	}
	cout << "WSACleanup() Success" << endl;

	system("PAUSE");
	return 0;
}	
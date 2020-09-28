/* 
***** 프로젝트 속성 > 구성 속성 > 링커 > 입력 > 추가 종속성 > WS2_32.lib 추가 *****

TCP (Transmission Control Protocol) 

	1. Stream Based.
	2. Connection Oriented
	3. Heavy wiehgt beacuse TCP Header is 20 Bytes.
	4. Provide Error Correction.
	5. Re-Transmission of Data if Data corupted. 
	6. Provide in-order Transmissioin of data


Programming Steps of TCP 
<Server>
1. WSAStartUp
2. Fill Client or Server Struct
3. Socket
4. Bind
5. Listen
6. Accept
7. recvfrm or sendto
8. closesocket
9. WSACleanUp

<Client> 
1. WWSAStartUp
2. Fill Server or Client Struct
3. Socket
4. Connect
5. sendto or recvfrm
6. closesocket
7. WSACleanUp


WSAStartup function
The WSAStartup function initiates use of the Winsock DLL by a process.

```
int WSAStartup(
  WORD      wVersionRequired,
  LPWSADATA lpWSAData
);
```

SOCKADDR_IN structure
The SOCKADDR_IN structure specifies a transport address and port for the AF_INET address family.

```
typedef struct sockaddr_in {
#if ...
  short          sin_family;
#else
  ADDRESS_FAMILY sin_family;
#endif
  USHORT         sin_port;
  IN_ADDR        sin_addr;
  CHAR           sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;
```

socket function
The socket function creates a socket that is bound to a specific transport service provider.

```
SOCKET WSAAPI socket(
  int af,
  int type,
  int protocol
);
```

bind function
The bind function associates a local address with a socket.

```
int bind(
  SOCKET         s,
  const sockaddr *addr,
  int            namelen
);
```

listen function
The listen function places a socket in a state in which it is listening for an incoming connection.

```
int WSAAPI listen(
  SOCKET s,
  int    backlog
);
```


accept function
The accept function permits an incoming connection attempt on a socket.

```
SOCKET WSAAPI accept(
  SOCKET   s,
  sockaddr *addr,
  int      *addrlen
);
```

recv function
The recv function receives data from a connected socket or a bound connectionless socket.

```
int recv(
  SOCKET s,
  char   *buf,
  int    len,
  int    flags
);
```

closesocket function
The closesocket function closes an existing socket.

```
int closesocket(
  IN SOCKET s
);
```

WSACleanup function
The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).

```
int WSACleanup();
```
*/


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t------ TCP SERVER ------" << endl;
	cout << endl;

	//Local Variable
	WSADATA		Winsockdata;
	int			iWsaStartup;
	int			iWsaCleanup;

	SOCKET		TCPServerSocket;
	int			iCloseSocket;

	struct		sockaddr_in TCPServerAdd;
	struct		sockaddr_in TCPClientAdd;
	int			iTCPClientAdd = sizeof(TCPClientAdd);

	int			iBind;
	int			iListen;

	SOCKET		sAcceptSocket;

	int			iSend;
	char		SenderBuffer[512] = "Hello from Server!";
	int			iSenderBuffer = strlen(SenderBuffer) + 1;

	int			iRecv;
	char		RecvBuffer[512];
	int			iRecvBuffer = strlen(RecvBuffer) + 1;


	//STEP-1 WSAStartUP()
	iWsaStartup = WSAStartup(MAKEWORD(2, 2, ), &Winsockdata);
	if (iWsaStartup != 0) {
		cout << "WSAStartup() Failed" << endl;
	}
	cout << "WSAStartup() Success" << endl;


	//STEP-2 Fill the Structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8000);


	//STEP-3 SocketCreation
	TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPServerSocket == INVALID_SOCKET) {
		cout << "socket() Failed & Error - " << WSAGetLastError() << endl;
	}
	cout << "socket() Success!" << endl;

	
	//STEP-4 bind
	iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iBind == SOCKET_ERROR) {
		cout << "bind() Faield & Error No - " << WSAGetLastError() << endl;
	}
	cout << "bind() Success" << endl;


	//STEP-5 listen()
	iListen = listen(TCPServerSocket, 2);
	if (iListen == SOCKET_ERROR) {
		cout << "listen() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "listen() Success" << endl;


	//STEP-6 Accept
	sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);
	if (sAcceptSocket == INVALID_SOCKET) {
		cout << "accept() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "accept() Success" << endl;


	//STEP-7 Send Data to Client 
	iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR) {
		cout << "send() Faield & Error no - " << WSAGetLastError() << endl;
	}
	cout << "send() Success" << endl;


	//STEP-8 Recv Data from Client
	iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR) {
		cout << "recv() Faield & Error no - " << WSAGetLastError() << endl;
	}
	cout << "recv() Success" << endl;

	cout << "DATA RECEIVED -> " << RecvBuffer << endl;


	//STEP-9 Close Socket
	iCloseSocket = closesocket(TCPServerSocket);
	if (iCloseSocket == SOCKET_ERROR) {
		cout << "closesocket() Failed & Error No - " << WSAGetLastError() << endl;
	}
	cout << "closesocket() Success" << endl;


	//STEP-10 CleanUp from DLL
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR) {
		cout << "WSACleanup() Faield & Error no -" << WSAGetLastError() << endl;
	}
	cout << "WSACleanup() Success" << endl;

	system("PAUSE");
	return 0;
}
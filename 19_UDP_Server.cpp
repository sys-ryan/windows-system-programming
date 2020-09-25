/*
* 
* 프로젝트 우클릭 -> 속성 -> 링커 -> 입력 -> 추가종속성에 WS2_32.lib 추가 후 빌드 !!!!
* 
What is Socket? 
Socket is one endpoint which is used for communicating between two nodes in a Network.
Socket is an interface of Client-Server Architecture. 

Socket Type
- Internet Sockets
- UNIX Sockets
- X.25 Sockets ... 

Internet Socket
Internet sockets characterized by IP Address (4 bytes) and port number(2 bytes).
It's a Transport Layer Protocol
  
	Types
	1. STREAM SOCKETS (SOCK_STREAM)
		i. Connection Oriented
		ii. Rely on TCP to provide two ways Communication.

	2. DATAGRAM SOCKETS (SOCK_DGRAM)
		i. Connection is Unreliable.
		ii. Rely on UDP


	UDP (User Datagram Protocol) 
	1. Message Oriented
	2. Connectionless
	3. Light weight(UDP Header is 60% less than TCP Header).
	4. Small Pakcet Size UDP Header - 8 byte.
	5. There is no Error Detection 
	6. If you lose teh data then you cant retrieve.
	7. Corrupted data may be discarded or lead to out of order. 
	

	Programming Steps of UDP
	<Server>
	1. WSAStartup
	2. Fill CilentORServer Struct
	3. Socket
	4. bind
	5. recvfrm or sendto
	6. closesocket
	7. WSACleanUp

	<Client>
	1. WSAStartUP
	2. Fill ServerORClient Struct
	3. Socket
	4. sendto or recvfrm
	5. closesocket
	6. WSACleanUp


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


htons function
The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).

```
u_short htons(
  u_short hostshort
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


recvfrom function
The recvfrom function receives a datagram and stores the source address.

```
int recvfrom(
  SOCKET   s,
  char     *buf,
  int      len,
  int      flags,
  sockaddr *from,
  int      *fromlen
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



#include <Windows.h>
#include <iostream>
#include <winsock.h>

using namespace std;

int main() {

	// Local Variable definitions
	cout << "\t\t------ UDP SERVER ------" << endl;
	cout << endl;

	WSADATA		WinSockData;
	int			iWsaStartup;
	int			iWsaCleanup;

	SOCKET		UDPSocketServer;
	struct		sockaddr_in		UDPClient;

	char		Buffer[512];
	int			iBufferLen = strlen(Buffer) + 1;

	int			iBind;
	int			iReceiveFrom;

	int			iUDPClientLen = sizeof(UDPClient);
	int			iCloseSocket;


	//STEP-1 Initialization of Winsock
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);

	if (iWsaStartup != 0) {
		cout << "WSAStartUp() Failed" << endl;
	}
	cout << "WSAStartUp() Success" << endl;


	//STEP-2 Fill the UDPClient(SOCKET ADDRESS) Structure
	UDPClient.sin_family = AF_INET;
	UDPClient.sin_addr.s_addr = inet_addr("127.0.0.1");
	UDPClient.sin_port = htons(8001);

	//STEP-3 Socket Creation
	UDPSocketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (UDPSocketServer == INVALID_SOCKET) {
		cout << "socket() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "socket() Success" << endl;

	
	//STEP-4 bind the server
	iBind = bind(
		UDPSocketServer,
		(SOCKADDR*)&UDPClient,
		sizeof(UDPClient));

	if (iBind == SOCKET_ERROR) {
		cout << "bind() Failed & Error No - " << WSAGetLastError() << endl;
	}
	cout << "bind() Success" << endl;
	

	//STEP-5 recvfrom() from receive data from client
	iReceiveFrom = recvfrom(
		UDPSocketServer,
		Buffer,
		iBufferLen,
		MSG_PEEK,
		(SOCKADDR*)&UDPClient,
		&iUDPClientLen);

	if (iReceiveFrom == SOCKET_ERROR) {
		cout << "recvfrom() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "recvfrom() Success" << endl;
	cout << "Receive Data -> " << Buffer << endl;

	//STEP-6 closesocket()
	iCloseSocket = closesocket(UDPSocketServer);

	if (iCloseSocket == SOCKET_ERROR) {
		cout << "closesocket() Failed & Error No - " << WSAGetLastError() << endl;
	}
	cout << "closesocket() Success" << endl;
		

	//STEP-7 WSACleanUp() for Terminating from DLL 
	iWsaCleanup = WSACleanup();

	if (iWsaCleanup == SOCKET_ERROR) {
		cout << "WSA CleanUp failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "WSACleanup() Success" << endl;

	system("PAUSE");
	return 0;
}



/*
connect function
The connect function establishes a connection to a specified socket.

```
int WSAAPI connect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);

```
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t------ TCP CLIENT ------" << endl;
	cout << endl;

	//Local Variable
	WSADATA		Winsockdata;
	int			iWsaStartup;
	int			iWsaCleanup;

	SOCKET		TCPClientSocket;
	int			iCloseSocket;

	struct		sockaddr_in TCPServerAdd;

	int			iConnect;

	int			iRecv;
	char		RecvBuffer[512];
	int			iRecvBuffer = strlen(RecvBuffer) + 1;

	int			iSend;
	char		SenderBuffer[512] = "Hello from Client!";
	int			iSenderBuffer = strlen(SenderBuffer) + 1;


	//STEP-1 WSAStartUP()
	iWsaStartup = WSAStartup(MAKEWORD(2, 2, ), &Winsockdata);
	if (iWsaStartup != 0) {
		cout << "WSAStartup() Failed" << endl;
	}
	cout << "WSAStartup() Success" << endl;


	//STEP-2 SocketCreation
	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (TCPClientSocket == INVALID_SOCKET) {
		cout << "socket() Failed & Error - " << WSAGetLastError() << endl;
	}
	cout << "socket() Success!" << endl;


	//STEP-3 Fill the Structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8000);


	//STEP-4 Connect
	iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR) {
		cout << "connect() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "Connect() Success" << endl;


	//STEP-5 RECV Data From Server Side
	iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
	if (iRecv == SOCKET_ERROR) {
		cout << "recv() Failed & Error no - " << WSAGetLastError() << endl;
	}
	cout << "DATA RECEIVED -> " << RecvBuffer << endl;


	//STEP-6 Send Data to Server 
	iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);
	if (iSend == SOCKET_ERROR) {
		cout << "sned() Faield & Error no - " << WSAGetLastError() << endl;
	}
	cout << "send() Success" << endl;


	//STEP-8 WSA Cleanup
	iWsaCleanup = WSACleanup();
	if (iWsaCleanup == SOCKET_ERROR) {
		cout << "WSACleanup() Faield & Error no -" << WSAGetLastError() << endl;
	}
	cout << "WSACleanup() Success" << endl;

	system("PAUSE");
	return 0;
}
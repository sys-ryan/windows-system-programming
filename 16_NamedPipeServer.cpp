/*
Programming Steps:

<Server>
1. Create named Pipe
2. ConnectNamedPipe
3. WriteFile or ReadFile
4. DisconnectNamedPipe
6. CloseHandle

<Client>
1. CreateFile of CallNamedPipe
2. WriteFile/ReadFile/TransactNamedPipe
3. CloseHandle


CreateNamedPipe function
Creates an instance of a named pipe and returns a handle for subsequent pipe operations

```
HANDLE CreateNamedPipe(
  LPCTSTR               lpName,
  DWORD                 dwOpenMode,
  DWORD                 dwPipeMode,
  DWORD                 nMaxInstances,
  DWORD                 nOutBufferSize,
  DWORD                 nInBufferSize,
  DWORD                 nDefaultTimeOut,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
```


ConnectNamedPipe function
Enables a named pipe server process to wait for a client process to connect to an instance of a named pipe.
A client process connects by calling either the CreateFile or CallNamedPipe function.

```
BOOL ConnectNamedPipe(
  HANDLE       hNamedPipe,
  LPOVERLAPPED lpOverlapped
);
```


FlushFileBuffers function
Flushes the buffers of a specified file and causes all buffered data to be written to a file.

```
BOOL FlushFileBuffers(
  HANDLE hFile
);
```


DisconnectNamedPipe function
Disconnects the server end of a named pipe instance from a client process.

```
BOOL DisconnectNamedPipe(
  HANDLE hNamedPipe
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....NAMED PIPE SERVER...." << endl;

	//Named Pipe Local Variable
	HANDLE	hCreateNamedPipe;
	char	szInputBuffer[1023];
	char	szOutputBuffer[1023];
	DWORD	dwszInputBuffer = sizeof(szInputBuffer);
	DWORD	dwszOutputBuffer = sizeof(szOutputBuffer);


	//ConnectNamedPipe Local Variable
	BOOL	bConnectNamedPipe;


	//WriteFile Local Variable
	BOOL	bWriteFile;
	char	szWriteFileBuffer[1023] = "Hello From NamepdPipe Server!!";
	DWORD	dwWriteBufferSize = sizeof(szWriteFileBuffer);
	DWORD	dwNoBytesWrite;


	//FlushBuffer
	BOOL	bFlushFileBuffer;


	//ReadFile Local variable
	BOOL	bReadFile;
	char	szReadFileBuffer[1023];
	DWORD	dwReadBufferSize = sizeof(szWriteFileBuffer);
	DWORD	dwNoBytesRead;


	//CreateNamedPipe - STEP -1
	hCreateNamedPipe = CreateNamedPipe(
		L"\\\\.\\pipe\\MYNAMEDPIPE",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		dwszOutputBuffer,
		dwszInputBuffer,
		0,
		NULL);

	if (hCreateNamedPipe == INVALID_HANDLE_VALUE) {
		cout << "CreateNamedPipe() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateNamedPipe() Sucess" << endl;


	//ConnectNamedPipe - STEP - 2
	bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
	if (bConnectNamedPipe == FALSE) {
		cout << "ConnectNamedPipe() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "ConnectNamedPipe() Success" << endl;



	//WriteFile Operation - STEP - 3
	bWriteFile = WriteFile(
		hCreateNamedPipe,
		szWriteFileBuffer,
		dwWriteBufferSize,
		&dwNoBytesWrite,
		NULL);

	if (bWriteFile == FALSE) {
		cout << "WriteFile Failed = " << GetLastError() << endl;
	}
	cout << "WriteFile() Success" << endl;


	//Flush the File Buffer - STEP - 4
	bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);
	if (bFlushFileBuffer == FALSE) {
		cout << "FlushFileBuffer() Faield & Error no - " << GetLastError() << endl;
	}
	cout << "FlushFileBuffer() Success" << endl;


	//ReadFile - STEP - 5
	bReadFile = ReadFile(
		hCreateNamedPipe,
		szReadFileBuffer,
		dwReadBufferSize,
		&dwNoBytesRead,
		NULL);

	if (bReadFile == FALSE) {
		cout << "ReadFile Failed = " << GetLastError() << endl;
	}
	cout << "ReadFile Success" << endl;

	cout << "DATA READING FROM CLIENT -> " << szReadFileBuffer << endl;


	// DisconnectNamed Pipe - STEP - 6
	DisconnectNamedPipe(hCreateNamedPipe);


	//CloseHandle - STEP - 7
	CloseHandle(hCreateNamedPipe);

	system("PAUSE");
	return 0;
}

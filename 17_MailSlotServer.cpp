/*
MAILSLOTS

1. MailSlots is another IPC Mechanism
2. Used as one way commuincation
3. Mailslots generally used for Transmit to Short messages .
	i.e. Datagram
4. Mailslots can be used either locally or over the network.
5. Mailslots is a Client-Server Interface
6. In Mailslots, Only CLIENT write the message which is stored on mailslots and later SERVER can retrieve or read the message.
7. Generally Mailslots is message exchanging communication
8. Mailslots does not provide any confirmation that a message has been received.
9. ''We can send Only 424 bytes message.


PROGRAMMING STEPS
<SERVER>
1. CreateMailSlots
2. ReadFile
3. CloseHandle

<CLIENT>
1. CreateFile
2. WriteFile
3. CloseHandle


CreateMailslot function
Creates a mailslot with the specified name and returns a handle that a mailslot server can use to perform operations on the mailslot.

```
HANDLE CreateMailslot(
  LPCTSTR                lpName,
  DWORD                 nMaxMessageSize,
  DWORD                 lReadTimeout,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
```

□ lpName
The name of the mailslot. This name must have the following form:
\\.\mailslot\[path]name


□ lReadTimeout
The time a read operation can wait for a message to be written to the mailslot before a time-out occurs, in milliseconds. 
The following values have special meanings.
	0						: Returns immediately if no message is present. (The system does not treat an immediate return as an error.)
	MAILSLOT_WAIT_FOREVER	: Waits forever for a message.
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....MAILSLOTS SERVER...." << endl;

	//CreateMailSlots Local variable
	HANDLE hSlots;



	//ReadFile Local Variable
	BOOL	bReadFile;
	DWORD	dwNoBytesRead;
	char	szReadFileBuffer[1023];
	DWORD	dwReadFileBufferSize = sizeof(szReadFileBuffer);


	//STEP - 1 CreateMailSlots def
	hSlots = CreateMailslot(
		L"\\\\.\\mailslot\\MYMAILSLOTS",
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);
	if (hSlots == INVALID_HANDLE_VALUE) {
		cout << "CreateMailslot() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateMailslot() Success" << endl;


	//STEP - 2 ReadFile def
	bReadFile = ReadFile(
		hSlots,
		szReadFileBuffer,
		dwReadFileBufferSize,
		&dwNoBytesRead,
		NULL);

	if (bReadFile == FALSE) {
		cout << "ReadFile() Failed & Erorr no - " << GetLastError() << endl;
	}
	cout << "ReadFile() Success" << endl;
	cout << "DATA READINF FROM MAILSLOTS CLIENT -> " << szReadFileBuffer << endl;


	//STEP - 3 CloseHandle
	CloseHandle(hSlots);

	system("PAUSE");
	return 0;
}

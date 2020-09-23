#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....MAILSLOTS CLIENT...." << endl;

	//CreateFile Local Variable
	HANDLE	hCreateFile;


	//WriteFile Local Variable
	BOOL	bWriteFile;
	DWORD	dwNoBytesWrite;
	char	szWriteFileBuffer[1023];
	DWORD	dwWriteFileBufferSize = sizeof(szWriteFileBuffer);


	//CreateFile for Pipe
	hCreateFile = CreateFile(
		L"\\\\.\\mailslot\\MYMAILSLOTS",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hCreateFile == INVALID_HANDLE_VALUE) {
		cout << "CreateFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateFile() Success" << endl;

	cout << "Write Your Message" << endl;
	cin.getline(szWriteFileBuffer, dwWriteFileBufferSize);

	//WriteFile Operation
	bWriteFile = WriteFile(
		hCreateFile,
		szWriteFileBuffer,
		dwWriteFileBufferSize,
		&dwNoBytesWrite,
		NULL);

	if (bWriteFile == FALSE) {
		cout << "WriteFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "WriteFile() Success" << endl;

	CloseHandle(hCreateFile);

	system("PAUSE");
	return 0;
}

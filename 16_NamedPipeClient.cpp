#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....NAMED PIPE CLIENT...." << endl;

	//Local Varaible
	HANDLE	hCreateFile;


	////ReadFile Local Variable
	BOOL	bReadFile;
	DWORD	dwNoBytesRead;
	char	szReadFileBuffer[1023];
	DWORD	dwReadFileBufferSize = sizeof(szReadFileBuffer);


	//WriteFile Local Variable
	BOOL	bWriteFile;
	DWORD	dwNoBytesWrite;
	char	szWriteFileBuffer[1023] = "Hello From NamedPipe Client!!";
	DWORD	dwWriteFileBufferSize = sizeof(szWriteFileBuffer);


	//CreateFile for Pipe
	hCreateFile = CreateFile(
		L"\\\\.\\pipe\\MYNAMEDPIPE",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hCreateFile == INVALID_HANDLE_VALUE) {
		cout << "CreateFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateFile() Success!" << endl;


	//ReadFile
	bReadFile = ReadFile(
		hCreateFile,
		szReadFileBuffer,
		dwReadFileBufferSize,
		&dwNoBytesRead,
		NULL);

	if (bReadFile == FALSE) {
		cout << "ReadFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "ReadFile() Success!" << endl;
	cout << "DATA READING FROM SERVER -> " << szReadFileBuffer << endl;


	//WwriteFile Operation
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

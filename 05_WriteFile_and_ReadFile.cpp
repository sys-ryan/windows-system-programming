/*
WriteFile function
Writes data to the specified file or input/output (I/O) device.

Syntax
```
BOOL WriteFile(
  HANDLE       hFile,
  LPCVOID      lpBuffer,
  DWORD        nNumberOfBytesToWrite,
  LPDWORD      lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
);
```


ReadFile function
Reads data from the specified file or input/output (I/O) device. Reads occur at the position specified by the file pointer if supported by the device.

Syntax
```
BOOL ReadFile(
  HANDLE       hFile,
  LPVOID       lpBuffer,
  DWORD        nNumberOfBytesToRead,
  LPDWORD      lpNumberOfBytesRead,
  LPOVERLAPPED lpOverlapped
);
```
*/
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {

	//local variables
	HANDLE hFile;
	BOOL bFile;
	char chBuffer[] = "This is the Sample program of Write & Read API";
	DWORD dwNumberOfBytesToWrite = strlen(chBuffer);
	DWORD dwNumberOfBytesWrriten = 0;

	DWORD dwNumberOfBytesToRead = strlen(chBuffer);
	DWORD dwNumberOfBytesRead = 0;

	//Create File
	hFile = CreateFile(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\TestFile.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		cout << "CreateFile() Failed & Error No =" << GetLastError() << endl;
	}
	cout << "CreateFile() Success" << endl;

	//WriteFile
	bFile = WriteFile(
		hFile,
		chBuffer,
		dwNumberOfBytesToWrite,
		&dwNumberOfBytesWrriten,
		NULL);
	if (bFile == FALSE) {
		cout << "WriteFile() Failed & Error No =" << GetLastError() << endl;
	}
	cout << "WriteFile() Success" << endl;

	//ReadFile
	bFile = ReadFile(
		hFile,
		chBuffer,
		dwNumberOfBytesToRead,
		&dwNumberOfBytesRead,
		NULL);
	if (bFile == FALSE) {
		cout << "ReadFile() Failed & Error No = " << GetLastError() << endl;
	}
	cout << "ReadFile() Success " << endl;

	cout << "Data read from the file -> " << chBuffer << endl;

	//Closing the Handle
	CloseHandle(hFile);
	system("PAUSE");
	return 0;
}

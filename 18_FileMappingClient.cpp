/*
OpenFileMapping function
Opens a named file mapping object.

```
HANDLE OpenFileMappingA(
  DWORD		dwDesiredAccess,
  BOOL		bInheritHandle,
  LPCTSTR	lpName
);
```
*/
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....FILEMAPPING CLIENT...." << endl;
	cout << endl;

	// Local Variable Definition
	HANDLE	hFileMap;
	BOOL	bResult;
	PCHAR	lpBuffer = NULL;

	//STEP-1 OpenFileMapping
	hFileMap = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		L"Local\\MyFileMap");

	if (hFileMap == NULL) {
		cout << "OpenFileMapping() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "OpenFileMapping() Success" << endl;


	//STEP-2 MapViewOfFile
	lpBuffer = (PCHAR)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256);

	if (lpBuffer == NULL) {
		cout << "MapViewOfFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "MapViewOfFile Success" << endl;


	//STEP-3 Reading the Data from File-Map Object
	cout << "DATA READING FROM SERVER PROCESS -> " << lpBuffer << endl;


	//STEP-4 UnmapViewOfFile
	bResult = UnmapViewOfFile(lpBuffer);
	if (bResult == NULL) {
		cout << "Unmapping Failed = " << GetLastError() << endl;
	}
	cout << "Unmapping Success" << endl;


	//STEP-5 Close Handle
	CloseHandle(hFileMap);

	system("PAUSE");
	return 0;
}

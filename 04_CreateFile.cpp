/*
CreateFileA function
The function returns a handle that can be used to access the file or device for various types of I/O depending on the file or device and the flags and attributes specified.


Syntax
```
HANDLE CreateFileA(
  LPCSTR                lpFileName,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
);
```


CloseHandle function
Closes an open object handle.

Syntax
```
BOOL CloseHandle(
  HANDLE hObject
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	HANDLE hFile;
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
	CloseHandle(hFile);
	system("PAUSE");
	return 0;
}

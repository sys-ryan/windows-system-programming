/*
FILE-MAPPING in IPC

	1. File-Mapping is similar to Shared Memory.
	2. File-mapping is local to the system and it cannot be used over the network.
	3. Whenever we createa file-mapping object, this object is treated as a shared memory block.
	4. It is useful when live information between processes is changing frequently.

	Example - Suppose we have a multiple information resource then
	i.		1st process obtains the information
	ii.		2nd process changes the information
	iii.	3rd process is displaying the information on Screen.

	5. Whenever we use the File-mapping object then require some synchronization techniques otherwise another process contaminate the information.


How File-Mapping Works
There are 3 ways an application to shar a file-mapping object.
1. inheritance.
2. Named file mapping.
3. Handle Duplication


<Programming Steps>

	Server OR Parent
	1. CreateFileMapping
	2. MapViewOfFile
	3. CopyMemory
	4. UnMapViewOfFile


	Client or Child
	1. OpenFileMapping
	2. MapViewOfFile
	3. Print Your Data
	4. UnMapViewOfFile
	5. CloseHandle


CreateFileMapping function
Creates or opens a named or unnamed file mapping object for a specified file.

```
HANDLE CreateFileMappingA(
  HANDLE                hFile,
  LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
  DWORD                 flProtect,
  DWORD                 dwMaximumSizeHigh,
  DWORD                 dwMaximumSizeLow,
  LPCTSTR               lpName
);
```

MapViewOfFile function
Maps a view of a file mapping into the address space of a calling process.

```
LPVOID MapViewOfFile(
  HANDLE hFileMappingObject,
  DWORD  dwDesiredAccess,
  DWORD  dwFileOffsetHigh,
  DWORD  dwFileOffsetLow,
  SIZE_T dwNumberOfBytesToMap
);
```


CopyMemory function
Copies a block of memory from one location to another.

```
void CopyMemory(
  _In_       PVOID  Destination,
  _In_ const VOID   *Source,
  _In_       SIZE_T Length
);
```

UnmapViewOfFile function
Unmaps a mapped view of a file from the calling process's address space.

```
BOOL UnmapViewOfFile(
  LPCVOID lpBaseAddress
);
```

*/
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	cout << "\t\t....FILEMAPPING SERVER...." << endl;
	cout << endl;

	// Local Variable Definitions
	HANDLE	hFileMap;
	BOOL	bResult;
	PCHAR	lpBuffer = NULL;
	char	Buffer[1024] = "Hello from file map server";
	size_t	szBuffer = sizeof(Buffer);


	//STEP-1 CreateFileMapping
	hFileMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"Local\\MyFileMap");

	if (hFileMap == FALSE) {
		cout << "CreateFileMapping() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateFileMapping() Success" << endl;


	//STEP-2 MapViewofFile
	lpBuffer = (PCHAR)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256);
	if (lpBuffer == NULL) {
		cout << "MapViewOfFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "MapViewOfFile() Success" << endl;


	//STEP-3 CopyMemory function
	CopyMemory(lpBuffer, Buffer, szBuffer);


	//STEP-4 UnmapViewOfFile
	bResult = UnmapViewOfFile(lpBuffer);
	if (bResult == FALSE) {
		cout << "UnmapViewOfFile() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "UnmapViewOfFile() Success" << endl;


	system("PAUSE");
	return 0;
}

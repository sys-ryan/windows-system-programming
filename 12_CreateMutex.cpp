/*

1. Mutex is a locking Mechanism.
2. Mutex has only one state either Locked or Unlocked
3. Mutex has mutual ownership means those who caquire the lock only can release the lock.
4. If Mutex is locked mor than once in NON_RECURSIVE tehn DeaLock will occure
5. Mutex in only used for thead Synchronization.
6. In Windows:
		i.	Name Mutex
		ii. UnNamed Mutex



CreateMutex function
Creates or opens a named or unnamed mutex object.

```
HANDLE CreateMutex(
	LPSECURITY_ATTRIBUTES lpMutexAttributes,
	BOOL                  bInitialOwner,
	LPCTSTR                lpName
);
```

ReleaseMutex function
Releases ownership of the specified mutex object.

```
BOOL ReleaseMutex(
  HANDLE hMutex
);
```

OpenMutex function
Opens an existing named mutex object.

```
HANDLE OpenMutexW(
  DWORD   dwDesiredAccess,
  BOOL    bInheritHandle,
  LPCTSTR lpName
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	HANDLE hMutex;

	/*
	hMutex = CreateMutex(
		NULL,
		FALSE,
		NULL);		//UnNamed Mutex

	if (hMutex == NULL) {
		cout << "CreateMutex() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateMutex() Success" << endl;

	CloseHandle(hMutex);
	*/

	cout << "Mutex1" << endl;
	hMutex = CreateMutex(
		NULL,
		FALSE,
		L"MyMutex");	//Named Mutex


	if (hMutex == NULL) {
		cout << "CreateMutex() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateMutex() Success" << endl;

	getchar();

	//CloseHandle(hMutex);


	system("PAUSE");
	return 0;
}

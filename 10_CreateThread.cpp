/*
Thread is independent entity which runs within a process.

Note:
	1. Thread share some resources to process except STACK and REGISTER.
	2. By default, thread size in Windows OS is 1MB of STACK
	3. We can create 2048 MAX thread in a Process. (FROM MSDN)
	4. Terminating a thread does not necessarily remove the thread object from the operating system.
		A thread object is deleted when the las handle to the thread is closed.

CreateThread function

Creates a thread to execute within the virtual address space of the calling process.

```
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
  SIZE_T                  dwStackSize,
  LPTHREAD_START_ROUTINE  lpStartAddress,
  __drv_aliasesMem LPVOID lpParameter,
  DWORD                   dwCreationFlags,
  LPDWORD                 lpThreadId
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI Thread1Func(LPVOID lpParam) {
	while(1) {
		cout << "thread 1" << endl;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI Thread2Func(LPVOID lpParam) {
	while (1) {
		cout << "thread 2" << endl;
		Sleep(3000);
	}

	return 0;
}

int main() {

	HANDLE hThread1;
	HANDLE hThread2;
	DWORD ThreadID1;
	DWORD ThreadID2;

	hThread1 = CreateThread(
		NULL,
		0,
		Thread1Func,
		NULL,
		0,
		&ThreadID1
	);

	if (hThread1 == NULL) {
		cout << "CreateThread() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateThread() Success" << endl;
	cout << "Thread ID -> " << ThreadID1 << endl;



	hThread2 = CreateThread(
		NULL,
		0,
		Thread2Func,
		NULL,
		0,
		&ThreadID2
	);

	if (hThread2 == NULL) {
		cout << "CreateThread() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateThread() Success" << endl;
	cout << "Thread ID -> " << ThreadID2 << endl;


	CloseHandle(hThread1);
	CloseHandle(hThread2);

	system("PAUSE");
	return 0;
}

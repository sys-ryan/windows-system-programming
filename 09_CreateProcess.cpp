/*
CreateProcess function
Creates a new process and its primary thread. The new process runs in the security context of the calling process.

```
BOOL CreateProcessA(
  LPCTSTR               lpApplicationName,
  LPTSTR                lpCommandLine,
  LPSECURITY_ATTRIBUTES	lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCTSTR               lpCurrentDirectory,
  LPSTARTUPINFOA        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);
```


STARTUPINFOA structure
Specifies the window station, desktop, standard handles, and appearance of the main window for a process at creation time.

```
typedef struct _STARTUPINFOA {
  DWORD  cb;
  LPSTR  lpReserved;
  LPSTR  lpDesktop;
  LPSTR  lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;
```


PROCESS_INFORMATION structure
Contains information about a newly created process and its primary thread.

```
typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
```


WaitForSingleObject function
Waits until the specified object is in the signaled state or the time-out interval elapses.

```
DWORD WaitForSingleObject(
  HANDLE hHandle,
  DWORD  dwMilliseconds
);
```

*/
#include <Windows.h>
#include <iostream>

using namespace std;

int main() {

	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId = 0;
	DWORD dwThreadId = 0;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	BOOL bCreateProcess = NULL;
	bCreateProcess = CreateProcess(
		L"C:\\Program Files\\Windows Media Player\\wmplayer.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);

	if (bCreateProcess == FALSE) {
		cout << "Create Process Failed & Error No - " << GetLastError() << endl;
	}
	cout << "Create Process Success " << endl;
	cout << "Process ID -> " << pi.dwProcessId << endl;
	cout << "Thread ID -> " << pi.dwThreadId << endl;
	cout << "GetProcessID -> " << GetProcessId(pi.hProcess) << endl;
	cout << "GetThreadID -> " << GetThreadId(pi.hThread) << endl;

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;

}

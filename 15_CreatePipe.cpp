/*
IPC - It's a mechanism which is used for communicating between different processes.

PIPE - It's a IPC mechanism which is used for communicating the local process or different proccesses.
    1. It has two types
        i. Anonymous Pipe or unName Pipe.
        ii. Named Pipe


    UNNAMED or ANONYMOUS PIPE
    1. Used for One way communication or Unidirectional.
    2. Anonymous pipe is local to the system
    3. Anonymous pipe can not be used over the network.
    4. At the one end we can read/write and from other end we can read/write


■ CretePipe function
Creates an anonymous pipe, and returns handles to the read and write ends of the pipe.

```
BOOL CreatePipe(
  PHANDLE               hReadPipe,
  PHANDLE               hWritePipe,
  LPSECURITY_ATTRIBUTES lpPipeAttributes,
  DWORD                 nSize
);
```


■ WriteFile function
Writes data to the specified file or input/output (I/O) device.

```
BOOL WriteFile(
  HANDLE       hFile,
  LPCVOID      lpBuffer,
  DWORD        nNumberOfBytesToWrite,
  LPDWORD      lpNumberOfBytesWritten,
  LPOVERLAPPED lpOverlapped
);
```


■ ReadFile function
Reads data from the specified file or input/output (I/O) device. Reads occur at the position specified by the file pointer if supported by the device.

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
    BOOL bCreatePipe;
    HANDLE hRead;
    HANDLE hWrite;

    char szBuffer[512] = "Hello Pipe";
    DWORD dwBufferSize = sizeof(szBuffer);
    BOOL bWritefile;
    BOOL bReadfile;
    DWORD dwNoBytesWrite;
    DWORD dwNoBytesRead;



    bCreatePipe = CreatePipe(
        &hRead,
        &hWrite,
        NULL,
        dwBufferSize);
    if (bCreatePipe == FALSE) {
        cout << "CreatePipe() Failed & Error No - " << GetLastError() << endl;
    }
    cout << "CreatePipe() Success" << endl;

    bWritefile = WriteFile(
        hWrite,
        szBuffer,
        dwBufferSize,
        &dwNoBytesWrite,
        NULL);
    CloseHandle(hWrite);

    bReadfile = ReadFile(
        hRead,
        szBuffer,
        dwBufferSize,
        &dwNoBytesRead,
        NULL);

    cout << "Read from Pipe -> " << szBuffer << endl;
    CloseHandle(hRead);

    system("PAUSE");
    return 0;

}

/*
Thread Synchronization
    
    1. Printing Odd and Even Number Using Thread and Mutex
    2. Create Mutex
    3. Create Two Threads
    4. Create Thread func. In Thread func use WwaitForSingleObject and ReleaseMutex API.
    5. In Main function, use CloseHandle API.



■ WaitForSingleObject function
Waits until the specified object is in the signaled state or the time-out interval elapses.

```
DWORD WaitForSingleObject(
  HANDLE hHandle,
  DWORD  dwMilliseconds
);
```


■ WaitForMultipleObjects function
Waits until one or all of the specified objects are in the signaled state or the time-out interval elapses.

```
DWORD WaitForMultipleObjects(
  DWORD        nCount,
  const HANDLE *lpHandles,
  BOOL         bWaitAll,
  DWORD        dwMilliseconds
);
```


■ ReleaseMutex function
Releases ownership of the specified mutex object.

```
BOOL ReleaseMutex(
  HANDLE hMutex
);
```
*/


#include <Windows.h>
#include <iostream>

using namespace std;

HANDLE hMutex;
int gcount = 1;

DWORD WINAPI ThreadFun1(LPVOID lpParam){
    while(gcount <= 10){
        WaitForSingleObject(hMutex, INFINITE);
        if(gcount%2 == 0){
            cout << "thrad 1 - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID lpParam){
    while(gcount <= 10){
        WaitForSingleObject(hMutex, INFINITE);
        if(gcount%2 == 1){
            cout << "thread2 - " << gcount++ << endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

int main(){
    HANDLE hThread1, hThread2;
    
    cout << "Thread synchronization" << endl;

    hMutex = CreateMutex(
        NULL,
        FALSE,
        NULL);
    
    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFun1,
        NULL,
        0,
        NULL);

    hThread2 = CreateThread(
        NULL,
        0,
        ThreadFun2,
        NULL,
        0,
        NULL);
    
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    system("PAUSE");
    return 0;
}
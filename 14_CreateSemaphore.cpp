/*
SEMAPHORE

    1. Semaphore is an integer variable. (Mutex - Object)
    2. Semaphore is a Signalling Mechanism. (Mutex - Locking)
    3. Semaphore Value can be modified by WAIT & SIGNAl Operation. (Mutext - Either Locked Or Unlocked)
    4. Semaphore has two type (Mutex is not Categorized)
        i. Binary Semaphore
        ii. Counting Semaphore
    5. Semaphore value modified by any process by Acquiring or Releasing the Semaphore.
        (Mutex - Those who acquired the lock only can release the lock i.e Mutual Ownership)

■ CreateSemaphore function
Creates or opens a named or unnamed semaphore object.


```
HANDLE CreateSemaphore(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCTSTR               lpName
);
```


■ OpenSemaphore function
Opens an existing named semaphore object.

```
HANDLE OpenSemaphore(
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
    HANDLE hSem;
    hSem = CreateSemaphore(
        NULL,
        1,
        1,
        L"MySemaphore");

    if (hSem == NULL) {
        cout << "CreateSemaphore() Failed & Error No - " << GetLastError() << endl;
    }
    cout << "CreateSemaphore() Sucess!" << endl;


    getchar();

    CloseHandle(hSem);
    system("PAUSE");
    return 0;
}

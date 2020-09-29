/*
■ CRITICAL_SECTION in Windows 

	- Critical section is a region of code where code need to be executed atomically or indivisible operation. 
	- Critical section is used for synchronization 
	- It provides a lock similar to Mutex
	- Process si only responsible for allocating the memory used by Ciritical Section 

	Example
		do {
			Entry_Section() 
				//Critical Section
			Exit_Section()

			//Rest of the Code 
		} while(TRUE); 

■ Differences betweeen CRITICAL_SECTION & MUTEX
	
	- Critical Section
		1. CS object is not shared by Processes.
		2. CS is used by only the thread of a single process.
		3. It doesn ot communicate with Kernel.
		4. It is slightly faster than Event, Mutex and Semaphore. 

	- Mutex
		1. Mutex Ojbect is shared by Processes.
		2. Iti s used by mroe than one Process.
		3. It may communicate with Kernel.
		4. It is slower and may lead to deadlock. 


■ CRITICAL_SECTION API's 

	1. InitializeCriticalSection
	2. InitializeCritialSectionAndSpinCount
	3. EnterCriticalSection
	4. TryEnterCriticalSection
	5. LeaveCriticalSectionSpinCount
	6. SetCriticalSectionSpinCount
	7. DeleteCriticalSection 



InitializeCriticalSection function
Initializes a critical section object.

```
void InitializeCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);
```


EnterCriticalSection function
Waits for ownership of the specified critical section object. 
The function returns when the calling thread is granted ownership.

```
void EnterCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);
```


LeaveCriticalSection function
Releases ownership of the specified critical section object.

```
void LeaveCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);
```



DeleteCriticalSection function
Releases all resources used by an unowned critical section object.

```
void DeleteCriticalSection(
  LPCRITICAL_SECTION lpCriticalSection
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global varaible
int gcount = 1;
CRITICAL_SECTION cs;

//Thread Function
DWORD WINAPI ThreadFuncEven(LPVOID lpParam) {
	while (gcount < 10) {
		EnterCriticalSection(&cs);
		if (gcount % 2 == 0) {
			cout << "EVEN - " << gcount++ << endl;
		}
		LeaveCriticalSection(&cs);
	}
	
	return 0;
}

DWORD WINAPI ThreadFuncOdd(LPVOID lpParam) {
	while (gcount < 10) {
		EnterCriticalSection(&cs);
		if (gcount % 2 == 1) {
			cout << "ODD - " << gcount++ << endl;
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int main() {
	cout << "\t\t ---- CRITICAL_SECTION ---- " << endl;
	

	//Local variable
	HANDLE hThread1, hThread2;

	//STEP-1 Initialize the CRITICAL_SECTION
	InitializeCriticalSection(&cs);

	
	//STEP-2 CreateThread() 
	hThread1 = CreateThread(
		NULL,
		0,
		ThreadFuncEven,
		NULL,
		0,
		NULL);

	hThread2 = CreateThread(
		NULL,
		0,
		ThreadFuncOdd,
		NULL,
		0,
		NULL);


	//STEP-3 Wait for Signaled Object
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);


	//STEP-4 Closing the Handle of thread
	CloseHandle(hThread1);
	CloseHandle(hThread2);


	//STEP-5 Deleting the Critical Section obejct
	DeleteCriticalSection(&cs);


	system("PAUSE");
	return 0;
}
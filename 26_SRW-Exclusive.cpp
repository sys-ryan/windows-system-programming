/*
SLIM-READER-WRITER LOCKS in Windows OS

	1. Slim Reader-Writer(SRW) lock is another variant of Critical Section in Windoos
	2. Only difference is SRW locks allow multiple Reader threads at the same time.
	3. Generally we will be having multiple reader thread and single writer thread then
		- if we are using CS for the synchronization of thread
		  then each reader thread will have to wait for the other reader thread to leave the CS

		- But if we are using SRW lock then It allow multiple reader threads at the same time.

	4. More concurrency on Multi-processor system .
	5. SRW Locks cannot be shared between processes.
	6. SRW is a user object not a kernel object
	7. Thy don't allow recursive locks (CS and mutext allows it.)


	SRW Locks provide two Modes for sharing the resources.

		1. Exclusive Mode
		2. Shared Mode


Slim Reader-Writer Lock in Exclusive Mode

	1. When the lock has been acquired, no other threads can access the resources until writer release the lock.
	2. It allows read/write access to one writer thread at a time.



	- When Writer thread is writing then reader thread will wait until writer thread release the lock.
	- When Reader thread is reading then Writer thread will wait until reader thread release the lock.
	- Assume there is 1-Writer thread and 2-Reader threads in Exclusive mode then reader threads can access the resources sequentially.
	  But not recommendable.



Exclusive Slim Reader - Writer Lock APIs

	1. InitializeSRWLock
	2. AcqurieSRWLockExclusive
	3. ReleaseSRWLockExclusive
	4. TryAcquireSRWLockExclusive



Slim Reader/Writer (SRW) Locks [MSDN]
Slim reader/writer (SRW) locks enable the threads of a single process to access shared resources; 
they are optimized for speed and occupy very little memory. 
Slim reader-writer locks cannot be shared across processes.

The caller must allocate an SRWLOCK structure and initialize it by either calling InitializeSRWLock (to initialize the structure dynamically) 
or assign the constant SRWLOCK_INIT to the structure variable (to initialize the structure statically).


AcquireSRWLockExclusive function
Acquires a slim reader/writer (SRW) lock in exclusive mode.

```
void AcquireSRWLockExclusive(
  PSRWLOCK SRWLock
);
```


ReleaseSRWLockExclusive function
Releases a slim reader/writer (SRW) lock that was acquired in exclusive mode.

```
void ReleaseSRWLockExclusive(
  PSRWLOCK SRWLock
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global Variable 
SRWLOCK lock;
int flag = 0;
int x = 0;


//Thread function for writer and reader thread
DWORD WINAPI WriterThread(LPVOID lpvoid) {
	
	while (1) {
		AcquireSRWLockExclusive(&lock);
		x += 5;
		cout << "Writer : " << x << endl;
		ReleaseSRWLockExclusive(&lock);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI ReaderThread(LPVOID lpvoid) {
	
	while (1) {
		AcquireSRWLockExclusive(&lock);
		++flag;
		if (flag == 1) {
			cout << "Reader : " << x << endl;

		}
		--flag;
		ReleaseSRWLockExclusive(&lock);
		Sleep(1000);
	}
	return 0;
}


int main() {

	//Local variable
	HANDLE hWriter;
	HANDLE hReader; 

	
	//STPE-1 Initialize SRW Lock 
	InitializeSRWLock(&lock);


	//STEP-2 CreateThread function for writer and reader 
	hWriter = CreateThread(
		NULL,
		0,
		&WriterThread,
		NULL,
		0,
		0);
	
	hReader = CreateThread(
		NULL,
		0,
		&ReaderThread,
		NULL,
		0,
		0);

	
	//STEP-3 WaitForSingleObject for writer and reader threads
	WaitForSingleObject(hWriter, INFINITE);
	WaitForSingleObject(hReader, INFINITE);


	//STEP-4 CloseHandle for Writer and Reader Threads
	CloseHandle(hWriter);
	CloseHandle(hReader);

	system("PAUSE");
	return 0;

}
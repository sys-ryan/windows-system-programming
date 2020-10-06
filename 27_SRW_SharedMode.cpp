/*
Simple Reader-Writer Lock - Shared Mode 
	
	- Read only access to multiple reader threads. 
	- Reading the data from shared resources concurrently
	- so, performance and throughput increases compared to ciritical section. 


	In SRW Lock, Only writer thread is in Exclusive mode and Reader Threads is in Shared mode. 
	Multiple Reader threads access the resources at the same time. 


Difference between Critical Section and SRW Lock. 

	<SRW Lock> 

		- 8 bytes of memory in 64bit OS
		- Execution is fast
		- Multiple readers executes in parallel.
		- Non- Reentrant
		- Writer Starvation 


	<Critical Section> 

		- 40 Bytes of memory in 64bit OS
		- Execution is Slower 
		- Multiple Readers can't execute in Parallel. 
		- Reentrant
		- No writer starvation 


Reader-Writer problem with Writer Priority 
	
	* Writer 
	
		AcquireLock
		// -- Write Something -- // 
		ReleasetheLock 
		Signal for Reader 


	* Reader 
	
		AcquireLock
			readercount++ // global cariable initialized with 0 
		if(readercount == 1){  // the first reader  
			writer will sleep
		}

		ReleaseLock 

		// --- Reading will start here --- // 

		AcquireLock
		readercount--
		if(readercount == 0){  // the last reader 
			Writer will try to acquire the lock for writing 
		}
		ReleaseLock 
		signal for writer 


Windows APIs for SRW Lock-shared mode 

	1. InitializeSRWLock
	2. AcquireSRWLockShared 
	3. SleepConditionVariableSRW
	4. TryAcquireSRWLockShared 
	5. ReleaseSRWLockkShared
	6. WakeAllConditionalVariable 



AcquireSRWLockShared function 
Acquires a slim reader/writer (SRW) lock in shared mode.


```
void AcquireSRWLockShared(
  PSRWLOCK SRWLock
);
```


SleepConditionVariableSRW function
Sleeps on the specified condition variable and releases the specified lock as an atomic operation.

```
BOOL SleepConditionVariableSRW(
  PCONDITION_VARIABLE ConditionVariable,
  PSRWLOCK            SRWLock,
  DWORD               dwMilliseconds,
  ULONG               Flags
);
```


WakeAllConditionVariable function
Wake all threads waiting on the specified condition variable.

```
void WakeAllConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global variable 
CONDITION_VARIABLE cvw;
CONDITION_VARIABLE cvr;
SRWLOCK lock;
int x = 0;
int readercount = 0;

DWORD WINAPI WriterThread(LPVOID lpvoid) {
	while (1) {
		AcquireSRWLockShared(&lock);
		x += 5;
		cout << "Writer = " << x << endl;
		ReleaseSRWLockShared(&lock);
		WakeConditionVariable(&cvr);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI ReaderThread(LPVOID lpvoid) {
	while (1) {
		AcquireSRWLockShared(&lock);
		++readercount;
		if (readercount == 1) {
			SleepConditionVariableSRW(&cvw, &lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED);
		}
		ReleaseSRWLockShared(&lock); // 위에서 락  해제했는데 또 ?? 

		cout << "Reader = " << x << endl;

		AcquireSRWLockShared(&lock);
		--readercount;
		if (readercount == 0) {
			TryAcquireSRWLockShared(&lock);
		}
		ReleaseSRWLockShared(&lock);
		WakeConditionVariable(&cvw);
		Sleep(1000);
	}
	return 0;
}

int main() {

	//Local variable 
	HANDLE hWriter;
	HANDLE hReader[2]; 


	//STEP-1 Initialize conditional variable for Writer and Reader 
	InitializeConditionVariable(&cvw);
	InitializeConditionVariable(&cvr);


	//STEP-2 Initialize SRW Lock 
	InitializeSRWLock(&lock);


	//STEP-3 Create WRiter Thread 
	hWriter = CreateThread(
		NULL,
		0,
		&WriterThread,
		NULL,
		0,
		0);


	//STEP-4 Create 2 Reader Thread 
	for (int i = 0; i < 2; i++) {
		hReader[i] = CreateThread(
			NULL,
			0,
			&ReaderThread,
			NULL,
			0,
			0);
	}


	//STEP-5 Wake up all conditional variable 
	WakeAllConditionVariable(&cvw);
	WakeAllConditionVariable(&cvr);

	
	//STEP6 Wait for Single object for reader and writer 
	WaitForSingleObject(hWriter, INFINITE);
	for (int i = 0; i < 2; i++) {
		WaitForSingleObject(hReader[i], INFINITE);
	}

	
	//STEP-7 Close Handle for WriterThrad & ReaderThread
	CloseHandle(hWriter);
	for (int i = 0; i < 2; i++) {
		CloseHandle(hReader[i]);
	}

	system("PAUSE");
	return 0;

}
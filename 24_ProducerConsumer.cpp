/*
Condition Variables in Windows OS

	1. Condition variables is a synchronization method.
	2. It is a User mode object so cannot be shared across different Process.
	3. It allows thread to wait until particular condition is satisfied.
	4. Conditional variable is just a Boolean value under 'if condition'.


	CONDITGIONAL VARIABLE

		1. Provide atomicity for the unlock/lock and sleep operations.
		2. Sometimes we want to block until some condition is met.
		3. Automatically and atomically unlocks mutex or semaphore and then calls sleep function and wait it to be automatically relocked.

	MUTEX

		1. Mutexes are good for controlling access to a critical region
		2. In mutex, if we call sleep function then it will become race condition.

	SEMAPHORE

		1. Semaphores are good for situations where counting is needed.
		2. In Semaphore, if we call sleep function then it will become race condition.



PRODUCER-CONSUMER PROBLEM

	Producer - Produce until buffer is full.
				When the buffer is full, then it will go in sleep mode.

	Consumer - Consume until buffer is empty.
				When buffer is empty then it will go in sleep mode.


	Windows API 
		
		1. InitializeConditionVariable()
		2. SleepConditionVariableCS()
		3. WakeConditionVariable()
		4. WakeAllConditionVariable() 


InitializeConditionVariable function
Initializes a condition variable.

```
void InitializeConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
);
```


SleepConditionVariableCS function	
Sleeps on the specified condition variable and releases the specified critical section as an atomic operation

```
BOOL SleepConditionVariableCS(
  PCONDITION_VARIABLE ConditionVariable,
  PCRITICAL_SECTION   CriticalSection,
  DWORD               dwMilliseconds
);
```

WakeConditionVariable function
Wake a single thread waiting on the specified condition variable.

```
void WakeConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
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

CRITICAL_SECTION cs;
CONDITION_VARIABLE cv; 

int buffer = 0;
int max_items[20];

DWORD WINAPI ProducerThread(LPVOID lpvoid) {

	for (int i = 0; i < 20; i++) {
		
		EnterCriticalSection(&cs);
		while (buffer == 20)
			SleepConditionVariableCS(&cv, &cs, INFINITE);

		buffer++;
		cout << "Producer = " << buffer << endl;
		Sleep(1000);
		WakeConditionVariable(&cv);
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI ConsumerThread(LPVOID lpvoid) {

	for (int i = 0; i < 20; i++) {
			
		EnterCriticalSection(&cs);
		
		while(buffer == 0) 
			SleepConditionVariableCS(&cv, &cs, INFINITE);

		cout << "Consumer = " << buffer << endl;
		buffer--;
		
		WakeConditionVariable(&cv);
		LeaveCriticalSection(&cs);
	}

	return 0;
}


int main() {

	//Handle for thread
	HANDLE hProducer, hConsumer; 

	
	//Initialize Critical Section 
	InitializeCriticalSection(&cs);


	//STEP-1 Initialize Conditional variable
	InitializeConditionVariable(&cv);


	//STEP-2 Create Producer and Consumer Thread 
	hProducer = CreateThread(
		NULL,
		0,
		&ProducerThread,
		NULL,
		0,
		0);

	hConsumer = CreateThread(
		NULL,
		0,
		&ConsumerThread,
		NULL,
		0,
		0);


	//STEP-3 Wawke All Conditional Variable 
	WakeAllConditionVariable(&cv);


	//STEP-4 Wait for single ojbect for Thread 
	WaitForSingleObject(hProducer, INFINITE);
	WaitForSingleObject(hConsumer, INFINITE);

	system("PAUSE");
	return 0;
}
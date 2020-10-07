/*
Synchronization Barriers

A synchronization barrier enables multiple threads to wait until all threads have all reached a particular point of execution before any thread continues.
Synchronization barriers cannot be shared across processes.

Synchronization barriers are useful for phased computations, in which threads executing the same code in parallel must all complete one phase before moving on to the next.

To create a synchronization barrier, call the `InitializeSynchronizationBarrier` function 
and specify a maximum number of threads and how many times a thread should spin before it blocks.
Then launch the threads that will use the barrier.
After each thread finishes its work, it calls `EnterSynchronizationBarrier` to wait at the barrier.
The EnterSynchronizationBarrier function blocks each thread until the number of threads blocked in the barrier reaches the maximum thread count for the barrier, at which point EnterSynchronizationBarrier unblocks all the threads.
The EnterSynchronizationBarrier function returns TRUE for exactly one of the threads that entered the barrier, and returns FALSE for all other threads.

To release a synchronization barrier when it is no longer needed, call `DeleteSynchronizationBarrier`.
It is safe to call this function immediately after calling EnterSynchronizationBarrier because that function ensures that all threads have finished using the barrier before it is released.

If a synchronization barrier will never be deleted, threads can specify the `SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE` flag when they enter the barrier.
All threads using the barrier must specify this flag; if any thread does not, the flag is ignored.
This flag causes the function to skip the extra work required for deletion safety, which can improve performance.
Note that deleting a barrier while this flag is in effect may result in an invalid handle access and one or more permanently blocked threads.



InitializeSynchronizationBarrier function 
Initializes a new synchronization barrier.

```
BOOL InitializeSynchronizationBarrier(
  LPSYNCHRONIZATION_BARRIER lpBarrier,
  LONG                      lTotalThreads,
  LONG                      lSpinCount
);
```

EnterSynchronizationBarrier function
Causes the calling thread to wait at a synchronization barrier until the maximum number of threads have entered the barrier.

```
BOOL EnterSynchronizationBarrier(
  LPSYNCHRONIZATION_BARRIER lpBarrier,
  DWORD                     dwFlags
);
```

	** dwFlags

		- SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY	
			Specifies that the thread entering the barrier should block immediately until the last thread enters the barrier.

		- SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY
			Specifies that the thread entering the barrier should spin until the last thread enters the barrier, even if the spinning thread exceeds the barrier's maximum spin count.

		- SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE
			Specifies that the function can skip the work required to ensure that it is safe to delete the barrier, which can improve performance. 
			All threads that enter this barrier must specify the flag; otherwise, the flag is ignored. This flag should be used only if the barrier will never be deleted
*/

#include <Windows.h>
#include <iostream>
using namespace std;

//Global Variable
SYNCHRONIZATION_BARRIER sb;
int x = 5;

//Thread-1 Function
DWORD WINAPI Thread1_function(LPVOID lpvoid) {
	Sleep(5000);
	cout << "Thrad1 ready" << endl;
	EnterSynchronizationBarrier(&sb, SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);
	cout << "Thread1 : " << ++x << endl;
	
	DeleteSynchronizationBarrier(&sb);
	return 0;
}

//Thread-2 Function
DWORD WINAPI Thread2_function(LPVOID lpvoid) {
	Sleep(2000);
	cout << "Thrad2 ready" << endl;
	EnterSynchronizationBarrier(&sb, SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);
	cout << "Thread2 : " << ++x << endl;

	DeleteSynchronizationBarrier(&sb);
	return 0;
}

int main() {

	//Local Variable
	HANDLE Thread1, Thread2;


	//STEP-1 Initialize the Synchronization Barrier 
	InitializeSynchronizationBarrier(&sb, 2, SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);
	

	//STEP-2 Create Two Thread 
	Thread1 = CreateThread(
		NULL,
		0,
		&Thread1_function,
		NULL,
		0,
		0);

	Thread2 = CreateThread(
		NULL,
		0,
		&Thread2_function,
		NULL,
		0,
		0);


	//STEP-3 Wait for single object for Thread1 and Thread2 
	WaitForSingleObject(Thread1, INFINITE);
	WaitForSingleObject(Thread2, INFINITE);


	//STEP-4 Close Handle for Thrad1 and Thread2 
	CloseHandle(Thread1);
	CloseHandle(Thread2);

	system("PAUSE");
	return 0;
}
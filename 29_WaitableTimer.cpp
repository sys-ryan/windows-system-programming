/*
A waitable timer object is a synchronization object whose state is set to signaled when the specified due time arrives. There are two types of waitable timers that can be created: manual-reset and synchronization. A timer of either type can also be a periodic timer.

- manual-reset timer
   A timer whose state remains signaled until SetWaitableTimer is called to establish a new due time.

- synchronization timer
   A timer whose state remains signaled until a thread completes a wait operation on the timer object.

- periodic timer
   A timer that is reactivated each time the specified period expires, until the timer is reset or canceled. A periodic timer is either a periodic manual-reset timer or a periodic synchronization timer.


When a timer is signaled, the processor must run to process the associated instructions.


A thread uses the CreateWaitableTimer or CreateWaitableTimerEx function to create a timer object.
The creating thread can specify a name for the timer object. Threads in other processes can open a handle to an existing timer by specifying its name in a call to the OpenWaitableTimer function.
Any thread with a handle to a timer object can use one of the wait functions to wait for the timer state to be set to signaled.

The thread calls the SetWaitableTimer function to activate the timer.

A thread can use the CancelWaitableTimer function to set the timer to the inactive state.

When you are finished with the timer object, call CloseHandle to close the handle to the timer object.


The behavior of a waitable timer can be summarized as follows:

□ When a timer is set, it is canceled if it was already active, the state of the timer is nonsignaled, and the timer is placed in the kernel timer queue.
□ When a timer expires, the timer is set to the signaled state. If the timer has a completion routine, it is queued to the thread that set the timer. The completion routine remains in the asynchronous procedure call (APC) queue of the thread until the thread enters an alertable wait state. At that time, the APC is dispatched and the completion routine is called. If the timer is periodic, it is placed back in the kernel timer queue.
□ When a timer is canceled, it is removed from the kernel timer queue if it was pending. If the timer had expired and there is still an APC queued to the thread that set the timer, the APC is removed from the thread's APC queue. The signaled state of the timer is not affected.


Windows APIs
   1. CreateWaitableTimer
   2. SetWaitableTimer
   3. OpenWaitableTimer
   4. WaitForSingleObject
   5. CancelWaitableTimer
   6. CloseHandle


LARGE_INTEGER union
Represents a 64-bit signed integer value.

```
typedef union _LARGE_INTEGER {
  struct {
   DWORD LowPart;
   LONG  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
   DWORD LowPart;
   LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;
```
*/

#include <Windows.h>
#include <iostream> //Waitable timer

using namespace std;

HANDLE hTimer = NULL;
DWORD dWaitForSingleObject;

//Thread function
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
   dWaitForSingleObject = WaitForSingleObject(hTimer, INFINITE);
   if (dWaitForSingleObject == WAIT_FAILED) {
      cout << "WaitForSingleObject() Failed & Error no - " << GetLastError() << endl;
   }
   else {
      cout << "Timer Signaled after 5 sec..." << endl;
   }

   cout << "Thread running" << endl;
   return 0;
}

int main() {
   //Local Variable 
   HANDLE hThread;
   BOOL bSetWaitableTimer = FALSE;


   LARGE_INTEGER liDueTime;
   liDueTime.QuadPart = -50000000LL;


   //STEP-1 Create Waitable Tiemr
   hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
   if (hTimer == NULL) {
      cout << "CreateWaitableTimer() Failed & Error no - " << GetLastError() << endl;
   }
   cout << "CreateWaitableTimer() Success" << endl;

   //Thread 
   hThread = CreateThread(
      NULL,
      0,
      ThreadFunction,
      NULL,
      0,
      NULL);

   //STEP-2 SetWaitableTimer function 
   bSetWaitableTimer = SetWaitableTimer(
      hTimer,
      &liDueTime,
      0,
      NULL,
      NULL,
      0);

   if (bSetWaitableTimer == FALSE) {
      cout << "SetWaitableTimer() Failed & Error no - " << GetLastError() << endl;
   }
   cout << "SetWaitableTimer() Success" << endl;


   //STEP-3 Printing Output
   cout << "Waiting for 5 sec..." << endl;


   //STEP-4 WaitForSingleObject
   WaitForSingleObject(hThread, INFINITE);
   /*dWaitForSingleObject = WaitForSingleObject(hTimer, INFINITE);
   if(dWaitForSingleObject == WAIT_FAILED){
      cout << "WaitForSingleObject() Failed & Error no - " << GetLastError() << endl;
   }else {
      cout << "Timer Signaled after 5 sec..." << endl;
   }*/


   //STEP-5 CloseHandle
   CloseHandle(hTimer);
   CloseHandle(hThread);

   system("PAUSE");
   return 0;
}
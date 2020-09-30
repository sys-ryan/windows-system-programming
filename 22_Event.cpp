/*
■ Event

	Event is an action or occurrence. 
	Event can be either user action or system occurrence. 

	EX) Mouse being clicked, key being pressed from keyboard, System running of memory ..


	- Event Handler
		Event handler is a routine (function) that is used to deal with an event

	- Event Driven Program
		A program is designen dto react. 
		Ex) react to specific kind of user input etc. 


	In Windows, Event can be: 
		
		1. Manual Reset Event
		2. Auto Reset Event 

	The s tate of an event can be:
	
		1. Signaled
		2. Non-signaled 


	Event API's
	
		1. CreateEvent
		2. OpenEvent
		3. SetEvent
		4. ResetEvent


■ Difference between Event & Interrupt

	- Event
		1. Event occur at any specific point of time
		2. When events occurs the program code has prepared to take action
		3. There is no need for Event handler to save and restore state of program because this is a compiler defined place and always interact with main program.
		4. Event may take more time to respond because theyt are taken by invitation only. 

	- Interrupt
		1. Interrupts may occur any time.
		2. Interrupts halt the program to let some other code execute
		3. When an interrupt happens, code save the state of program and is careful not to interact with main program. 
		4. Interrupt ahs predictable timing and predictable state. 





▶ CreateEVent function 
Creates or opens a named or unnamed event object.

```
HANDLE CreateEventA(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCTSTR                lpName
);
```

▶ SetEvent function
Sets the specified event object to the signaled state.

```
BOOL SetEvent(
  HANDLE hEvent
);
```
*/



#include <Windows.h>
#include <iostream>

using namespace std;

//Global variable 
HANDLE hEvent; 

//Thread function 
DWORD WINAPI ThreadFunc1(LPVOID lpParam) {
	WaitForSingleObject(hEvent, INFINITE);		//Wait until the state of the Event is TRUE
	cout << "Thread-1 Running" << endl;
	return 0;
}

DWORD WINAPI ThreadFunc2(LPVOID lpParam) {
	cout << "Thread-2 Running" << endl;
	SetEvent(hEvent);		// Change the state of the Event  (Event = TRUE)
	return 0;
}


int main() {
	HANDLE hThread1, hThread2;
	DWORD ThreadID1, ThreadID2; 

	
	//STEP-1 Create an Event 
	hEvent = CreateEvent(
		NULL,
		FALSE,
		FALSE,		//Initial State of the Event == FALSE
		L"MyEvent");
	
	if (hEvent == NULL) {
		cout << "CreateEvent() Failed & Error no - " << GetLastError() << endl;
	}
	cout << "CreateEvent() Success" << endl;
	
	//STEP-2 Thread Creation
	hThread1 = CreateThread(
		NULL,
		0,
		ThreadFunc1,
		NULL,
		0,
		&ThreadID1);

	if (hThread1 == NULL) {
		cout << "CreateThread() Failed & Error no - " << GetLastError() << endl;
	}
	
	hThread2 = CreateThread(
		NULL,
		0,
		ThreadFunc2,
		NULL,
		0,
		&ThreadID2);

	if (hThread2 == NULL) {
		cout << "CreateThread() Failed & Error no - " << GetLastError() << endl;
	}


	//STEP-3 WaitForSingleOBject - Waits until the object is in the signaled state 
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);


	//STEP-4 CloseHandle - Close the handle of Thread and Event 
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	CloseHandle(hEvent);

	system("PAUSE");
	return 0;
}
/*
Manual Reset Event
This type of Event is waiting for particular event to occur until explicit call to resetting the event in non signaled state.

	For Manual Reset, Explicitly call to `ResetEvent()` API

	In Create Evnet API
	-> bManualReset = TRUE

*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global variable
HANDLE hEvent;

//Thread function
DWORD WINAPI ThreadFunc1(LPVOID lpParam) {
	HANDLE hOpenEvent;
	hOpenEvent = OpenEvent(
		EVENT_ALL_ACCESS,
		FALSE,
		L"MyEvent");

	if (hOpenEvent == FALSE) {
		cout << "OpenEvent() Failed & Error No - " << GetLastError() << endl;
	}
	cout << "OpenEvent() Success " << endl;

	for (int i = 1; i <= 2; i++) {
		WaitForSingleObject(hEvent, INFINITE);
		ResetEvent(hOpenEvent);
		cout << "Got Signaled = " << i << endl;
	}

	cout << "Thread-1 Running" << endl;
	CloseHandle(hOpenEvent);
	return 0;
}


DWORD WINAPI ThreadFunc2(LPVOID lpParam) {
	cout << "Thread-2 Running" << endl;
	for (int i = 1; i <= 2; i++) {
		SetEvent(hEvent);
		Sleep(2000);
	}
	return 0;
}
int main() {

	cout << "\t\t ---- AUTO RESET EVENT ---- " << endl;
	cout << endl;

	HANDLE hThread1, hThread2;
	DWORD ThreadID1, ThreadID2;

	//STEP-1 Create an Event 
	hEvent = CreateEvent(
		NULL,
		TRUE,		//MANUAL_RESET
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
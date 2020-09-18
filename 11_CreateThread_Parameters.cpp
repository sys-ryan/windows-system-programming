#include <Windows.h>
#include <iostream>

using namespace std;

int a[2];

DWORD WINAPI ThreadFun(LPVOID lpParam) {

	int x, y, result;
	x = a[0];
	y = a[1];

	result = x + y;

	cout << "Addition = " << result << endl;
	return 0;
}

int main() {
	HANDLE hThread;
	DWORD ThreadID;

	cout << "Enter Your 1st No." << endl;
	cin >> a[0];

	cout << "Enter Your 2nd No." << endl;
	cin >> a[1];

	hThread = CreateThread(
		NULL,
		0,
		ThreadFun,
		(void*)& a,          // (void*) : PVOID ThreadParameter 
		0,
		&ThreadID);

	if (hThread == NULL) {
		cout << "CreateThread() Failed & Error No - " << GetLastError() << endl;
	}

	cout << "Thread Creation Success" << endl;

	CloseHandle(hThread);

}
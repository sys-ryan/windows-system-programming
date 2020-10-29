#include <Windows.h>
#include <iostream> 

using namespace std;

//Global Handle for Semaphore and Mutex
HANDLE hSemaphore;
HANDLE hMutex;
int i = 0;

//Thread function
DWORD WINAPI MySyncFunction(LPVOID lpParam) {
    while (i < 20) {
        WaitForSingleObject(hSemaphore, INFINITE);
        WaitForSingleObject(hMutex, INFINITE); // Mutex Lock
        cout << "Count = " << i++ << endl;
        ReleaseMutex(hMutex); //Mutex Unlock
        ReleaseSemaphore(hSemaphore, 1, 0);

    }
    return 0;
}


int main() {
    //Local Variable 
    HANDLE hThread1;
    HANDLE hThread2;


    //STEP-1 Create Semaphore
    hSemaphore = CreateSemaphore(
        NULL, //Security Attributes
        2, //Initial Count
        2, //Max count,
        NULL); //Semaphore Name
    if (hSemaphore == NULL) {
        cout << "Semaphore Creation Faield && Error no - " << GetLastError() << endl;
    }
    cout << "Semaphore Creation Success" << endl;


    //STEP-2 Mutex Creation 
    hMutex = CreateMutex(
        NULL, //Security Attributes
        FALSE, //Ownership
        NULL);

    if (hMutex == NULL) {
        cout << "Mutex Creation Faield & Error no - " << GetLastError() << endl;
    }
    cout << "Mutex Creation Succes" << endl;


    //STEP-3 Create 2 Threads 
    hThread1 = CreateThread(
        NULL, //Security Attributes
        0, //Stack Size
        &MySyncFunction, //Thread Startup Function
        NULL, //Thread Parameter
        0, //Creation flag
        0); //Thread ID

    hThread2 = CreateThread(
        NULL,
        0,
        &MySyncFunction,
        NULL,
        0,
        0);


    //STEP-4 Wait for Single Object for All threads
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);


    //STEP-5 CloseHandle for Thread
    CloseHandle(hThread1);
    CloseHandle(hThread2);


    //STEP-6 CloseHandle for Mutex
    CloseHandle(hMutex);


    //STEP-7 CloseHandle for Semaphore
    CloseHandle(hSemaphore);


    system("PAUSE");
    return 0;
}
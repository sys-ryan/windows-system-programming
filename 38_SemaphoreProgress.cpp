/*
In Cooperative process, synchronization is very important. 
Semaphore is easy to use in this case. 
Only some process come in Critical section and rest of toehr processes are independent to critical section. 

Let's assume we want to execute process in the order of 'P4->P2->p1->p3'.

P4 {
    execute
    Signal(S1)
}

P2 {
    Wait(S1)
    execute
    Signal(S2)
}

P1 {
    Wait(S2)
    execute
    Signal(S3)
}

P3 {
    Wait(S3)
    execute
}


Windows APIs
1. CreateSemaphore()
2. ReleaseSemaphore()
3. WaitforSingleObject()
4. CreateThread()
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global Handle for Semaphore
HANDLE hSemaphore1;
HANDLE hSemaphore2;
HANDLE hSemaphore3;

//Thread functions
DWORD WINAPI ThreadFunction1(LPVOID lpParam){
    WaitForSingleObject(hSemaphore2, INFINITE);
    cout << "\nThread-1" << endl;
    ReleaseSemaphore(hSemaphore3, 1, 0);
    return 0;   
}

DWORD WINAPI ThreadFunction2(LPVOID lpParam){
    WaitForSingleObject(hSemaphore1, INFINITE);
    cout << "\nThread-2" << endl;
    ReleaseSemaphore(hSemaphore2, 1, 0);    
    return 0;   
}

DWORD WINAPI ThreadFunction3(LPVOID lpParam){
    WaitForSingleObject(hSemaphore3, INFINITE);
    cout << "\nThread-3" << endl;
    return 0;   
}

DWORD WINAPI ThreadFunction4(LPVOID lpParam){
    cout << "Thread-4" << endl;
    ReleaseSemaphore(hSemaphore1, 1, 0);   
    return 0;   
}


int main(){
    //Handle for Threads
    HANDLE hThread1;
    HANDLE hThread2;
    HANDLE hThread3;
    HANDLE hThread4;


    //STEP-1 Create 3 Semaphores Initialized with 0
    hSemaphore1 = CreateSemaphore(
        NULL, //Security Attributes
        0, //Initial Count -> Semaphore Initialization 
        1, //Max count 
        NULL); //Semaphore name 

    if(hSemaphore1 == NULL){
        cout << "Semaphore Creation failed & Error no - " << GetLastError() << endl;
    }
    cout << "Semaphore1 Creation Success" << endl;

    hSemaphore2 = CreateSemaphore(
        NULL, //Security Attributes
        0, //Initial Count -> Semaphore Initialization 
        1, //Max count 
        NULL); //Semaphore name 

    if(hSemaphore2 == NULL) { 
        cout << "Semaphore Creation failed & Error no - " << GetLastError() << endl;
    }
    cout << "Semaphore2 Creation Success" << endl;
    hSemaphore3 = CreateSemaphore(
        NULL, //Security Attributes
        0, //Initial Count -> Semaphore Initialization 
        1, //Max count 
        NULL); //Semaphore name 

    if(hSemaphore3 == NULL) {
        cout << "Semaphore Creation faield & Error no - " << GetLastError() << endl;
    }
    cout << "Semaphore3 Creation Success" << endl;


    //STEP-2 Create 4 Threads
    hThread1 = CreateThread(
        NULL, //Security Attributes
        0, //Stack size -> Default stack size
        &ThreadFunction1, //Thread start function name
        NULL,
        0,
        0);

    hThread2 = CreateThread(
        NULL, //Security Attributes
        0, //Stack size -> Default stack size
        &ThreadFunction2, //Thread start function name
        NULL,
        0,
        0);

    hThread3= CreateThread(
        NULL, //Security Attributes
        0, //Stack size -> Default stack size
        &ThreadFunction3, //Thread start function name
        NULL,
        0,
        0);

    hThread4 = CreateThread(
        NULL, //Security Attributes
        0, //Stack size -> Default stack size
        &ThreadFunction4, //Thread start function name
        NULL,
        0,
        0);


    //STEP-3 WaitForSingleObejct for All threads
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);


    //STEP-4 CloseHandle for All threads
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);
    CloseHandle(hThread4);


    system("PAUSE");
    return 0;
}


/*
Semaphore1 Creation Success
Semaphore2 Creation Success
Semaphore3 Creation Success
Thread-4

Thread-2

Thread-1

Thread-3
계속하려면 아무 키나 누르십시오 . . .

*/
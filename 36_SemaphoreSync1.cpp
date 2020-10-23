#include <Windows.h> 
#include <iostream> //Binary semaphore

using namespace std;

//Global handle for semaphore
HANDLE hSemaphore;


//Thread function
DWORD WINAPI MyFun(LPVOID lpParam) {
    
    LPVOID thread_no = lpParam;

    WaitForSingleObject(hSemaphore, INFINITE);
    cout << "Critical Section" << endl;
    cout << "Thread no : " << (int)thread_no << endl;
    cout << endl;
    ReleaseSemaphore(hSemaphore, 1, 0);

    return 0;
}


int main() {
    //Local variable
    HANDLE hThread1;
    HANDLE hThread2;

    //STEP-1 Create Semaphore 
    hSemaphore = CreateSemaphore(
        NULL, // Security Attiributes
        1,  //Initial State
        1,  // No. of Resources
        NULL);
    if (hSemaphore == NULL) {
        cout << "Semaphore Creation failed & Error no - " << GetLastError() << endl;
    }
    else {
        cout << "Semaphore Creation Success" << endl;
    }

    int first_thread = 1;
    int second_thread = 2;

    //STEP-2 Thread Creation
    hThread1 = CreateThread(
        NULL,   // SecurityAttributes
        0,      // StackSize
        &MyFun, // StartFunction
        (LPVOID)first_thread,   // ThreadParameter
        0,      // CreationFlags
        0);     // ThreadId

    hThread2 = CreateThread(
        NULL,
        0,
        &MyFun,
        (LPVOID)second_thread,
        0,
        0);


    //STEP-3 Wait for single object for thread 
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //STEP-4 CloseHandle for Thread
    CloseHandle(hThread1);
    CloseHandle(hThread2);


    //STEP-5 CloseHandle for Semaphore
    CloseHandle(hSemaphore);

    system("PAUSE");
    return 0;
}
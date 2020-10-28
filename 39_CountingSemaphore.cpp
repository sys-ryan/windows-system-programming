#include <Windows.h>
#include <iostream>

using namespace std;

HANDLE hSemaphore;
DWORD WINAPI ThreadFunction(LPVOID lpParam){
    DWORD dwWaitResult;
    BOOL bCondition = TRUE;

    while(bCondition){
        dwWaitResult = WaitForSingleObject(hSemaphore, INFINITE);
        switch(dwWaitResult){
            case WAIT_OBJECT_0:
                cout << "\nThreadID - " << GetCurrentThreadId() << endl;
                bCondition = FALSE;

                Sleep(5000);

                ReleaseSemaphore(hSemaphore, 1, 0);
                break;

            case WAIT_TIMEOUT:
                cout << "\nWait Timed Out Thread ID - " << GetCurrentThreadId() << endl;
                break;

            default: 
        }
    }
    return 0;
}

int main(){
    //Local variable
    HANDLE hThread[8];
    DWORD ThreadID;


    //STE:-1 Create Counting Semaphore
    hSemaphore = CreateSemaphore(
        NULL,
        5, //Initdial count -> 5
        5, //Max count
        NULL);

    if(hSemaphore == NULL){
        cout << "Semaphore Creation Failed & Error no - " << GetLastError() << endl; 
    }
    cout << "Semaphore creation success" << endl;


    //STEP-2 Create 8 Threads
    for(size_t i=0; i<8; i++){
        hThread[i] = CreateThread(
            NULL,
            0,
            &ThreadFunction,
            NULL,
            0,
            &ThreadID);
    }


    //STEP-3 Wait for all threads to terminate
    WaitForMultipleObjects(8, hThread, TRUE, INFINITE);


    //STEP-4 CloseHandle for Thread
    for(size_t i=0; i<8; i++){
        CloseHandle(hThread[i]);
    }


    //STEP-5 CloseHandle for Semaphore
    CloseHandle(hSemaphore);

    system("PAUSE");
    return 0;
}
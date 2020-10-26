/*
CreateSemaphore function  
Creates or opens a named or unnamed semaphore object.  

```
HANDLE CreateSemaphoreA(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpName
);
```


ReleaseSemaphore function   
Increases the count of the specified semaphore object by a specified amount.  

```
BOOL ReleaseSemaphore(
  HANDLE hSemaphore,
  LONG   lReleaseCount,
  LPLONG lpPreviousCount
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global handle for semaphore  
HANDLE hSemaphore; 

//Global Variable
int a, b, c;

//Thread function 
DWORD WINAPI InputFunction(LPVOID lpParam){
    cout << "Enter 1st No. " << endl;
    cin >> a;
    cout << "Enter 2nd No. " << endl;
    cin >> b;
    ReleaseSemaphore(hSemaphore, 1, 0);
    Sleep(2000);
    return 0;
}

DWORD WINAPI OutputFunction(LPVOID lpParam){
    WaitForSingleObject(hSemaphore, INFINITE);
    c = a + b;
    cout << "Addition : " << c << endl;

    return 0;
}


int main(){
    //Local variable
    HANDLE hThread1;
    HANDLE hThread2;


    //STEP-1 Create Semaphore
    hSemaphore = CreateSemaphore(
        NULL, //Security Attributes
        0, //Non-Signaled state
        1, //Max count 
        NULL);
    if(hSemaphore == NULL){
        cout << "Semaphroe Creation Faield & Error no - " << GetLastError() << endl;
    }
    cout << "Semaphore Creation Success" << endl; 


    //STEP-2 Thread Creation 
    hThread1 = CreateThread(
        NULL,   //Security Attributes
        0,      //StackSize
        &InputFunction, //Start function
        NULL,   //Thread Parameter
        0,      //Cration Flags
        0);     //Thread ID

     hThread2 = CreateThread(
        NULL,   
        0,      
        &OutputFunction,  
        NULL,    
        0,       
        0);  


    //STEP-3 Wait for Single Object for thread 
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

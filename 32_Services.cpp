/*
lstrcmpi function
Compares two character strings. 
The comparison is not case-sensitive. 

```
int lstrcmpiA(
  LPCSTR lpString1,
  LPCSTR lpString2
);
```


ServiceMain callback function
The entry point for a service.

```
VOID WINAPI ServiceMain(
    _In_ DWORD dwArgc,
    _IN_ LPTSTR *lpszArgv
)
```


RegisterServiceCtrlHandler function
Registers a function to handle service control requests.


```
SERVICE_STATUS_HANDLE RegisterServiceCtrlHandlerA(
  LPCSTR             lpServiceName,
  LPHANDLER_FUNCTION lpHandlerProc
);
```

SERVICE_STATUS structure
Contains status information for a service.

```
typedef struct _SERVICE_STATUS {
  DWORD dwServiceType;
  DWORD dwCurrentState;
  DWORD dwControlsAccepted;
  DWORD dwWin32ExitCode;
  DWORD dwServiceSpecificExitCode;
  DWORD dwCheckPoint;
  DWORD dwWaitHint;
} SERVICE_STATUS, *LPSERVICE_STATUS;
```


SetServiceStatus function
Updates the service control manager's status information for the calling service.

```
BOOL SetServiceStatus(
  SERVICE_STATUS_HANDLE hServiceStatus,
  LPSERVICE_STATUS      lpServiceStatus
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

//Global Variable declaration 
#define SERVICE_NAME TEXT("ASP Service") //Service Name 
SERVICE_STATUS ServiceStatus = { 0 }; // Service Status Structure
SERVICE_STATUS_HANDLE hServiceStatusHandle = NULL; // Service Status Handle for registering the service
HANDLE hServiceEvent = NULL; // Event Handle for Service 

//Windows Service functions declaration 
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv); //Service Main function
void WINAPI ServiceControlHandler(DWORD dwControl); // Service Control Handler 
void ServiceReportStatus(
    DWORD dwCurrentState, 
    DWORD dwWin32ExitCode,
    DWORD dwWaitHint); //Service Report Status
void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv);


// Main function
int main(int argc, CHAR *argv[]){
    cout << "In main function Start" << endl;

    //Local Variable 
    BOOL bStServiceCtrlDispatcher = FALSE;

    //Functional logic starts here 

    if( ){
        //call service install function 

        cout << "Installation Success" << endl;

    }else if(  ){
        //call Service start function

        cout << "ServiceStart Success" << endl;
    }else if(  ){
        //call service stop function

        cout << "ServiceStop Success" << endl;
    }else if (  ){
        //call service delete function 

        cout << "ServiceDelete" << endl; 
    }else {
        //STEP-1 Fill the Service Table Entry (2D Array)

        //STEP-2 Start Service Control Dispatcher 

        if(bStServiceCtrlDispatcher == FALSE){
            cout << "StartServiceCtrlDispatcher Failed = " << GetLastError() << endl;
        }else {
            cout << "StartServiceCtrlDispatcher Success" << endl;
        }
    }

    cout << "In main function End" << endl;
    system("PAUSE");
    return 0;
}

//ServiceMain Function definition 
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv){
    cout << "ServiceMain Start" << endl;
    //Local Variable definition
    BOOL bServiceStatus = FALSE;

    //STEP-1 Registering Service Control Handler function to SCM 
    hServiceStatusHandle = RegisterServiceCtrlHandler(
        SERVICE_NAME,
        ServiceControlHandler);

    if(hServiceStatusHandle){
        cout << "RegisterServiceCtrlHandler Failed" << GetLastError() << endl;
    }else{
        cout << "RegisterServiceCtrlHandler Success" << endl;
    }

    //STEP-2 SERVICE_STATUS Initial Setup 
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwServiceSpecificExitCode = 0;

    //STEP-3 call Service Report Status for Notifying Initial setup
    ServiceReportStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

    //STEP-4 Check the Service Status
    bServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);
    if(bServiceStatus == FALSE){
        cout << "Service Status initial setup FAILED = " << GetLastError() << endl;
    }else {
        cout << "Service Status initial setup SUCCESS" << endl;
    }

    //STEP-5 Call serviceInit function 
    ServiceInit(dwArgc, lpArgv);

    cout << "ServiceMain End" << endl;

}
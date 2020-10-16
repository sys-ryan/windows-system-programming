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


SERVICE_TABLE_ENTRYA structure
Specifies the ServiceMain function for a service that can run in the calling process. 
It is used by the StartServiceCtrlDispatcher function.

```
typedef struct _SERVICE_TABLE_ENTRYA {
  LPSTR                    lpServiceName;
  LPSERVICE_MAIN_FUNCTIONA lpServiceProc;
} SERVICE_TABLE_ENTRYA, *LPSERVICE_TABLE_ENTRYA;
```


StartServiceCtrlDispatcherA function
Connects the main thread of a service process to the service control manager, which causes the thread to be the service control dispatcher thread for the calling process.

```
BOOL StartServiceCtrlDispatcherA(
  const SERVICE_TABLE_ENTRYA *lpServiceStartTable
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
void ServiceInstall(void);  // Service install function
void ServiceDelete(void);   // Service delete function
void ServiceStart(void);    // Service start function
void ServiceStop(void);     // Service Stop function 

// Main function
int main(int argc, CHAR *argv[]){
    cout << "In main function Start" << endl;

    //Local Variable 
    BOOL bStServiceCtrlDispatcher = FALSE;

    //Functional logic starts here 

    if(lstrcmpiA(argv[1], "install") == 0){
        //call service install function 
        ServiceInstall();
        cout << "Installation Success" << endl;

    }else if(lstrcmpiA(argv[1], "start") == 0){
        //call Service start function
        ServiceStart();
        cout << "ServiceStart Success" << endl;
    }else if(lstrcmpiA(argv[1], "stop") == 0){
        //call service stop function
        ServiceStop();
        cout << "ServiceStop Success" << endl;
    }else if (lstrcmpiA(argv[1], "delete") == 0){
        //call service delete function 

        cout << "ServiceDelete" << endl; 
    }else {
        //STEP-1 Fill the Service Table Entry (2D Array)
        SERVICE_TABLE_ENTRY DispatchTable[] = {
            {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
            {NULL, NULL}
        };

        //STEP-2 Start Service Control Dispatcher 
        bStServiceCtrlDispatcher = StartServiceCtrlDispatcher(DispatchTable);

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


// Service Control Handler
void WINAPI ServiceControlHandler(DWORD dwControl){

    cout << "ServiceControlHandler" << endl;

    switch(dwControl){
        case SERVICE_CONTROL_STOP:
        {
            //call serviceReportStatus function 
            ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
            cout << "Service stopped" << endl;
            break;
        }
        default:
            break;
    }

    cout << "ServiceControlHandler" << endl;
}
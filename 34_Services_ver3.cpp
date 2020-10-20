/*
GetModuleFileNameA function
Retrieves the fully qualified path for the file that contains the specified module.  
The module must have been loaded by the current process.  

```
DWORD GetModuleFileNameA(
  HMODULE hModule,
  LPSTR   lpFilename,
  DWORD   nSize
);
```


OpenSCManagerA function
Establishes a connection to the service control manager on the specified computer 
and opens the specified service control manager database.

```
SC_HANDLE OpenSCManagerA(
  LPCSTR lpMachineName,
  LPCSTR lpDatabaseName,
  DWORD  dwDesiredAccess
);
```


CreateServiceA function
Creates a service object and adds it to the specified service control manager database.

```
SC_HANDLE CreateServiceA(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  LPCSTR    lpDisplayName,
  DWORD     dwDesiredAccess,
  DWORD     dwServiceType,
  DWORD     dwStartType,
  DWORD     dwErrorControl,
  LPCSTR    lpBinaryPathName,
  LPCSTR    lpLoadOrderGroup,
  LPDWORD   lpdwTagId,
  LPCSTR    lpDependencies,
  LPCSTR    lpServiceStartName,
  LPCSTR    lpPassword
);
```


OpenServiceA function
Opens an existing service.  

```
SC_HANDLE OpenServiceA(
  SC_HANDLE hSCManager,
  LPCSTR    lpServiceName,
  DWORD     dwDesiredAccess
);
```


DeleteService function
Marks the specified service for deletion from the service control manager database.

```
BOOL DeleteService(
  SC_HANDLE hService
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
        ServiceDelete();
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


void ServiceReportStatus(
    DWORD dwCurrentState,
    DWORD dwWin32ExitCode,
    DWORD dwWaitHint){

    cout << "ServiceReportStatus Start" << endl;
    
    //Local Variable Definitions
    static DWORD dwCheckPoint = 1;
    BOOL bSetServiceStatus = FALSE;

    
    //STEP-1 -> Filling the SERVICE_STATUS structure
    ServiceStatus.dwCurrentState = dwCurrentState;
    ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
    ServiceStatus.dwWaitHint = dwWaitHint; 


    //STEP-2 -> Check the Current State of Service
    if(dwCurrentState == SERVICE_START_PENDING){ //Service is about to start
        ServiceStatus.dwControlsAccepted = 0;
    }else {
        ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    }


    //STEP-3 -> Progress for Service operation 
    if((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED)){
        ServiceStatus.dwCheckPoint = 0;
    }else {
        ServiceStatus.dwCheckPoint = dwCheckPoint++;
    }


    //STEP-4 -> Notify the current status of SCM
    bSetServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

    if(bSetServiceStatus == FALSE){
        cout << "Service Status FAILED = " << GetLastError() << endl;
    }else{
        cout << "Service Status SUCCESS" << endl;
    }

    cout << "ServiceReportStatus End" << endl;
}


void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv){
    cout << "ServiceInit Start" << endl;

    //STEP-1 -> Create Event 
    hServiceEvent = CreateEvent(
        NULL,   //Security Attributes
        TRUE,   //Manutal Reset Event 
        FALSE,  //Non Signaled
        NULL);  //Name of Event 
    
    if(hServiceEvent == NULL){
        //Call ServiceReportStatus Function to notify SCM for current status of service. 
        ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
    }else {
        //Call ServiceReportStatus Function to notify SCM for current status of service. 
        ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);
    }


    //STEP-2 -> Check Whether to stop the Service 
    while(1){
        //WaitForSingleObject which waits event to be signaled. 
        WaitForSingleObject(hServiceEvent, INFINITE);
        
        //Send report status to SCM
        ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
    }

    cout << "ServiceInit End" << endl;
}



void ServiceINstall(void){
    cout << "ServiceInstall Start" << endl;

    //Local Variable
    SC_HANDLE hScOpenSCManager = NULL;
    SC_HANDLE hScCreateService = NULL;
    DWORD dwGetModuleFileName = 0;
    TCHAR szPath[MAX_PATH];

    
    //STEP-1 -> GetModuleFileName: Get the executable file from SCM 
    dwGetModuleFileName = GetModuleFileName(NULL, szPath, MAX_PATH);
    if(dwGetModuleFileName == 0){
        cout << "Service Installation Failed = " << GetLastError() << endl;
    }else {
        cout << "Successfully installed the file\n" << endl;
    }


    //STEP-2 -> Open the Service Control Manager 
    hScOpenSCManager = OpenSCManager(
        NULL,   //Local Machine
        NULL,   //By default Database i.e. SERVICES_ACTIVE_DATABASE
        SC_MANAGER_ALL_ACCESS); //Access RIght
    if(hScOpenSCManager == NULL){
        cout << "OpenSCManager Failed = " << GetLastError() << endl;
    }else {
        cout << "OpenSCManger Success" << endl;
    }


    //SPTE-3 -> Create the Service 
    hScCreateService = CreateService(
        hScOpenSCManager,
        SERVICE_NAME,
        SERVICE_NAME,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        szPath,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);
    if(hScCreateService == NULL){
        cout << "CreateService Faield = " << GetLastError() << endl;
    }else {
        cout << "CreateService Success" << endl;
    }


    //STEP-4 -> Close the Handle for OpenSCManager and Create Service 
    CloseServiceHandle(hScCreateService);
    CloseServiceHandle(hScOpenSCManager);

    cout << "ServiceInstall End" << endl;
}


void ServiceDelete(void){
    cout << "ServiceDelete Start" << endl;

    //Local Vriable
    SC_HANDLE hScOpenSCManager = NULL;
    SC_HANDLE hScOpenService = NULL;
    BOOL bDeleteService = FALSE;


    //STEP-1 -> Open the Service control manager
    hScOpenSCManager = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS);
    if(hScOpenSCManager == NULL){
        cout << "OpenSCManager Failed = " << GetLastError() << endl;
    }else {
        cout << "OpenSCManager Success" << endl;
    }
    

    //STEP-2 -> Open the Service 
    hScOpenService = OpenService(
        hScOpenSCManager,
        SERVICE_NAME,
        SERVICE_ALL_ACCESS);
    if(hScOpenService == NULL){
        cout << "OpenService Faield = " << GetLastError() << endl;
    }else {
        cout << "OpenService Success " << endl;
    }


    //STEP-3 -> Delete Service
    bDeleteService = DeleteService(hScOpenService);
    if(bDeleteService == FALSE){
        cout << "Delete Service Failed = " << GetLastError() << endl;
    }else {
        cout << "Delte Service Success" << endl;
    }

    //STEP-4 -> Close the Handle for SCM and OpenService
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);

    cout << "ServiceDelete End" << endl;
}
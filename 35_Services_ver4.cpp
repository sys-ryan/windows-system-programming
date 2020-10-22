/*
SERVICE_STATUS_PROCESS structure
Contains process status information for a service.

```
typedef struct _SERVICE_STATUS_PROCESS {
  DWORD dwServiceType;
  DWORD dwCurrentState;
  DWORD dwControlsAccepted;
  DWORD dwWin32ExitCode;
  DWORD dwServiceSpecificExitCode;
  DWORD dwCheckPoint;
  DWORD dwWaitHint;
  DWORD dwProcessId;
  DWORD dwServiceFlags;
} SERVICE_STATUS_PROCESS, *LPSERVICE_STATUS_PROCESS;
```


QueryServiceStatusEx function
Retrieves the current status of the specified service based on the specified information level.

```
BOOL QueryServiceStatusEx(
  SC_HANDLE      hService,
  SC_STATUS_TYPE InfoLevel,
  LPBYTE         lpBuffer,
  DWORD          cbBufSize,
  LPDWORD        pcbBytesNeeded
);
```


StartServiceA function
Starts a service.

```
BOOL StartServiceA(
  SC_HANDLE hService,
  DWORD     dwNumServiceArgs,
  LPCSTR    *lpServiceArgVectors
);
```


ControlService function
Sends a control code to a service.

```
BOOL ControlService(
  SC_HANDLE        hService,
  DWORD            dwControl,
  LPSERVICE_STATUS lpServiceStatus
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



void ServiceInstall(void){
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


void ServiceStart(void){
    cout << "Insie ServiceStart function" << endl;

    //Loca Variable 
    BOOL bStartService = FALSE;
    SERVICE_STATUS_PROCESS SvcStatusProcess;
    SC_HANDLE hOpenSCManager = NULL;
    SC_HANDLE hOpenService = NULL;
    BOOL bQueryServiceStatus = FALSE;
    DWORD dwBytesNeeded; 


    //STEP-1 -> Open Service Control Manager 
    hOpenSCManager = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS);

    if(hOpenSCManager == NULL){
        cout << "hOpenSCManager Failed = " << GetLastError() << endl;
    }else {
        cout << "hOpenSCManager Success" << endl;
    }


    //STEP-2 -> OpenService
    hOpenService = OpenService(
        hOpenSCManager,
        SERVICE_NAME,
        SC_MANAGER_ALL_ACCESS);
    if(hOpenService == NULL){
        cout << "OpenService Failed = " << GetLastError() << endl;
        CloseServiceHandle(hOpenSCManager);
    }else {
        cout << "OpenService Success" << endl; 
    }


    //STEP-3 -> Query about current Service Status 
    bQueryServiceStatus =  QueryServiceStatusEx(
        hOpenService,
        SC_STATUS_PROCESS_INFO,
        (LPBYTE) &SvcStatusProcess, 
        sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded);
    if(bQueryServiceStatus == FALSE){
        cout << "QueryService Faield = " << GetLastError() << endl;
    }else{
        cout << "QueryService Success" << endl;
    }


    //STEP-4 -> Check if the Service is running or stopped 
    if((SvcStatusProcess.dwCurrentState != SERVICE_STOPPED) && (SvcStatusProcess.dwCurrentState != SERVICE_STOP_PENDING)){
        cout << "service is already running" << endl;
    }else {
        cout << "service is already stopped" << endl;
    }


    //STEP-5 -> If Service is stopped then query the service
    while(SvcStatusProcess.dwCurrentState == SERVICE_STOP_PENDING){
        bQueryServiceStatus = QueryServiceStatusEx(
            hOpenService,
            SC_STATUS_PROCESS_INFO,
            (LPBYTE) &SvcStatusProcess,
            sizeof(SERVICE_STATUS_PROCESS),
            &dwBytesNeeded);
        if(bQueryServiceStatus == FALSE){
            cout << "QueryService Faield = " << GetLastError() << endl;
            CloseServiceHandle(hOpenService);
            CloseServiceHandle(hOpenSCManager);
        }else {
            cout << "QueryService Success" << endl;
        }
    }


    //STEP-6 -> Start the service. 
    bStartService = StartService(
        hOpenService,
        NULL,
        NULL);
    if(bStartService == FALSE){
        cout << "StartService Faield = " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }else {
        cout << "StartService Success" << endl;
    }
    
    
    //STEP-7 -> Query the service again 
    bQueryServiceStatus = QueryServiceStatusEx(
        hOpenService,
        SC_STATUS_PROCESS_INFO,
        (LPBYTE) &SvcStatusProcess,
        sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded);
    if(bQueryServiceStatus == FALSE){
        cout << "QueryService Faield = " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }else {
        cout << "QueryService Success" << endl;
    }


    //STEP-8 -> Check if the service is running or not 
    if(SvcStatusProcess.dwCurrentState == SERVICE_RUNNING){
        cout << "Service Started Running..." << endl; 
    }else {
        cout << "Service Running Faield = " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }


    //STEP-9 -> Close the service handle for OpenSCManager & OpenService
    CloseServiceHandle(hOpenService);
    CloseServiceHandle(hOpenSCManager);

    cout << "ServiceStart end" << endl;
}


void ServiceStop(void){
    cout << "Inside Service Stop" << endl;

    //Local variable
    SERVICE_STATUS_PROCESS SvcStatusProcess;
    SC_HANDLE hScOpenSCManager = NULL;
    SC_HANDLE hScOpenService = NULL;
    BOOL bQueryServiceStatus = TRUE;
    BOOL bControlService = TRUE;
    DWORD dwBytesNeeded;

    
    //STEP-1 -> Open Service Control Manager
    hScOpenSCManager = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS);
    
    if(NULL == hScOpenSCManager){
        cout << "OpenSCManager Failed = " << GetLastError() << endl;
    }else {
        cout << "OpenSCManager Success" << endl;
    }


    //STEP-2 -> Open your Service
    hScOpenService = OpenServie(
        hScOpenSCManager, 
        SERVICE_NAME,
        SC_MANAGER_ALL_ACCESS);
    
    if(hScOpenService == NULL){
        cout << "OpenService Faield = " << GetLastError() << endl;
    }else{
        cout << "OpenService Success" << endl;
    }


    //STEP-3 -> QueryServiceStatus 
    bQueryServiceStatus = QueryServiceStatusEx(
        hScOpenService,
        SC_STATUS_PROCESS_INFO,
        (LPBYTE) &SvcStatusProcess,
        sizeof(SERVICE_STATUS_PROCESS),
        &dwBytesNeeded);
    
    if(bQueryServiceStatus == FALSE){
        cout << "QueryService Failed = " << GetLastError() << endl;
        CloseServiceHandle(hScOpenService);
        CloseServiceHandle(hScOpenSCManager);
    }else {
        cout << "QueryService Success" << endl;
    }


    //STEP-4 -> send a stop code to the Service Control Manager 
    bControlService = ControlService(
        hScOpenService, 
        SERVICE_CONTROL_STOP,
        (LPSERVICE_STATUS)&SvcStatusProcess);
    if(bControlService == TRUE){
        cout << "Control Service Success" << endl;
    }else {
        cout < "Control Service Failed = " << GetLastError() << endl;
        CloseServiceHandle(hScOpenService);
        CloseServiceHandle(hScOpenSCManager);
    }


    //STEP-5 -> wiat for service to stop 
    while(SvcStatusProcess.dwCurrentState != SERVICE_STOPPED){
        

        //STEP-6 -> Inside while loop, query the service 
        bQueryServiceStatus = QueryServiceStatusEx(
            hScOpenService,
            SC_STATUS_PROCESS_INFO,
            (LPBYTE)&SvcStatusProcess,
            sizeof(SERVICE_STATUS_PROCESS),
            &dwBytesNeeded);
        
        if(bQueryServiceStatus == FALSE){
            cout << "QueryService Failed = " << GetLastError() << endl;
            CloseServiceHandle(hScOpenService);
            CloseServiceHandle(hScOpenSCManager);
        }else {
            cout << "QueryService Success" << endl;
        }


        //STEP-7 -> Inside while loop, check the current state of service
        if(SvcStatusProcess.dwCurrentState == SERVICE_STOPPED){
            cout << "Service Stopped Successfully" << endl;
            break;  //comming out of while loop
        }else {
            cout << "Service Stop Failed = " << GetLastError() << endl;
        }
    }

    //STEP-8 -> Close the handle for Open SCM & Open Service 
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);
    cout << "Service Stop" << endl;
}
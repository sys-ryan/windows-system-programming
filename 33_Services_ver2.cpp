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




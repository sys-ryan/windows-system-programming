# 5th Part 
### 1. void ServiceStart(void);  
### 2. void ServiceStop(void);  
### 3. QueryServiceStatusEx API   

## 7. Service Start function   
It Starts the on-demand service. 

<Programming Steps for ServiceStart function>  
1. Open the service control manager - `OpenSCManager` API  
2. Open the service - `OpenService` API  
3. Query the service status - `QueryServiceStatusEx` API  
4. Start the service - `StartService` API  
5. Query the service status that service is started or not - `QueryServiceStatusEx` API  
7. Close the handle for SCM & Create service - `CloseServiceHandle` API  





### 8. Service Stop function 
- IT stops the on-demand service

### Programming steps for serviceStop function  
1. Open the service control manager - `OpenSCManager` API  
2. Open the service - `OpenService` API   
3. Query the Service status - `QueryServiceStatusEx` API   
4. Send a Control Stop code to the SCM - `ControlService` API  
5. Wait for service to be stopped.   
6. Query the service status if service is stopped or not  - `QueryServiceStatusEx` API  
7. Close the handle for SCM & Create service - `CloseServiceHandle` API  





# SUMMARY  
## 1. Service Program  

    1. int main(*int argc, CHAR *argv [])   
    2. void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv);  
    3. void WINAPI ServiceControlHandler(DWORD dwControl);    
    4. void ServiceReportStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);  
    5. void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv);    

## 2. Service Configuration Program   
    
    1. void ServiceInstall(void);  
    2. void ServiceDelete(void);  
    3. QueryServiceStatusEx() API  

## 3. Servce Control Program  

    1. void ServiceStart(void);  
    2. void ServiceStop(void);  



## Part 1 - Service Program

    1. int main(*int argc, CHAR *argv [])   
    2. void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv);    
    3. void WINAPI ServiceControlHandler(DWORD dwControl);   


## Part 2 - Service Program

    4. void ServiceReportStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);  
    5. void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv);    


## Part 3 - Service Configuration Program

    1. void ServiceInstall(void);  
    2. void ServiceDelete(void);  
    3. QueryServiceStatusEx() API  


## Part 3 - Service Control Program

    1. void ServiceStart(void);  
    2. void ServiceStop(void);  




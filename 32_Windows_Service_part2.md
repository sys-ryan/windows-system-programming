# Programming Steps for Windows Service

### 1) int main(int argc, char *argv[])  
### 2) void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv); // * 
### 3) void WINAPI ServiceControlHandler(DWORD dwControll)  

## 1. Service Main Function
This is the entry point for a service.   
ServiceMain is a placeholder for an application-defined function name.  
It should immediately call `RegisterServiceCtrHandler` function to specify a handler function to handle control request.  
The, specify Service Type.
```
SERVICE_WIN32_OWN_PROCESS  
SERVICE_WIN32_SHARE_PROCESS
```
and it should immediately call  `StartServiceCtrlDispatcher` function from its main thread.  
It taked less than 30 seconds to start.   

Next, it should call `SetServiceStatus` function to send status to SCM.  

After these call, it should complete the initialization of Service. 


### Programming Steps for Service Main function 
1. Register the service program - `RegisterServiceCtrlHandler`  
2. Fill `SERVICE_STATUS` Structure for Initial setup.  
3. Check the Service Status using `SetServiceStatus` API.  
4. Then Call `ServiceInit` function.  


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




## 2. Service Control Handler Function 
Each service has acontrol handler function.   
When the service receive control request from SCM, It is called by Control Dispatcher function. (i.e. `StartServiceCtrlDispatcher`)   
This function executes in the context of the control dispatcher.  
When the service control handler is called, then the service calls `SetServiceStatus` to report its status to SCM only if handling the control code causes the service status to change.   
If handling the control code does not cause the service status to chagne, it is not necessary to call `SetServiceStatus`. 
There is various control code it can accept but here I am covering only which is Important.   
- SERVICE_CONTROL_STOP  
    1. When it is accepted then service must stop and status of service would be `SERVICE_STOP_PENDING` or `SERICE_STOPPED`.   
    2. After the SCM sends this control code, it will not send other control codes.   

- SERVICE_CONTROL_INTERROGATE   
    1. It sends current status of service to the SCM.   
    2. This control is not generally useful as the SCM is aware of the current state of the service.   

- SERVICE_CONTROL_CONTINUE  
    1. It notifies that service is paused and it should start.   
    2. 



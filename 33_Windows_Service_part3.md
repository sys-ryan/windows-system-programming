# 3rd Part 
## 4. void ServiceReportStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHin);  
## 5. void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv);  



## 3. ServiceInit(Customize) Fuction
- This one is initialization function of Service.  
- Once the Service has registered then Start hte service using Event function and check if the service has started or not.  
    * Why Event?  
    We can set 4 Startup Type of Service.  
    1. Automatic - Service starts at boot time.  
    2. Automatic(delayed start) - Service starts only after the system has loaded all the services set to start automatically.  
    3. Manual - Service start only when it needed using Event.  
    4. Disabled - Service never starts, even when its functionality is requested by other Windows service or apps.  
- Then send the service ststus report to SCM.   


### Programming Steps for ServiceInit function.
1. Create the Event -` CreateEvent API`  
2. Send the Service Report Status to SCM that service is running or stopped.  
    `ServiceReportStatus Function`  
3. Check the condition, if service is stopped then it uses INFINITE Loop.  
    - `WaitForSingleObject` - Set the event to be signaled   
    - `ServiceReportStatus` - Send Service Report Status to SCM. 



## Service Report Status Function  
- This function contains a `_SERVICE_STATUS` Structure, and stores the status information of Service.  
- It calls `SetServiceStatus` function to set the current status of service.  
- Then it notifies to the SCM.  
- The ControlService, EnumDependentServices, EnumServicesStatus, and QueryServiceStatus function use this structure.  


### Programming Steps for Service Report Status Function  
1. Fill the `_SERVICVE_STATUS` Structure.  
2. Retrieve the current status of the Service.  
3. If current status is `SERVICE_RUNNING` or `SERVICE_STOPPED`, then fill the check point in Structure.  
4. Then notify the current status of service to SCM using `SetServiceStatus` API.  


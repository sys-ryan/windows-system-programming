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




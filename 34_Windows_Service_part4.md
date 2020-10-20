## 4th part   
### 1. void ServiceInstall(void);  
### 2. void ServiceDelete(void);  

## 5. Service Install Function  
- It installs our service.  
- It will take the executing file handle of calling process.  
- Then, it calls SCM and SCM will create on demand service. 


### Programming Steps for ServiceInstall function.  
1. `GetModuleFileName` API  
2. Open the service control manager - `OpenSCManager` API  
3. Create on demand service - `CreateService` API  
4. Close the Handle for SCM & Create Service - `CloseServiceHandle` API  


## 6. Service Delete function  
- It deletes the service from installed service database.  


### Programming Steps for ServiceDelete function  
1. Open the service control manager - `OpenSCManager` API  
2. Open the service - `OpenService` API  
3. Delete the service - `DeleteService` API  
4. Close the handle for SCM & Create service - `CloseServiceHandle` API  



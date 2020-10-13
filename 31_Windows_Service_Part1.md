## Windows services 

Windows Services are daemon process as Linux.  
Deamon Process runs in background.  
It automatically starts when system boot up and can be restarted and pause.    
It does not have any user interface.   
Services can execute even when no user is logged on to the system.    
A `service application` conforms to the interface rules of SCM(Service Control Manager).  
It can be started automatically at system boot.   
A `driver service` conforms to the device driver protocols.  
It is like a service application, but it does not interact with the SCM.  

### Service lifetime 
A Service has several internal states in its lifetime.   

## Service States 
Services has 4 basic states:   
a) Running  
b) Paused  
c) Stopped  
d) Pending  


## Types of Services 
### 1. Win32OwnProcess  
a) A Win32 program that can be started by Service Controller   
b) They follow the Service Control Protocol  
c) This type of Win32 service runs in a process by itself.  

### 2. Win32SharedProcess  
A Win32 service that can share a process with other Win32 services  


## Service Windows Editor
1. Windows 7 and Windows Vista User  
Start > services.msc  
2. Windows 8, 8.1 and Windows 10 User   
Search > services  


## Windows Service Working 
1. First the service is installed onto the system on which it will run.  
2. Then, Process executes the installer for service and loads service into the Service Control Manager(SCM) for that computer.   
3. SCM is the central utility provided by windows to administer service.   
4. Then Service will start from service explorer or start method.   


## Service Control Manager(SCM)
The service control manager(SCM) maintains a database of installed services and driver services.   
It provides a unified and secure controlling  
The database includes information on how each service or driver service should be started.  
It also enables system administrators to customize security requirements for each service and thereby control access to the service.  


SCM provides some function which is used by the folling types of program.  

### 1   Service Program  
 
    It provides executable code for one or more servicees.   
    Service programs use functions that connect to the SCM   
    It sends status information to the SCM.   

### 2   Service configuration program

    It queries or modifies the services database.   
    It queries or modifies the configuration and security parameters for installed services.  
    `ServiceConfigProg` manages both Application service and Driver service.  
    `ServiceConfigProg` uses the SCM function that Open, Delete the services from Database.   

### 3   Service control program 

    It start and control the Application service and Driver service   
    Whatever it gets the request, it sends request to Service Control Manager.  



    ### Service Control Manager  ->  Service Database  
    ### ↑  
    ### Service Control Program    
    It starts and Stop Service based on request.   
    ### ↑  
    ### Service Configuration Program  
    It queries or modifies the service & open or delete the service based on requeest.   
    ### ↑  
    ### Service Program  
    Provide Executable code for servicee & connect to SCM & send status inormation to SCM   
    ### ↑  
    ### Application   


## ServiceMain Function Workflow
1. A service program can start one or more services.  
2. A service process has a `SERVICE_TABLE_ENTRY` structure for each service that it can start.  
3. The structure specifies the service name and a pointer to the `ServiceMain` function for that service.  
4. When the service control manager receives a request to start a service, it starts the service process if it is not already running.  
5. The main thread of the service process calls the `StartServiceCtrlDispatcher` function with a pointer to an array of `SERVICE_TABLE_ENTRY` structures.   
6. Then the service control manager sends a start request to the serevice control dispatcher for this service process.  
7. The `service control dispatcher` creates a new thread to execute the `ServiceMain` function of the service being started. 


## Programming Step for Windows Service
### 1   Service Program   
    1. Servis Program's main function  
    2. ServiceMain function  
    3. Control handler function   

### 2   Service Configuration Program  
    1. Installing a Service  
    2. Deleting a Service  
    3. Changing a Service's Configuration  
    4. Querying a Service's Configuration 

### 3   Service Control Program 
    1. Starting a Service  
    2. Stopping a Service  
    3. Modifying the DACL for a Service  



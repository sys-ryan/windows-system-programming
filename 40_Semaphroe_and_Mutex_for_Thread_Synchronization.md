# Thread Synchronization Using Counting Semaphore and Mutex in Windows 

There are mainly 3 use cases of Semaphore  
1. Mutual Exclusion or Mutext Lock  
2. Count-Down counter  
3. Notiification   


## Difference Between Semaphore and Mutex   
### Semaphore
1. Semaphore is Signaling mechanism.   
2. Semaphore is used for process and thread synchronization.  
3. Binary semaphore can act as a mutex.  
4. Semaphore does not provide ownership.  

### Mutex  
1. Mutex is Locking mechanism.  
2. Mutex is for thread synchronization.  
3. But Mutex cannot act as a binary semaphore.   
4. Mutex provides ownership.  


In counting semaphore,  
if S = 2 then,  
2 threads come simultaneously into C.S but the order may not be same.  

In mutex,  
Only those who acquire lock first can release the lock.  


### Windows APIs
1. CreateSemaphore()  
2. CreateThread()  
3. WaitforSingleObject()  
4. CreateMutex()  
6. ReleaseMutex()  
7. CloseHandle()  

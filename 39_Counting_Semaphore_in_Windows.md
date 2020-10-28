# Counting Semaphore in Windows  
1. Semaphore is a non-Negative integer value  
2. If Semaphore,   
    Coumt > 1 = Counting Semaphore.   
3. Semaphore object is useful in controlling a shared resource that can support a limited number of users.  
4. Create Semaphore: 

```
HANDLE CreateSemaphoreA(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpName
);
```

`LONG lInitialCount`  
i.  Used for Initialize Semaphore.  
ii. The initial count must be neither less than zero nor greater than tha maximum value  

`LONG lMaximumCount`  
i.  The maximum count for the semaphore object.  
ii. This value must be greater than zero.  



5. If more than one thread is waiting on a semaphore, then waiting thread is selected. 
6. The initial count of semaphore is set to the maximum vlaue and then count value is decremented from that level as the protected resource is consumed.   



WaitForMultipleObjects function  
Waits until one or all of the specified objects are in the signaled state or the time-out interval elapses.  

```
DWORD WaitForMultipleObjects(
  DWORD        nCount,
  const HANDLE *lpHandles,
  BOOL         bWaitAll,
  DWORD        dwMilliseconds
);
```
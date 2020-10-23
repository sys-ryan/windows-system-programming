# SEMAPHORE in WINDOWS

1. Semaphore is an integer variable.  
2. A semaphore object is a synchronization object that maintains a count between zero and a specified maximum value.  
3. It's a replacement of Mutual Exclusion.  
4. It can be accessed by only two interlocked or atomic operation, `wait & signal`  
5. There is no mutual ownership in Semaphore.  
6. In case of Mutex:   
    - Those who locked the resources only release the lock   

7. In case of Smaphore:   
    - Anyone can lock the resources and release the resources.  

8. Two types of Semaphore:  
    - Binary Semaphore  
    - Counting Semaphore  

9. State of Semaphore:  
    - Signaled = count > 0;  
    - Non-Signaled = 0;  

10. Counter is a list of tasks waiting to access resources.   


# Semaphore Working:  
We know that there are two atomic operation of Semaphore. 

    ## 1. Wait Operation  
    - Decrement the count, when each thread complete wait operation for the semaphore objet. 
    - In Windoes, `WaitForSingleObject` API is used for wiat operation  

    ## 2. Signal Operation  
    - Simply Increment the count, each time a thread releases the semaphore. 
    - In Windows, `ReleaseSemaphore` API is used for Signal Operation.  


    ## Semaphore Types:
    ### 1. Binary Semaphore.
        - It can have only Two values either 0 or 1  
        - Very useful to solving the critical section problem.  
        - if S=1, We can access only one resources at a time  

    ### 2. Counting Semaphore  
        - It can have multiple value of Count.  
        - Semaphroe initialization tells that how many resources we can access simultaneously. 
        - If S=5, we can access 5 resources simultaneously.  
        - Context switching happens at any point of time.  



CreateSemaphore API   
This function creates a named or unnamed semaphore object.  

```
HANDLE CreateSemaphore(
LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, 
LONG lInitialCount, 
LONG lMaximumCount, 
LPCTSTR lpName ); 
```

LONG lInitialCount 
    0 : Semaphore in non-signaled state  
    1 : Semaphore in signaled state  

LONG lMaximumCount  
    1 : Binary semaphore  
    n>1 : Counting Semaphore 






ReleaseSemaphore function
Increases the count of the specified semaphore object by a specified amount.

```
BOOL ReleaseSemaphore(
  HANDLE hSemaphore,
  LONG   lReleaseCount,
  LPLONG lpPreviousCount
);
```


### Windows APIs  
1. CreateSemaphore()  
2. ReleaseSemaphore()  
3. CreateThread()  
4. WaitForSingleObject()  
5. CloseHandle()  



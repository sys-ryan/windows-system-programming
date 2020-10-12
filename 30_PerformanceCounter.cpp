/*
Query Performance Counter 

    1. Counters are used to provide information as to how well the operating system or an application, service, or driver is performing. 
    2. With the help of counter, we can determine how much resources are being used.
    3. QPC is used for measuring time intervals or high-resolution time stamps. 
    4. QPC measures the total computation of response time of code execution. 
    5. QPC is independent and isn't synchronized to any external time reference. 
    6. If we want to use synchronization time stamps, then we must use `GetSystemTimePreciseAsFileTime`.
    7. QPC is typically the best method to use for time-stamp events and measuring small time intervals that occur on the same system or virtual machine. 
    8. QPC has two types of API
        APPLICATION     - QueryPerformanceCounter (QPC)
        DEVICE DRIVER   - KeQueryPerformanceCounter

LARGE_INTEGER & ULARGE_INTEGER 
a) L.I. is a window type, basically a portable 64-bit integer
b) Its definition depends on whether the target system supports 64-bit integers or not. 
c) If the system doesn't support 64-bit integer then it's defined as two 32-bit integers, a High Part and a Low Part 
d) If the system does support 64-bit integer then it's a union between the Two 32-bit integer and a 64-bit integer called the QuadPart 


```
typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;
```

Windows APIs
1. QueryPerformanceFrequency()
2. QueryPerformanceCounter() 
*/

#include <Windows.h>
#include <iostream>  //Query performance counter

using namespace std;

int main() {
    LARGE_INTEGER StartingTime, EndingTime, DifferenceOfTime;
    LARGE_INTEGER frequency; //Default frequency supported by H/W
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&StartingTime);
    cout << "Hello World!" << endl;
    Sleep(1995);
    QueryPerformanceCounter(&EndingTime);

    DifferenceOfTime.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

    DifferenceOfTime.QuadPart *= 1000000;
    DifferenceOfTime.QuadPart /= frequency.QuadPart; // For Tick/Sec.
    DifferenceOfTime.QuadPart /= 1000;  // in milli Sec.

    cout << "Execution Timer = " << DifferenceOfTime.QuadPart << "ms" << endl;

    system("PAUSE");
    return 0;
}
/*
INTERLOCKED FUNCTIONS in Windows

	1. Interlocked functions synchronize access to a variable that is shared by multiple threads
	2. All the operations are performed in Atomic way or single clock
	3. In Linux, It is called Atomic Variable. 
	4. APIs change according to system configuration. 
	5. This is a method used to safely update and/or fetch data shared between tasks, threads, and interrupt routines, and between processors on multi-processor system. 
	6. Atomic functions are the ones that the read-write operation is done as one instruction without any interruption.
	7. Suppose your system
		
		32 Bit -> InterlockedIncrement()
		64 Bit -> InterlockedIncrement64()


	Interlocked APIs 
	
		- InterlockedIncrement
		- InterlockedIncrement64
		- InterlockedDecrement
		- InterlockedExchange
		- InterlockedExchangePointer
		- InterlockedExchangeAdd
		- InterlockedCompareExchange
		- InterlockedAnd
		- InterlockedOr
		- InterlockedXor
		- InterlockedDecrementAcquire
		- InterlockedDecrementRelease
		- Etc... 


InterlockedAdd function
Performs an atomic addition operation on the specified LONG values.

```
LONG InterlockedAdd(
  LONG volatile *Addend,
  LONG          Value
);
```

*** The InterlockedAdd function is only available on the Itanium platform. 
	On x86 and x86-64 platforms you can use InterlockedExchangeAdd instead. 
	This also adds a value to the target variable, but it returns the original value instead of the new value.


InterlockedIncrement function
Increments (increases by one) the value of the specified 32-bit variable as an atomic operation.
+ To operate on 64-bit values, use the InterlockedIncrement64 function.

```
LONG InterlockedIncrement(
  LONG volatile *Addend
);
```
*/

#include <Windows.h>
#include <iostream>
//#include <intrin.h>
#include <winnt.h>

using namespace std;

int main() {

	volatile LONG64 a = 5;
	volatile LONG64 old_value;

	old_value = _InterlockedExchangeAdd64(&a, 5);
	cout << "Addition = " << a << endl;


	volatile LONG64 x = 10;
	volatile LONG64 y;

	y = _InterlockedIncrement64(&x);
	cout << "Increment = " << y << endl;



	system("PAUSE");
	return 0;
}

/*
Registry keys
1. HKEY_LOCAL_MACHINE
	it stores physical info about machine along with installed software.

2. HKEY_USERS
	It defines user configuration information

3. HKEY_CURRENT_CONFIG
	It contains current settings of user such as font and resolution.

4. HKEY_CLASSES_ROOT
	It contains subordinate entries to define mappings from file extension to classes.

5. HKEY_CURRENT_USER
	It contains user specific information


RegCreateKeyEx function
This function creates the specified key. If the key already exists in the registry, the function opens it.


```
LONG RegCreateKeyEx(
	HKEY hKey,
	LPCTSTR lpSubKey,
	DWORD Reserved,
	LPTSTR lpClass,
	DWORD dwOptions,
	REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY phkResult,
	LPDWORD lpdwDisposition );
```


RegSetValueEx function
Sets the data and type of a specified value under a registry key.

```
LONG WINAPI RegSetValueEx(
	_In_        HKEY hKey,
	_In_opt_    LPCTSTR lpValueName,
	_Reserved_  DWORD Reserved,
	_In_        DWORD dwType,
	_In_        const BYTE *lpData,
	_In_        DWORD cbData);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	LONG lReg;
	HKEY hKey;

	DWORD dwData = 1234;

	lReg = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		L"Software\\Test\\Product\\SmartId",
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS | KEY_WOW64_64KEY,
		NULL,
		&hKey,
		NULL);
	if (lReg != ERROR_SUCCESS) {
		cout << "Registry creation failed & Error No - " << GetLastError() << endl;
	}
	cout << "Registry creation Success" << endl;


	lReg = RegSetValueEx(
		hKey,
		L"VALUE",
		NULL,
		REG_DWORD,
		(LPBYTE)&dwData,
		sizeof(dwData)
		);
	if (lReg != ERROR_SUCCESS) {
		cout << "RegSetValueEx creation failed & Error No - " << GetLastError() << endl;
	}
	cout << "RegSetValueEx creation Success" << endl;

	RegCloseKey(hKey);

	system("PAUSE");
	return 0;
}

/*
CreateSymbolicLink function

```
BOOLEAN CreateSymbolicLinkA(
  LPTSTR lpSymlinkFileName,
  LPTSTR lpTargetFileName,
  DWORD  dwFlags
);
```
*/


#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	BOOL bHfile;

	bHfile = CreateSymbolicLink(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\SymbolicLInk.txt",
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\TestFile.txt",
		0);
	if (bHfile == FALSE) {
		cout << "CreateSymbolicLink() Failed & Error No = " << GetLastError() << endl;
	}
	cout << "CreateSymbolicLink() Success" << endl;

	system("PAUSE");
	return 0;
}

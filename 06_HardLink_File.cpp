/*
CreateHardLink function
 Establishes a hard link between an existing file and a new file. This function is only supported on the NTFS file system, and only for files, not directories.

 ```
 BOOL CreateHardLink(
  LPCTSTR                lpFileName,
  LPCTSTR                lpExistingFileName,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
```
*/

#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	BOOL bHfile;
	bHfile = CreateHardLink(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\HardLink.txt",
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\TestFile.txt",
		NULL
	);
	if (bHfile == FALSE) {
		cout << "CreateHardLink() Failed & Error No = " << GetLastError() << endl;
		return 1;
	}
	cout << "CreateHardLink() Success" << endl;

	system("PAUSE");
	return 0;
}

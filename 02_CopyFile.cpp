#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	BOOL bFile;
	bFile = CopyFile(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\OldFile.txt",
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\NewFile.txt",
		TRUE);

	if (bFile == FALSE) {
		cout << "CopyFile() Failed & Error No - " << GetLastError() << endl;
	}

	cout << "CopyFile() Success" << endl;

	system("PAUSE");
	return 0;
	}

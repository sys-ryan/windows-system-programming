#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
	BOOL bFile;

	bFile = MoveFile(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\Old.txt",
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\New.txt");

	if (bFile == FALSE) {
		cout << "MoveFile() Failed & Error No - " << GetLastError() << endl;
	}

	cout << "MoveFile() Success" << endl;

	system("PAUSE");
	return 0;
}

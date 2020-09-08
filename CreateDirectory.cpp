#include <Windows.h>
#include <iostream>

using namespace std;

int main() {

	BOOL bDir;
	bDir = CreateDirectory(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\Dir1",
		NULL
		);

	if (bDir == FALSE) {
		cout << "CreateDirectory() Failed & Error No - " << GetLastError() << endl;
	}

	cout << "CreateDirectory() Success" << endl;

	getchar();


	bDir = RemoveDirectory(
		L"C:\\Users\\ryan\\source\\repos\\SampleDirectory\\Dir1"
		);

	if (bDir == FALSE) {
		cout << "RemoveDirectory() Failed & Error No - " << GetLastError() << endl;
	}

	cout << "RemoveDirectory() Success" << endl;

	system("PAUSE");
	return 0;
}

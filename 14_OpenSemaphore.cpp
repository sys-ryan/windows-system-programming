#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
    HANDLE hSem;
    cout << "OpenSemaphore" << endl;

    hSem = OpenSemaphore(
        SEMAPHORE_ALL_ACCESS,
        FALSE,
        L"MySemaphore");

    if (hSem == NULL) {
        cout << "Open Semaphore Creation Failed & Error No - " << GetLastError() << endl;
    }
    cout << "Open Semaphore Creation Success" << endl;

    system("PAUSE");
    return 0;
}

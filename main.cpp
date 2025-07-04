// 9-2
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n = 9;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int m = 0;
    int re = 0;
    for (int i = 0; i < n; i++) {
        if (m < arr[i]) {
            m = arr[i];
            re = i;
        }
    }
    cout << m << endl;
    cout << re + 1 << endl;

    delete[] arr;
    return 0;
}

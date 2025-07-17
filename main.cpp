// 10-3
#include <iostream>
#include <array>
#include <algorithm> 

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a_1, a_2, a_3, a_4, a_5;
    cin >> a_1 >> a_2 >> a_3 >> a_4 >> a_5;
    array<int, 5> arr = {a_1, a_2, a_3, a_4, a_5};
    sort(arr.begin(), arr.end());
    int d = arr[2];
    int ct = 0;
    while (true) {
        for (int i=0; i < 5; i++) {
            if (d % arr[i] == 0) {
                ct++;
            }
        }
        if (ct >= 3) {
            cout << d;
            break;
        }
        d++;
        ct = 0;
    };
    ct = 0;
    return 0;
}
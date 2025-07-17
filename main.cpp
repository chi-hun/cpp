// 10-3
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
	cin.tie(0); 

    int n;
    cin >> n;
    
    int y = 0;
    int m = 0;

    int t;

    for (int i=1; i <= n; i++) {
        cin >> t;
        y += ((t / 30) + 1) * 10;
        m += ((t / 60) + 1) * 15;
    }

    if (y > m) {
        cout << "M " << m << endl;
    } else if (y < m) {
        cout << "Y " << y << endl;
    } else {
        cout << "Y M " << y << endl;
    }
        

    return 0;
}

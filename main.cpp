// 9-3
#include <iostream>

using namespace std;

struct NUM{
    static const int a = 3;
};

int main() {
    NUM d;
    cout << d.a << endl;
    return 0;
}

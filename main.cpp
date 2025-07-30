// 17-1
#include <iostream>
using namespace std;

template<typename T>
void what(T t) {
    if constexpr (is_pointer<T>::value) {
        cout << "포인트 : " << *t << endl;
    } else {
        cout << "포인트 아님 : " << t << endl;
    }
}

int main() {
    int d = 3;
    int* dp = &d;
    what(d);
    what(dp);

    return 0;
}

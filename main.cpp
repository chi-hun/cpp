// 14
#include <iostream>
#include <string>
#include <functional>

using namespace std;

struct S {
    int data;
    S(int d) : data(d){
        cout << "생성자" << endl;
    }
    S(const S& s) {
        cout << "복사 생성자" << endl;
        data = s.data;
    }
    S(S&& s) {
        cout << "이동 생성자" << endl;
        data = s.data;
    }
    
};

void som(S& s_1, S& s_2) {
        s_1.data = s_2.data+3;
    }

int main() {
    S s_1(2), s_2(3);
    auto som_b = bind(som, ref(s_1), placeholders::_1);
    som_b(s_2);
    cout << s_1.data << endl;
    return 0;
}

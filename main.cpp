// 13-2
#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <vector>


using namespace std;

class A {
    string s;
    weak_ptr<A> other;
    public:
        A(string s) : s(s) {
            cout << "생성" << endl;
        }
        ~A() {
            cout << "소멸" << endl;
        }
        void some() {
            cout << "some" << endl;
        }
        void some_2() {
            cout << "some_2" << endl;
        }
        void set_other(weak_ptr<A> o) {other = o;}
        void acces_other() {
            shared_ptr<A> o = other.lock();
            if (o) {
                cout << "name : "<< o -> name() << endl;
            } else {
                cout << "not other" << endl;
            }
        }
        string name() {return s;}
};


int main() {
    vector<shared_ptr<A>> v;
    v.push_back(make_shared<A>("A"));
    v.push_back(make_shared<A>("B"));
    v[0] -> set_other(v[1]);
    v[1] -> set_other(v[0]);
    v[0] -> acces_other();
    v.pop_back();
    v[0] -> acces_other();

    return 0;
}

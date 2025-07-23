// 13-1
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class A {
    public:
        A() {cout << "nomal create" << endl;}
        A(const A& a) {cout << "copy create" << endl;}
        A(const A&& a) {cout << "move create" << endl;}
};


class B {
 public:
  B(const A& a) : a_(std::move(a)) {}

  A a_;
};


int main() {
    A a;
    std::cout << "create B-- \n";
    B b(move(a));
    return 0;
}

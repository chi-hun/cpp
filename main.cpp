// 9-3
#include <iostream>

using namespace std;

template <int i, int j>
struct gcd {
    static const int value = gcd<j, i % j>::value;
};

template <int j>
struct gcd<j, 0> {
    static const int value = j;
};

template <int N, int D>
struct ratio {
    static const int _gcd = gcd<N, D>::value;
    using type = ratio<N / _gcd, D / _gcd>;
    static const int num = N / _gcd;
    static const int den = D / _gcd;
};

template <class A, class B>
struct _ratio_add { 
    using type = ratio<A::num * B::den + B::num * A::den, A::den * B::den>;
};

template <class A, class B>
struct ratio_add : _ratio_add<A, B>::type {};


int main() {
    typedef ratio<3, 2> r_1;
    typedef ratio<9, 3> r_2;
    typedef ratio_add<r_1, r_2> r_3;
    cout << r_3::num << "/" << r_3::den << endl;
    return 0;
}

// 9-4
#include <iostream>

using namespace std;

template <int N>
struct NUM {
    static const int num = N;
};

using one = NUM<1>;
using two = NUM<2>;
using three = NUM<3>;

template <typename A, typename B>
struct add{
    using result = NUM<A::num + B::num>;
};

template <typename A, typename B>
struct divine{
    using result = NUM<A::num / B::num>;
};

template <typename N, typename D>
struct check_divine {
    static const bool result = (N::num % D::num == 0) || check_divine<N, typename add<D, one>::result>::result;
};

template <typename N>
struct _is_prime {
    static const bool result = !check_divine<N, two>::result;
};


template <>
struct _is_prime<two> {
    static const bool result = true;
};

template <>
struct _is_prime<three> {
    static const bool result = true;
};

template <int N>
struct is_prime {
    static const bool result = _is_prime<NUM<N>>::result;
};

template <typename N>
struct check_divine <N, typename divine<N, two>::result>{
    static const bool result = (N::num % (N::num / 2) == 0);
};

int main() {
    cout << is_prime<41>::result;
    return 0;
}

// 9-4
#include <iostream>
#include <typeinfo>

using namespace std;

template <int A, int B>
struct GCD {
    static const int value = GCD<B, A%B>::value;
};

template <int A>
struct GCD <A, 0> {
    static const int value = A;
};

template <int N, int D>
struct Ratio {
    const static int _GCD = GCD<N, D>::value;

    using type = Ratio<N/_GCD, D/_GCD>;
    static const int num = N /_GCD;
    static const int den = D /_GCD;
};

template <typename A, typename B>
struct _Ratio_add {
    using type = Ratio<A::num * B::den + A::den * B::num, A::den * B::den>;
};

template <typename A, typename B>
struct Ratio_add : _Ratio_add<A, B>::type {};

template <typename A, typename B>
struct _Ratio_subtract  {
    using type = Ratio<A::num * B::den - A::den * B::num, A::den * B::den>;
};

template <typename A, typename B>
struct Ratio_subtract  : _Ratio_subtract <A, B>::type {};

template <typename A, typename B>
struct _Ratio_multiply {
    using type = Ratio<A::num * B::num, A::den * B::den>;
};

template <typename A, typename B>
struct Ratio_multiply : _Ratio_multiply <A, B>::type {};

template <typename A, typename B>
struct _Ratio_divide {
    using type = Ratio<A::num * B::den, A::den * B::num>;
};

template <typename A, typename B>
struct Ratio_divide : _Ratio_divide <A, B>::type {};

template<typename U, typename V, typename W>
struct Dim {
    using M = U;
    using L = V;
    using T = W;
    using type = Dim<U, V, W>;
};

template<typename A, typename B>
struct add_dim_ {
    using type = Dim<typename Ratio_add<typename A::M, typename B::M>::type, 
                    typename Ratio_add<typename A::L, typename B::L>::type,
                    typename Ratio_add<typename A::T, typename B::T>::type>;
};

template<typename A, typename B>
struct subtract_dim_ {
    using type = Dim<typename Ratio_subtract<typename A::M, typename B::M>::type, 
                    typename Ratio_subtract<typename A::L, typename B::L>::type,
                    typename Ratio_subtract<typename A::T, typename B::T>::type>;
};


template<typename T, typename D>
struct quantity {
    T q;
    using Dim_type = D;

    quantity(T q) : q(q) {}

    quantity operator+(quantity<T, D> quant) {return quantity<T, D>(q + quant.q);}

    quantity operator-(quantity<T, D> quant) {return quantity<T, D>(q - quant.q);}

    template <typename D2>
    quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
    return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
    }

    template <typename D2>
    quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant) {
    return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
    }

    quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }

    quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }
    
};

template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
  out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
      << "s^" << D::T::num / D::T::den;

  return out;
}


int main() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;
    quantity<double, Dim<one, zero, zero>> kg(2);
    quantity<double, Dim<zero, one, zero>> meter(3);
    quantity<double, Dim<zero, zero, one>> second(1);

    // F 의 타입은 굳이 알필요 없다!
    auto F = kg * meter / (second * second);
    std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
                << std::endl;
    

    return 0;
}

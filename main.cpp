// 4-4
#include <iostream>
#include <string.h>

class Complex {
    int a;
    int b;

    public:
        Complex(int a, int b) : a(a), b(b) {};
        ~Complex() {};
        void print(void);
        Complex operator+(Complex c);
        Complex operator-(Complex c);
        Complex operator*(Complex c);
        Complex operator/(Complex c);
        
};

void Complex::print(void) {
    std::cout << a << " + " << b << "i" << std::endl;
}

Complex Complex::operator+(Complex c) {
    std::cout << "add" << std::endl;
    int _a = a + c.a;
    int _b = b + c.b;
    return Complex(_a, _b);
}

Complex Complex::operator-(Complex c) {
    std::cout << "sub" << std::endl;
    int _a = a - c.a;
    int _b = b - c.b;
    return Complex(_a, _b);
}

Complex Complex::operator*(Complex c) {
    std::cout << "mul" << std::endl;
    int _a = (a * c.a) - (b * c.b);
    int _b = (a * c.b) + (b * c.a);
    return Complex(_a, _b);
}

Complex Complex::operator/(Complex c) {
    std::cout << "div" << std::endl;
    int _d = c.a*c.a + c.b*c.b;

    int _a = ((a * c.a) + (b * c.b)) / _d;
    int _b = ((b * c.a) - (a * c.b)) / _d;
    return Complex(_a, _b);
}

int main(void) {
    Complex c_1(1,2);
    Complex c_2(3,4);
    c_1.print();
    c_2.print();

    Complex c_3 = c_1 + c_2;
    c_3.print();

    c_3 = c_1 - c_2;
    c_3.print();

    c_3 = c_1 * c_2;
    c_3.print();

    c_3 = c_1 / c_2;
    c_3.print();

    return 0;
}
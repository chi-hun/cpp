// 4-4
#include <iostream>
#include <string.h>

class Mystring {
    char* str_p;
    int str_l;
    int str_c;

    public:
    Mystring(char c);
    Mystring(const char *c);
    Mystring(const Mystring& c);
    ~Mystring();
    Mystring& assign(const Mystring& c);
    Mystring& assign(const char *c);
    Mystring& operator=(const Mystring& c);
    Mystring operator+(const Mystring& c);
    int length() const;
    int cap() const;
    void re_cap(int size);
    void print();
};

Mystring::Mystring(char c) {
    str_p = new char[1];
    str_p[0] = c;
    str_l = 1;
    str_c = 1;
}

Mystring::Mystring(const char *c) {
    str_l = strlen(c);
    str_c = str_l+1;
    str_p = new char[str_l+1];
    strcpy(str_p, c);
}

Mystring::Mystring(const Mystring& c) {
    str_l = strlen(c.str_p);
    str_c = str_l+1;
    str_p = new char[str_l+1];
    strcpy(str_p, c.str_p);
}

Mystring::~Mystring() {
    delete[] str_p;
}

Mystring& Mystring::assign(const Mystring& c) {
    if (str_l < c.str_l) {
        delete[] str_p;
        str_p = new char[c.str_l+1];
        str_c = c.str_l+1;
    }
    strcpy(str_p, c.str_p);
    str_l = c.str_l;
    return *this;
}

Mystring& Mystring::assign(const char *c) {
    int c_l = strlen(c);
    if (str_l < c_l) {
        delete[] str_p;
        str_p = new char[c_l+1];
    }
    strcpy(str_p, c);
    str_l = c_l;
    return *this;
}
Mystring& Mystring::operator=(const Mystring& c) {
    if (str_l < c.str_l) {
        delete[] str_p;
        str_p = new char[c.str_l+1];
    }
    strcpy(str_p, c.str_p);
    str_l = c.str_l;
    return *this;
}

Mystring Mystring::operator+(const Mystring& c) {
    Mystring tmp('e');
    tmp.str_l = str_l + c.str_l;
    tmp.str_c = tmp.str_l + 1;
    tmp.str_p = new char[tmp.str_c];
    strcpy(tmp.str_p, str_p);
    strcat(tmp.str_p, c.str_p);
    return tmp;
}

int Mystring::length() const {
    return str_l;
}

int Mystring::cap() const {
    return str_c;
}

void Mystring::re_cap(int size) {
    if (str_c < size) {
        char* tmp = str_p;
        str_p = new char[size];
        strcpy(str_p, tmp);
        str_c = size;
        delete[] tmp;
    }
}


void Mystring::print() {
    std::cout << str_p << std::endl;
}

int main(void) {
    Mystring cc("ddd");
    cc.print();
    Mystring dd(cc);
    dd.print();
    std::cout << dd.length() << std::endl;

    dd.assign("abc");
    dd.print();
    std::cout << dd.length() << std::endl;

    dd = cc;
    dd.print();
    std::cout << dd.length() << std::endl;
    std::cout << dd.cap() << std::endl;

    dd.re_cap(100);
    std::cout << dd.cap() << std::endl;

    Mystring aa = cc + dd;
    aa.print();

    return 0;
}
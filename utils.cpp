#include "utils.h"

namespace MyExel {
//Vector
Vector::Vector(int c) : data(new std::string[c]), capacity(c), length(0){}

Vector::~Vector() {delete[] data;}

std::string Vector::operator[](int i){return data[i];}

void Vector::info() {
    std::cout << "capacity :" << capacity << std::endl;
    std::cout << "length :" << length << std::endl;
    for (int i=0; i < length; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}

void Vector::push_back(std::string s) {
    if (capacity <= length) {
        std::string* temp = new std::string[capacity*2];
        for (int i=0; i < length; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data =temp;
        capacity *= 2;
    }
    data[length] = s;
    length++;
}

void Vector::remove(int x) {
    for (int i=x+1; i < length; i++) {
        data[i-1] = data[i];
    length--;
    }
}

//Stack
Stack::Stack() : start(nullptr, ""){
            curent = &start;
        }

Stack::~Stack() {
    while (curent != &start) {
        Node* prev = curent;
        curent = curent -> prev;
        delete prev;
    }
}

void Stack::push(std::string s) {
    Node* n = new Node(curent, s);
    curent = n;
}

std::string Stack::pop() {
    if (curent == &start){return "";}
    std::string s = curent->s;
    Node* prev = curent;
    curent = curent->prev;
    delete prev;
    return s;
}

std::string Stack::peek() {
    return curent->s;
}

bool Stack::is_empty() {
    if (curent == &start){return true;}
    return false;
}
}

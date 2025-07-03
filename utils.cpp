#include "utils.h"

namespace MyExel {
//Vector
Vector::Vector(int c) : data(new std::string[c]), capacity(c), length(0){}

Vector::~Vector() {delete[] data;}

std::string Vector::operator[](int i){return data[i];}

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
    }
    length--;
}

void Vector::info() {
    std::cout << "capacity :" << capacity << std::endl;
    std::cout << "length :" << length << std::endl;
    for (int i=0; i < length; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}

int Vector::size() { return length; }

//Stack
Stack::Stack() : start(nullptr, ""){
            current = &start;
        }

Stack::~Stack() {
    while (current != &start) {
        Node* prev = current;
        current = current -> prev;
        delete prev;
    }
}

void Stack::push(std::string s) {
    Node* n = new Node(current, s);
    current = n;
}

std::string Stack::pop() {
    if (current == &start){return "";}
    std::string s = current->s;
    Node* prev = current;
    current = current->prev;
    delete prev;
    return s;
}

std::string Stack::peek() {
    return current->s;
}

bool Stack::is_empty() {
    if (current == &start){return true;}
    return false;
}

//NumStack
NumStack::NumStack() : start(nullptr, 0) { current = &start; }

NumStack::~NumStack() {
  while (current != &start) {
    Node* prev = current;
    current = current->prev;
    delete prev;
  }
}

void NumStack::push(double s) {
  Node* n = new Node(current, s);
  current = n;
}

double NumStack::pop() {
  if (current == &start) return 0;

  double s = current->s;
  Node* prev = current;
  current = current->prev;

  // Delete popped node
  delete prev;
  return s;
}

double NumStack::peek() { return current->s; }

bool NumStack::is_empty() {
  if (current == &start) return true;
  return false;
}

}

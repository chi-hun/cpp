// #pragma once
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>

namespace MyExel {
class Vector {
    private: 
        std::string* data;
        int capacity;
        int length;
    
    public:
        Vector(int c=1);
        ~Vector();
        std::string operator[](int i);
        void push_back(std::string s);
        void remove(int x);
        void info();
        int size();
};

class Stack {
    private:
        struct Node{
            Node* prev;
            std::string s;

            Node(Node* prev, std::string s) : prev(prev), s(s){};
        };

        Node* current;
        Node start;

    public:
        Stack();
        ~Stack();
        void push(std::string s);
        std::string pop();
        std::string peek();
        bool is_empty();
};

class NumStack {
    private:
        struct Node {
            Node* prev;
            double s;

            Node(Node* prev, double s) : prev(prev), s(s) {}
        };

        Node* current;
        Node start;

    public:
        NumStack();
        ~NumStack();
        void push(double s);
        double pop();
        double peek();
        bool is_empty();

};


}
#endif
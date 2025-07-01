// 8-1

#include <iostream>
#include <string>

class Vector {
    private: 
        std::string* data;
        int capacity;
        int length;
    
    public:
        Vector(int c=1) : data(new std::string[c]), capacity(c), length(0){};
        ~Vector() {delete[] data;};
        std::string operator[](int i){return data[i];};
        void push_back(std::string s);
        void remove(int x);
};

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


int main(void) {

    std::cout << "Dd" << std::endl;

    return 0;
}

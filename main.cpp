// 7-2

#include <iostream>
#include <string>
#include <fstream>

int main(void) {

    std::ifstream in("test.txt", std::ios::binary);
    std::string s;
    int x;

    if (in.is_open()) {
        while (in >> s) {
            in.read((char*)(&x), 4);
            std::cout << std::hex<< x << std::endl;}
    } else {
        std::cout << "error" << std::endl;
    }
    return 0;
}



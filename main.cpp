// 7-1

#include <iostream>
#include <string>

int main(void) {
    int i;
    while(true) {
        std::cout << "입력" << std::endl;
        std::cin >> i;
        std::cout << i << std::endl;
        if (std::cin.fail()) {
            std::cout << "입력 똑바로" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
        if (i==1){break;}
    }
    return 0;
}



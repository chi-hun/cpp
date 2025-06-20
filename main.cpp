#include <iostream>
#include "plus.h"
using plus::plusplus;

int main(int argc, char *argv[]) {
        int a = 10;
        int b = plusplus(a);

        std::cout << "결과는  " << b << std::endl;
        return 0;
}
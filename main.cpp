// 5-4
#include <iostream>
#include <string.h>

class Int {
    private:
        int data;

    public: 
        Int(int d) : data(d){};
        operator int() {return data;}

};

int main(void) {
    Int a = 4;
    std::cout << a + 2 << std::endl;    
     
   return 0;
}
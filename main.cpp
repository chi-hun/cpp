// 12-1
#include <iostream>

using namespace std;

template <typename T>
class Vector {
    private:
        T* data;
        size_t size_;

    public:
        Vector(size_t size) : size_(size) {
            data = new T[size];
            for (size_t i=0; i < size; i++) {
                data[i] = 5;
            }
        }
        ~Vector() {
            delete[] data;
        }
        const T& at(size_t index) const {
            if (index >= size_) {
                throw out_of_range("띠디 안되요"); 
            }
            return data[index];
        }

};


int main() {
    Vector<int> aa(10);
    int data = 0;
    try {
        data = aa.at(12);
    } catch (out_of_range& e) {
        cout << "ㅋ" << e.what() << endl;
    }
    cout << data << endl;
    return 0;
}


// 5-4
#include <iostream>

namespace MyArray {
class Array;
class Int;

class Array {
    private:
        const int dim;
        int* size;
        friend class Int;

        struct Address {
            int level;
            void* next;
        };
        Address* top;
    
    public:
        Array(int dim, int* array_size) : dim(dim) {
            size = new int[dim];
            for (int i = 0; i < dim; i++) {
                size[i] = array_size[i];

            top = new Address;
            top -> level = 0;
            initial_address(top);
            }
        }
        Array(const Array& arr) : dim(arr.dim) {
            size = new int[dim];
            for (int i = 0; i < dim; i++) {
                size[i] = arr.size[i];
            }
            top = new Address;
            top -> level = 0;
            initial_address(top);
            copy_address(top, arr.top);
        }
        ~Array() {
            delete_address(top);
            delete[] size;
        }
        void initial_address(Address* current);
        void delete_address(Address* current);
        void copy_address(Address* to, Address* from);
        Int operator[](const int index);

};

class Int {
        private:
            int level;
            void* data;
            Array* arr;

        public:
            Int(int index, int level =0, void* data = nullptr, Array* arr = nullptr) 
            : level(level), data(data), arr(arr) {
                if (level < 1 || index >= arr -> size[level - 1]) {
                    data = nullptr;
                    return;
                }
                if (level == arr -> dim) {
                    data = static_cast<void*>(
                        static_cast<int*>(static_cast<Array::Address*>(data) -> next) + index);
                } else {
                    data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data) -> next) + index);
                }
            }
        Int operator[](int index) {
            return Int(index, level + 1, data, arr);
        }

        operator int() {
            if (data) return *static_cast<int*>(data);
            return 0;
        }
        
};

void Array::initial_address(Address* current) {
    if (!current) {return;}
    if (current -> level == dim - 1) {
        current -> next = new int[size[current -> level]];
        return;
    }
    current -> next = new Address[size[current -> level]];
    for (int i = 0; i < size[current -> level]; i++) {
        (static_cast<Address*>(current -> next) + i) -> level = current -> level + 1;
        initial_address(static_cast<Address*>(current -> next) + i);
    }
}

void Array::delete_address(Address* current) {
    if (!current) {return;}
    for (int i = 0; current->level != dim - 1 && i < size[current -> level]; i++) {
        delete_address(static_cast<Address*>(current -> next) + i);        
    }
    if (current -> level == dim - 1) {
        delete[] static_cast<int*>(current -> next);
    }else{
        delete[] static_cast<Address*>(current -> next);
    }
}

void Array::copy_address(Address* to, Address* from) {
    if (to -> level == dim - 1) {
        for (int i = 0; i < size[to -> level]; i++) {
            static_cast<int*>(to -> next)[i] = static_cast<int*>(from -> next)[i];
        }
        return;
    }
    for (int i = 0; i < size[to -> level]; i++) {
        Address* to_next = static_cast<Address*>(to -> next) + 1;
        Address* from_next = static_cast<Address*>(from -> next) + 1;
        copy_address(to_next, from_next);
    }
}

Int Array::operator[](const int index) {
        return Int(index, 1, static_cast<void*>(top), this);
        }

}


int main(void) {
    int size[2] = {2,2};
    MyArray::Array arr(3, size);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            arr[i][j] = (i+1)*(j+1);
        }
    }
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         std::cout <<arr[i][j] << std::endl;
    //     }
    // }
    std::cout << arr[0][1];
    return 0;
}

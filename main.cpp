// 1-3
#include <iostream>
#include <string.h>

struct Animal {
    char name[20];
    int age;
    int health;
    int hungry;
};

void new_animal(Animal* ani);
    
int main(void) {
    int n_animal;
    std::cout << "동물의 수량 : ";
    std::cin >> n_animal;
    Animal* animals = new Animal[n_animal];

    char name[20];
    int age;
    int health;
    int hungry;

    new_animal(&animals[0]);

    std::cout << "name : " <<animals[0].name << std::endl;
    std::cout << "age : " <<animals[0].age << std::endl;
    std::cout << "health : " <<animals[0].health << std::endl;
    std::cout << "hungry : " <<animals[0].hungry << std::endl;

    delete[] animals;

    return 0;
}

void new_animal(Animal* ani) {
    
    std::cout << "이름 : ";
    std::cin >> ani -> name;
    std::cout << "나이 : ";
    std::cin >> ani -> age;
    std::cout << "체력 : ";
    std::cin >> ani -> health;
    std::cout << "배부름 : ";
    std::cin >> ani -> hungry;
}
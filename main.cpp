// 4-4
#include <iostream>
#include <string.h>

class Marine {
    private:
        static int total_num;
        char* name;
        int hp;
        int damage;
        int x;
        int y;
        bool is_dead;

    public:
        Marine();
        Marine(int x, int y);
        Marine(const Marine& master);
        ~Marine();
        void show_status();
        void move(int _x, int _y);
        int attack();
        void be_attacked(int damage);
        int& access_damage();
};

int Marine::total_num = 0;

Marine::Marine() : name(NULL), hp(50), damage(5), x(0), y(0), is_dead(false) {
    total_num++;
}

Marine::Marine (int x, int y) : name(NULL), hp(50), damage(5), x(x), y(y), is_dead(false) {
    total_num++;
}

Marine::Marine(const Marine& master) {
    name = new char[strlen(master.name) + 1];
    strcpy(name, master.name);
    hp = master.hp;
    damage = master.damage;
    x = master.x;
    y = master.y;
    is_dead = false;
}

Marine::~Marine() {
    std::cout << "delete " << name << std::endl;
    total_num--;
    delete[] name;
}

void Marine::show_status() {
    if (name == NULL) {
        std::cout << "no name" << std::endl;
    } else {
        std::cout << "name: " << name << std::endl;
    }
    std::cout << "hp: " << hp << std::endl;
    std::cout << "damage: " << damage << std::endl;
    std::cout << "position: (" << x << ", " << y << ")" << std::endl;
    std::cout << "is_dead: " << (is_dead ? "true" : "false") << std::endl;
    std::cout << "total_num: " << total_num << std::endl;
}

void Marine::move(int _x, int _y) {
    x = _x;
    y = _y;
}

int Marine::attack() {
    return damage;
}

void Marine::be_attacked(int damage) {
    hp -= damage;
    if (hp <= 0) {
        is_dead = true;
    }
}

int& Marine::access_damage() {
    return damage;
}

int main(void) {
    Marine marine_1;
    marine_1.show_status();

    Marine marine_2(3, 4);
    marine_2.show_status();

    int& marine_2_access_damage = marine_2.access_damage();
    marine_2_access_damage = 50;
    marine_2.show_status();

    return 0;
}

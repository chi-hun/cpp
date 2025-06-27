// 5-4
#include <iostream>
#include <string>

class C_slave {
    // private:
    //     std::string name;
    //     std::string position;
    //     int age;
    //     int grade;

    protected:
        std::string name;
        std::string position;
        int age;
        int grade;

    public:
        C_slave(){};
        C_slave(std::string name, std::string position, int age, int grade) 
        : name(name), position(position), age(age), grade(grade) {};
        C_slave(C_slave& slave) : name(slave.name), position(slave.position), age(slave.age), grade(slave.grade) {};
        ~C_slave(){};
        int calculate_pay();
        void print_info();
};

class C_slave_h : public C_slave {
    private:
        int work_year;
    
    public:
        C_slave_h() {};
        C_slave_h(std::string name, std::string position, int age, int grade, int work_year) 
        : C_slave(name, position, age, grade), work_year(work_year) {}; 
        C_slave_h(C_slave_h& slave) 
        : C_slave(slave.name, slave.position, slave.age, slave.grade), work_year(slave.work_year) {};
        ~C_slave_h(){};
        int calculate_pay();
        void print_info();
        
};

class C_slave_list {
    private:
        int alloc_slave;
        int current_slave;
        int current_slave_h;
        C_slave** slave_list;
        C_slave_h** slave_list_h;

    public:
        C_slave_list(int alloc_slave) : alloc_slave(alloc_slave), current_slave(0), current_slave_h(0) {
            slave_list = new C_slave*[alloc_slave];
            slave_list_h = new C_slave_h*[alloc_slave];
        };
        ~C_slave_list();
        void add_slave(C_slave* slave);
        void add_slave_h(C_slave_h* slave);
        int slave_num() {return current_slave + current_slave_h;};
        void print_info();

};

int C_slave::calculate_pay() {
    int pay = 200 + grade *50;
    return pay;
}

void C_slave::print_info() {
    std::cout << "이름 : " << name << std::endl;
    std::cout << "직위 : " << position << std::endl;
    std::cout << "나이 : " << age << std::endl;
    std::cout << "급여 : " << calculate_pay() << std::endl;
}

int C_slave_h::calculate_pay() {
    int pay = 200 + grade *50 + work_year * 10;
    return pay;
}

void C_slave_h::print_info() {
    std::cout << "이름 : " << name << std::endl;
    std::cout << "직위 : " << position << std::endl;
    std::cout << "나이 : " << age << std::endl;
    std::cout << "근속년수 : " << work_year << std::endl;
    std::cout << "급여 : " << calculate_pay() << std::endl;
}

void C_slave_list::add_slave(C_slave* slave) {
    slave_list[current_slave] = slave;
    current_slave++;
}

void C_slave_list::add_slave_h(C_slave_h* slave) {
    slave_list_h[current_slave_h] = slave;
    current_slave_h++;
}

C_slave_list::~C_slave_list() {
    for (int i = 0; i < current_slave; i++) {
        delete slave_list[i];
    }
    delete[] slave_list;
}
void C_slave_list::print_info() {
    int total_pay = 0;
    for (int i = 0; i < current_slave; i++) {
        slave_list[i] -> print_info();
        total_pay += slave_list[i] -> calculate_pay();
    }
    for (int i = 0; i < current_slave_h; i++) {
        slave_list_h[i] -> print_info();
        total_pay += slave_list_h[i] -> calculate_pay();
    }
    std::cout << "총 급여 : " << total_pay << std::endl;
}

int main(void) {
    C_slave_list k_slave_list(10);
    k_slave_list.add_slave(new C_slave("김모씨", "대리", 25, 1 ));
    k_slave_list.add_slave(new C_slave("이모씨", "과장", 27, 2 ));
    k_slave_list.add_slave(new C_slave("박모씨", "부장", 29, 3 ));
    k_slave_list.add_slave_h(new C_slave_h("최모씨", "차장", 31, 4, 5));
    k_slave_list.print_info();

    return 0;
}
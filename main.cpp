// 1-3
#include <iostream>
#include <string.h>

class Ball {
    private:
        int x;
        int y;
    public:
        Ball (int _x, int _y) {
            x = _x;
            y = _y;
        }

        void print();
        void move(int _x, int _y);
        int s_x();
        int s_y();
        int distance(Ball ball_d);
};

void Ball::print() {
    std::cout << "x : " << x << ", " << "y : " << y << std::endl;
}

void Ball::move(int _x, int _y) {
    x += _x;
    y += _y;
}

int Ball::s_x() {
    return x;
}

int Ball::s_y() {
    return y;
}

int Ball::distance(Ball ball_d) {
    int x_d = ball_d.s_x();
    int y_d = ball_d.s_y();
    
    return ((x - x_d) * (x - x_d) + (y - y_d) * (y - y_d));
}   
    
int main(void) {
    Ball ball_1(1,2);
    ball_1.print();

    Ball ball_2(3,4);
    ball_2.print();
    ball_2.move(1,1);
    ball_2.print();

    int dd = ball_1.distance(ball_2);
    std::cout << dd << std::endl;

    return 0;
}

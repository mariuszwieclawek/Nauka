#include <iostream>

using namespace std;

class Circle{
    private:
        float radius_;
        float area_;
        float circumference_;

    public:

    Circle(float);
    float setRadius(float r);
    float getRadius();
    float getArea();


};



Circle::Circle(float radius_):radius_(radius_){
    area_ = radius_ * radius_ * 3.14;
    circumference_ = radius_ * 2 * 3.14;
}

float Circle::setRadius(float r){
    radius_ = r;
    return radius_;
}


float Circle::getRadius(){
    return radius_;
}

float Circle::getArea(){
    return area_;
}

int main(){
    Circle C1(20);
    cout << C1.getArea() << endl;
    return 0;
}

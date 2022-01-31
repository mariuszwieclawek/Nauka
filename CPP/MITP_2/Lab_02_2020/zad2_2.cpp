
#include <iostream>

using namespace std;

class Circle {
public:
  float radius_;
  Circle() {}; //konstruktor bezparametryczny, bez niego program nie dzia³a
  Circle(float r){radius_=r;}
  void wyswietl() {
  cout<< "Promien wynosi: "<<radius_<<endl;
  }
};


int main()
{
    Circle kolo, okrag;
    Circle C3(4); // stworzony nowy obiekt za pomoc¹ konstruktora

    kolo.radius_ = 5.6;
    okrag.radius_ = 6.8;

    kolo.wyswietl();
    okrag.wyswietl();
    C3.wyswietl();
}

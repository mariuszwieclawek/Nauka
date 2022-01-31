#include <iostream>

using namespace std;

class Circle {
public:
  float * radius_;
  ~Circle();
  Circle() {
      radius_ = new float;
      }
  void wyswietl() {
  cout<< "Promien wynosi: "<<radius_<<endl;
  }
};


int main()
{
    Circle kolo, okrag;


    kolo.radius_ = 5.6;
    okrag.radius_ = 6.8;

    kolo.wyswietl();
    okrag.wyswietl();

}


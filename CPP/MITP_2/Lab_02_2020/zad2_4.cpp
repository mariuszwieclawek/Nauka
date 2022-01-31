#include <iostream>

using namespace std;

class Circle {
public:
  float radius_;
  float circumference();
  float area();
  void wyswietl() {
  cout<< "Promien wynosi: "<<radius_<<endl;
  }
  void oblicz_pole(){
      cout<< "Pole kola to: "<< area()<< endl;
  }

  void oblicz_obwod(){
    cout<< "Obwod kola to: " << circumference()<<endl;
    }
};

float Circle::circumference(){
    return( 2 * 3.14 * radius_ );
}

float Circle::area(){
return( 3.14 * radius_ * radius_ );
}

int main()
{
    Circle kolo, okrag;
    kolo.radius_ = 5.6;
    okrag.radius_ = 6.8;

    kolo.wyswietl();
    kolo.oblicz_obwod();
    kolo.oblicz_pole();

    okrag.wyswietl();
    okrag.oblicz_obwod();
    okrag.oblicz_pole();
}

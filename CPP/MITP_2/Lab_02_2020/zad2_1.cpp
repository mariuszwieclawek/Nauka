//w funkcji main utwórz dwa obiekty klasy
//zinicjalizuj ich sk³adow¹ radius_ jak¹s wartoœci¹


#include <iostream>

using namespace std;

class Circle {
public:
  float radius_;
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

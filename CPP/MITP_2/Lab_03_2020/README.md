# Lab 03 
## **C++. Przeciążanie**
### Zajęcia laboratoryjne nr 3 - Metodyka i Techniki Programowania II

*Autorzy instrukcji: dr inż. Jarosław Bułat, mgr inż. Artur Kos*

Wykład do laboratorium: PI_09.pdf, PI_11.pdf
  
#### Zadanie 1. Przeciążanie konstruktora.
  
1. Uruchom program `Ex_1.cc`:

```cpp 
#include <iostream>
#include <stdio.h>
using namespace std;

class Vector {
public:
    Vector(double);
    int dimension_;
private:
    double data_[3] = { 0, 0, 0 };
};

Vector::Vector(double element1)
{
    cout << "\n Tworzenie obiektu klasy Vector w przestrzeni R1 :" << endl;
    dimension_ = 1;
    data_[0] = element1;
}

int main()
{
    Vector r1(1.0); // R1
    cout << "Obiekt klasy Vector o wymiarze:" << r1.dimension_ << endl;
}
```

2. Uzupełnij klasę `Vector` o konstruktory z 2 i 3 argumentami odpowiadającymi 2 lub 3 wymiarowym wektorom.  
3. Zmień odpowiednio treść informacji wyświetlanej podczas tworzenia obiektów przeciążonymi konstruktorami.
Zmień  wartości przypisywane do zmiennej `dimension_`( składowej informującej o wymiarowości wektora).
5. Zademonstruj w funkcji `main ()` wywołanie wszystkich przeciążonych konstruktorów.  



#### Zadanie 2. Przeciążanie metody.
  
1. Uzupełnij zmodyfikowany (przez dodany przeciążony konstruktor) kod z zadania nr 1 o dwie przeciążone metody klasy `Vector`. 
2. Pierwsza z nich powinna:
- być wywoływana obiektem typu `Vector`
- wyświetlać wartości wszystkich elementów tablicy `data_` (w oparciu o wymiarowość zapisaną w składowej `dimension_`) obiektu typu Vector którym została wywołana.
3. Druga metoda powinna:
- być bezparametryczna 
- wyświetlać wartości wszystkich elementów tablicy `data_` (w oparciu o wymiarowość zapisaną w składowej `dimension_`) obiektu typu `Vector` **na** którym została wywołana.
4. Zademonstruj w funkcji `main ()` działanie obu przeciążonych metod. W tym celu:
- utwórz 2 obiekty typu `Vector`: obiekt pierwszy 2-wymiarowy, obiekt drugi 3-wymiarowy
- wywołaj metodę bezparametryczną na obiekcie 2-wymiarowym
- wywołaj metodę parametryczną na obiekcie 2-wymiarowym. Jako parametru użyj obiektu 3-wymiarowego


#### Zadanie 3.  Przeciążanie funkcji.
  
1. Uzupełnij zmodyfikowany (przez dodany przeciążony konstruktor) kod z zadania nr 1 o dwie przeciążone funkcje (zewnętrzne funkcje, nie metody klasy `Vector`). W tym celu zmień specyfikator dostępu składowej `data_` na `public`.
2. Pierwsza z nich powinna:
- obliczać moduł wektora  w przestrzeni R3 zapisanego w tablicy 3-elementowej ze współrzędnymi wektora
-  przyjmować jako parametr wskaźnik do tablicy 3-elementowej ze współrzędnymi wektora
- zwracać obliczony moduł
4. Druga metoda powinna:
 -  obliczać moduł wektora w przestrzeni R3 zapisanego w obiekcie klasy  `Vector`
 -  być wywoływana obiektem typu `Vector`
 - zwracać obliczony moduł
5. Zademonstruj w funkcji `main ()` działanie obu przeciążonych funkcji.  


### Zadanie 4.  Przeciążanie funkcji.
1. W kodzie z poprzedniego z zadania 3 zmień specyfikator dostępu składowej `data_` z powrotem na `private`.
2. Uruchom kod. Dlaczego wystąpił błąd?
3. Rozwiąż problem w oparciu o funkcję zaprzyjaźniona z klasą.


### Zadanie 5. Przeciążony operator definiowany wewnątrz klasy.

1. Uzupełnij zmodyfikowany (przez dodany przeciążony konstruktor) kod z zadania nr 1 o nową wewnętrzną (będącą składową klasy) definicję operatora `+`.
2. Przeciążony operator powinien:
- być wywoływany przez obiekty typu `Vector`. 
- służyć do dodawania odpowiadających sobie elementów tablic składowych `data_` obiektów typu `Vector`. 
- tworzyć nowy obiekt typu`Vector`, do  przechowywania w nim wyniku działania . 
3. Zademonstruj w funkcji `main ()` działanie przeciążonego operatora.  



### Zadanie 6. Przeciążony operator definiowany poza klasą.

1. Uzupełnij zmodyfikowany (przez dodany przeciążony konstruktor) kod z zadania nr 1 o nową zewnętrzną (nie będącą składową klasy) definicję operatora `+`. W tym celu zmień specyfikator dostępu składowej `data_` na `public`.
2. Przeciążony operator powinien:
- być wywoływany przez obiekty typu `Vector`. 
- służyć do dodawania odpowiadających sobie elementów tablic składowych `data_` obiektów typu `Vector`. 
- tworzyć nowy obiekt typu`Vector`, do  przechowywania w nim wyniku działania . 
3. Zademonstruj w funkcji `main ()` działanie przeciążonego operatora.  


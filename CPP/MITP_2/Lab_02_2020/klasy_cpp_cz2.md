# Lab 02
## C++: Klasy cz. 2

### Zajęcia laboratoryjne nr 2 - Metodyka i Techniki Programowania II

*Autorzy instrukcji: dr inż. Jarosław Bułat, mgr inż. Artur Kos*

Wykład do laboratorium: PI_09.pdf

#### Zadanie 1. Prosta klasa
Klasa Circle jest zdefiniowana jako:

```c++
class Circle {
public:
  float radius_;
}
```

1. W funkcji `main()` utwórz dwa obiekty tej klasy.
2. Zainicjalizuj ich składową `radius_` wybranymi liczbami.

#### Zadanie 2. Konstruktor
Rozszerz klasę z zadania 1 dodając konstruktor:
1. Zadeklaruj i zdefiniuj konstruktor z 1 parametrem reprezentującym promień okręgu, który powinien być przypisywany do składowej `radius_`.
2. W funkcji `main()` utwórz nowy obiekt używając zdefiniowanego konstruktora i wybranej liczby (przekazywanej jako parametr).
    Dlaczego wystąpił błąd?
3. Rozwiąż problem dodając konstruktor bezparametryczny.

#### Zadanie 3. Destruktor
Rozszerz klasę zdefiniowaną w zadaniu 1 o destruktor (nie bazuj na programie utworzonym w punkcie Zadanie 2):
1. Zmień typ elementu `radius_` z float na `float *`.
2. Dodaj konstruktor, który powinien alokować pamięć i przypisywać ją do `radius_`;
3. Dodaj destruktor.
4. W funkcji `main()` zademonstruj poprawność działania konstruktora i destruktora.

#### Zadanie 4. Metody
Rozszerz klasę zdefiniowaną w zadaniu 1 (nie bazuj na programie utworzonym w poprzednich punktach) metodami:
1. Zadeklaruj i zdefiniuj dwie metody bezparametrowe:
 `circumference()` i `area()` obliczające odpowiednio: obwód i powierzchnię koła.
2. Obie metody powinny wykorzystywać do obliczeń element `radius_`.
3. Metody powinny obliczać i zwracać wynik i niczego nie wyświetlać.
4. Zdefiniuj obie metody poza deklaracją klasy.
5. W funkcji `main()` zademonstruj poprawność działania obu metod.

#### Zadanie 5. Inicjalizacja składowych prywatnych
Klasa `Circle` jest zdefiniowana jako:

```cpp
#include <iostream>
using namespace std;

class Circle{
private:
  float radius_;
  float area_;
  float circumference_;

public:
  Circle(float);
};
```

1. Dodaj definicję konstruktora inicjalizującego składowe `radius_` i `area_`.
2. W funkcji `main()` utwórz nowy obiekt za pomocą konstruktora.
3. Zastąp definicję konstruktora nową definicją z listą inicjalizującą.
4. W funkcji `main()` utwórz nowy obiekt za pomocą konstruktora z listą inicjalizującą.

#### Zadanie 6. setter i getter
1. W oparciu o program utworzony w punkcie Zadanie 5. rozszerz klasę Circle o:
- setter modyfikujący element `radius_`
- getter zwracający wartość elementu `radius_`
2. Zademonstruj działanie setter-a i getter-a w funkcji `main()`.

 
### UWAGA!

**ZACHOWAJ KODY PROGRAMÓW NA NASTĘPNE ZAJĘCIA LABORATORYJNE **

 

#### Literatura:
1.Wykłady z sem. 1.

2.Dowolna pozycja literaturowa z zakresu.

 

 

 

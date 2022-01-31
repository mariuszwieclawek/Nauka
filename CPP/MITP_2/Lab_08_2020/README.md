# Lab 08

### Matlab. Wprowadzenie cd.
wykład do laboratorium:PI_II_01.pdf, PI_II_02.pdf

### Ex0.  Funkcje matematyczne. `plot()`, `title()`, opisy osi.
Utwórz nowy skrypt w którym:
1. Oblicz wartości wielomianów/funkcji:

     *y1(x) = x^2 + 1*     
     *y2(x) = x^3 + x^2 + x + 1*  
     
    dla *x ∈* <−5, 5>
    
   Przyjmij krok pomiędzy kolejnymi punktami dziedziny zapewniający dobre odwzorowanie przebiegu funkcji.
2. Wklej poniższy fragment kodu i przeanalizuj jego działanie uruchamiając go linia po linii (zaznaczenie linii + `F9`):
    ```
    figure(2)
    plot(y1,'r.');
    hold on
    plot(y1,'r');

    title('Tytuł wykresu np. y_1 wykreślone dwoma rodzajami znaczników')
    xlabel('oś X')
    ylabel('oś Y')
    grid on
    ```
3. Zmodyfikuj kod tak, aby opisy osi i tytuł opisywały zawartość wykresu. Dodaj do wykresu legendę (polecenie `legend()`).
4. W punkcie 2 zostały wykreślone obliczone wartości pierwszego z wielomianów (z punktu 1) w funkcji **indeksów** elementów wektora dziedziny. W oparciu o dokumentację funkcji `plot()` (w oknie `Command Window` wpisz `doc plot`) w nowej figurze (polecenie `figure(3);`) wykreśl (na jednym wykresie) obliczone wartości obu wielomianów (z punktu 1) w funkcji **dziedziny** *x*.
5. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.
<napisz pętle w której bedzie obliczana wartość funkcji dla każdego elementu dziedziny, zachowaj liczby w utworzonym wektorze>

### Ex1. `subplot()`
1. Przy użyciu w funkcji `subplot()`wykreśl wartości funkcji  *y1  i y2* w funkcji dziedziny *x* (każda w osobnym  oknie, pierwsze okno poniżej drugiego).
2. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex2. Pętle i operacje na wektorach cd.
1. Oblicz wartości funkcji  *y1*  i *y2* dla każdego pojedynczego argumentu dziedziny *x* (bez korzystania z przeciążania operatorów dla argumentów wektorowych). Użyj pętli i nowych wektorów do przechowywania obliczonych wartości funkcji *y1*  i *y2*.
2. Wyniki obliczeń powinny być identyczne jak uzyskane w ćwiczeniu **Ex0** - porównaj je na jednym wykresie. 
3. Dodaj tytuł wykresu, opisy obu osi, legendę oraz siatkę.
4. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex3.  Funkcje cd. 
1. Napisz funkcję która będzie obliczała wartości obu funkcji (z zadania **Ex0** w punkcie (dla każdego  pojedynczego argumentu dziedziny). Funkcja powinna:
 - przyjmować 1 argument (pojedynczy argument dziedziny)
 - zwracać obliczone wartości obu wielomianów 
2. Za pomocą utworzonej funkcji oblicz wartości wielomianów dla *x ∈* <5, 5> (wykorzystując kod z poprzedniego zadania).
3. Wyniki obliczeń powinny być identyczne jak uzyskane w ćwiczeniach **Ex0** i **Ex2** - porównaj je na jednym wykresie. 
4. Dodaj tytuł wykresu, opisy obu osi, legendę oraz siatkę.
5. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex3a.  Funkcje cd. 
1. Zmodyfikuj funcję z zad **Ex3**  tak, aby: 
  -  przyjmowała cały wektor dziedziny jako argument
  -  zwracała wektor wartości obliczonych dla całego wektora
2. Porównaj uzyskane wyniki  z otrzymanymi w zad **Ex0**, **Ex2** i **Ex3** na jednym wykresie.
3. Dodaj tytuł wykresu, opisy obu osi, legendę oraz siatkę.
4. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex3b.  Funkcje cd. `polyval()`. 
1. Zapoznaj się z dokumentacją funkcji `polyval()`, i za jej pomocą rozwiąż problem postawiony w zadaniu **Ex0**. 
2. Porównaj uzyskane wyniki  z otrzymanymi w zad **Ex0** na jednym wykresie.
3. Dodaj tytuł wykresu, opisy obu osi, legendę oraz siatkę.
4. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex4.  Zapisywanie wyników obliczeń.
1. Zapoznaj się z dokumentacją funkcji `save()`, oraz `load()`. 
2. Zapisz jako `lab_08.mat` wektor dziedziny `x` oraz obliczone dla niego wartości obu wielomianów.
3. Wyczyść `Worskpace`, zaimportuj `lab_08.mat` i sprawdź czy zmienne wymienione w pkt. 2 zostały zapisane.

### Ex5.  Funkcja `size()`
1. Umieść w skrypcie poniższy kod. Przeanalizuj jego działanie uruchamiając go linia po lini (zaznaczenie linii + `F9`):
```
clear;
clc;
A = [1 2 3;4 5 6]
size(A)
sA = size(A)
[rows columns] = size(A)
sAr=size(A,1)
sAc=size(A,2)
```

### Ex6.  Funkcje `unique(),find(),sub2ind()`.
Umieść w skrypcie poniższy kod. Przeanalizuj jego działanie uruchamiając go linia po lini (zaznaczenie linii + `F9`):
```
clear;
clc;
A = [1 2 3;4 5 6]
A
A(:)
find(A==3)
find(A(:)==3)
ind = find(A==3)
[rows_ind columns_ind] = find(A==3)
[rows_ind_a columns_ind_a] = find(A(:)==3)
A(rows_ind(1), columns_ind(1))
A(ind(1))
A(rows_ind_a(1), columns_ind_a(1)) % Błąd. Dlaczego?
```
1. Zaimportuj plik`tab_5.mat`.
2. Znajdź funkcje `Matlab-a` odpowiedzialne za obliczanie wartości średniej i odchylenia standardowego.
Zapoznaj się z ich dokumentacją. Oblicz za ich pomocą wymienione wielkości dla macierzy zapisanej w`tab_5.mat`.
3.  Zapoznaj się z dokumentacją funkcji `unique()` i utwórz za jej pomocą wektor wartości unikalnych występujących w  macierzy.
4. Zapoznaj się z dokumentacją funkcji `find()`, `sum()` oraz `ind2sub()`i `sub2ind()`. Za ich pomocą utwórz histogram wartości występujących w  macierzy.
5. Wykreśl utworzony histogram za pomocą funkcji `bar()`.
6. Porównaj rezultat z otrzymanym za pomocą funkcji `Matlab-a` `histogram()`.
7. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.


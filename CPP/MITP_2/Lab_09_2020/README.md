

# Lab 09

## Matlab. Operacje na macierzach. Podstawy przetwarzania sygnałów.
wykład do laboratorium:PI_II_01.pdf, PI_II_02.pdf

### Ex0. Funkcje `find(),sub2ind()`.
1. Umieść w skrypcie poniższy kod. Przeanalizuj jego działanie uruchamiając go linia po lini (zaznaczenie linii + `F9`):
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
2. Zaimportuj plik `tab_4.mat`.
3. Zapoznaj się z dokumentacją funkcji `Matlab-a` odpowiedzialnych za obliczanie wartości średniej i odchylenia standardowego `mean()` oraz `std()`.
4. Oblicz za ich pomocą wymienione wielkości dla macierzy zapisanej w `tab_4.mat`.
5. Za pomocą funkcji `mean()` oblicz wartość średnią:
 * a) elementów całej macierzy `tab_4.mat`
 * b) elementów każdej kolumny macierzy `tab_4.mat`
6. Zapoznaj się z dokumentacją funkcji `find()`oraz `ind2sub()`, `sub2ind()`. 
7. Za pomocą funkcji `mean()` znajdź wszystkie elementy macierzy `tab_4.mat` o wartościach mniejszych niż dwukrotność wartości średniej wszystkich elementów macierzy. 
8. Wyzeruj (przypisz wartość równą 0) wszystkie znalezione elementy. Zweryfikuj rezultat, sprawdź czy znalezione wartości rzeczywiście zostały wyzerowane (wyświetl wartość znalezionego elementu).
9. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex1. Podstawy przetwarzania sygnałów. Obrazy. Histogram wartości.
Macierz dwuwymiarowa (o wartościach rzeczywistych) może być również przedstawiona jako obraz. 
1. Zapoznaj się pobieżnie z dokumentacją funkcji `imshow()` oraz `imagesc()`.
2. Zaimportuj plik `tab_4.mat`.
3. Za pomocą `imshow()` lub `imagesc()`wyświetl jako obraz:
- macierz jednostkową wygenerowaną za pomoca funkcji `eye()` np:
 `I=eye(32)`
- macierz `tab_4`
4. Zapoznaj się z dokumentacją funkcji `histogram()` i wyświetl za jej pomocą histogramy wartości elementów macierzy `I` oraz `tab_4.mat`.

### Ex2. Funkcje `unique(),find(),sub2ind()`. Histogram wartości.
1. Zaimportuj ponownie plik `tab_4.mat`.
2. Zapoznaj się z dokumentacją funkcji `unique()` i utwórz za jej pomocą wektor z unikalnymi wartościami elementów macierzy `tab_4.mat`.
3. Zapoznaj się z dokumentacją funkcji `histogram()` i utwórz za jej pomocą histogram wartości elementów macierzy `tab_4.mat`.
4. Za pomocą funkcji `unique`, `find()`oraz `ind2sub()`, `sub2ind()` spróbuj utwórzyć własną implementację histogramu i oblicz za jej pomocą wartości elementów macierzy `tab_4.mat`.
5. Wykreśl utworzony histogram za pomocą funkcji `bar()`.
6. Porównaj rezultat z otrzymanym za pomocą funkcji `Matlab-a` `histogram()`.
7. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex3. Podstawy przetwarzania sygnałów. Aliasing.
1. Wykreśl 4 przebiegi napięcia sinusoidalnego o amplitudzie A = 325 V, częstotliwości f = 50 Hz i czasie trwania od 0 do T = 0.04s. 
Wartości każdego z przebiegów  kroku dt:
 * a) 0.05 s
 * b) 0.01 s
 * c) 0.001 s
 * d) 0.0001 s
2. Wszystkie 4 przebiegi wyświetl na jednym wykresie, każdy w funkcji czasu.
Dla każdego wykresu użyj innego koloru oraz typu znacznika (np. `plot(...,...,'xr')`), nie używaj znacznika domyślnego funkcji `plot` (linii łączącej punkty).
3. Dodaj tytuł wykresu, opisy obu osi, legendę oraz siatkę.
4. Zwróć uwagę na którym wykresie *próbki sygnału* (wygenerowane punkty przebiegu) zaczynają układać się w przebieg sinusoidalny o częstotliwośi f = 50 Hz.
5. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.


### Ex3. Podstawy przetwarzania sygnałów. Aliasing.
1. Wykreśl przebieg czasowy (funkcję) napięcia sinusoidalnego o amplitudzie A = 325 V, częstotliwości f = 50 Hz i czasie trwania od 0 do _tend_ = 0.04s. 
Wartości przebiegu oblicz w chwilach czasowych odległych od siebie o dt = 0.001s. 
Przebiegi wykreśl w funkcji czasu używając znacznika `.` (np. `plot(...,...,'b.')`).
2. Wyskaluj wykres poleceniem `axis([0 tend -A A])`, dodaj siatkę.
3. wykreśl (na tym samym wykresie) wartości przebiegu z pkt. 1, ale obliczone w chwilach czasowych odległych od siebie o: 
 * a) dt = 0.005s, użyj znacznika `gx` (np. `plot(...,...,'gx')`)
 * b) dt = 0.0068s,  użyj znacznika `r+` (np. `plot(...,...,'r+')`)
 * c) dt = 0.02s,  użyj znacznika `ko` (np. `plot(...,...,'ko')`)
4. Zwróć uwagę na którym wykresie *próbki sygnału* ( wartości przebiegu obliczone w danych chwilach czasowych) przestają układać się w przebieg sinusoidalny o częstotliwośi f = 50 Hz.
5. Zapoznaj się z treścią _twierdzenia o próbkowaniu_. Który z przebiegów (o jakim dt) można uznać za _poprawnie spróbkowany_?
   Odpowiedź (poprawny/niepoprawny) zamieść w formie legendy wykresu. 
   Czy z samego rozmieszczenia _próbek_ sygnału możemy wnioskować o tym czy został on poprawnie spróbkowany? 
7. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.


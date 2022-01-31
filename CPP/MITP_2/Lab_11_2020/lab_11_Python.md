# Laboratorium 11 - Wprowadzenie do języka Python
*na podstawie Wykładu dr inż. Jarosława Bułata*: https://github.com/MiTPMaPT/MiTP_II_19_20/blob/master/wyklad/PI_II_05.pdf

## Instrukcje warunkowe

### Zadanie 01
Napisz program, który będzie przeliczał temperaturę w stopniach Celsjusza na temperaturę w stopniach Fahrenheita lub odwrotnie. Potraktuj, że użytkownik na wejściu podaje dane w postaci np. 21C lub 70F.
* Przypisz liczbę i rodzaj skali do osobnych zmiennych. Do elementów zmiennej typu string możesz odwoływać się tak samo jak w przypadku listy.
* Pamiętaj o odpowiednim rzutowaniu.
* Do przeliczania wykorzystaj następujący wzór: **T = (F - 32) * 5/9**, gdzie T to temperatura w st. Celsjusza, a F temparatura w st. Fahrenheita.

### Zadanie 02
Napisz program, który wczytuje dwie liczby całkowite reprezentujące numer dnia i numer miesiąca, a następnie zwraca nazwę pory roku dla podanych wartości.

## Pętle

### Zadanie 03
Przy użyciu pętli `for` i funkcji `range()` napisz program, który dla podanego słowa wypisze je w odwrotnej kolejności.

### Zadanie 04
Przy użyciu pętli `while` wypisz liczby z przedziału <100,150>, pomijając te, które są podzielne przez 5 i 7.
* Użyj instrukcji `continue`.

### Zadanie 05
Wypisz wszystkie liczby pierwsze z przedziału <2,10> wykorzystując instrukcję: `for ... else` lub `while ... else`.
* Użyj instrukcji `break` przy znalezieniu pierwszego dzielnika naturalnego innego niż 1 i dana liczba.
* W bloku `else` umieść informację o znalezieniu liczby pierwszej.

## Klasy

### Zadanie 06
1. Utwórz trzy klasy następujących obiektów: kwadrat, koło i trójkąt równoboczny.
1. Dodaj komponenty z informacjami potrzebnymi do obliczenia obwodów i pól figur.
1. Dodaj konstruktory dla poszczególnych klas, których argumentami będą wartości dla komponentów z punktu 2.
1. Dodaj metody wyświetlające obliczone obwody i pola figur.

## Wyjątki
Przykłady wyjątków:
- brak pliku
- odwołanie się do elementu spoza zakresu
- brak klucza w słowniku
- niepoprawny format danych
- odwołanie się do nieistniejącej zmiennej
- dzielenie przez zero

### Zadanie 07
Wybierz dwa typy wyjątków z powyższej listy i obsłuż je, korzystając z bloków: `try` i `except`.


## Pakiety i Moduły

### Zadanie 08
1. Wykorzystując wyniki z zadania 06 umieść każdą definicję utworzonej klasy w osobnym pliku, np. *kwadrat.py*, *kolo.py*, *trojkat.py*.
1. Utwórz nowy plik, np. *obliczenia.py*, w którym zaimportujesz moduły utworzone w poprzednim punkcie.
1. Sprawdź czy możesz utworzyć nowy obiekt i wyświetlić pole figury korzystając z odpowiedniej metody.
1. Następnie w katalogu bieżącym utwórz następujące podfoldery: **./figury/czworokaty**.
1. W obu utworzonych folderach utwórz pusty plik o nazwie: **\_\_init\_\_.py** (jest on niezbędny, aby katalogi były traktowane jako zawierające pakiety).
1. W folderze czworokaty  umiesc plik modułu: *kwadrat.py*.
1. Wróć do wcześniejszego katalogu bieżącego i utwórz w nim plik: *obliczenia2.py*.
1. Spróbuj zaimportować moduł *kwadrat* z utworzonego pakietu: `import figury.czworokaty.kwadrat as kw`
1. Czy udało Ci się utworzyć nowy obiekt Kwadrat i wyświetlić jego pole lub obwód ?

## Operacje na plikach

### Zadanie 09
1. Stwórz plik tekstowy zawierający dowolny tekst mający kilka linijek.
1. Napisz program, który policzy liczbę linijek w pliku.
1. Napisz kod, który wypisze na ekran z ilu słów składa się każda linijka.
1. Napisz program, który policzy liczbę samogłosek w każdej linijce.
1. Zmodyfikuj kod z poprzedniego punktu, tak aby wypisał każdą linijkę, gdzie samogłoski będą napisane dużą literą. Do tego celu użyj funkcji: `upper()` (str.upper())

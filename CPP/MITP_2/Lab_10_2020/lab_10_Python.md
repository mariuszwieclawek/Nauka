# Laboratorium 10 - Wprowadzenie do języka Python
*na podstawie Wykładu dr inż. Jarosława Bułata*: https://github.com/MiTPMaPT/MiTP_II_19_20/blob/master/wyklad/PI_II_04.pdf
*autor instrukcji: dr inż. dr n. prawn. Dawid Juszka*

## Podstawowe informacje:
* w Pythonie (prawie) wszystko jest obiektem, 
* podstawowe typy liczbowe nie są obiektami ale można po nich dziedziczyć,
* możliwe jest wielokrotne dziedziczenie,
* nie ma enkapsulacji (hermetyzacji), czyli nie da się ukrywać składowych w klasach - *wszystkie składowe są public*.
* nie ma znaków końca instrukcji (średniki w C/C++)
* nie ma klamerek {}
* blok kodu (pętla, warunek, funkcja/metoda) jest określony wcięciem
* nie da się napisać kodu źle sformatowanego - nie uruchomi się
* jedna linia - jedno wyrażenie
* dwukropek rozpoczyna "body" funkcji, pętli, warunku
* kod jest zwięzły, ale czytelny
* Python to język dynamicznie typowany
* nie ma deklaracji zmiennych - zmienna sama zostanie utowrzona podczas inicjalizacji, a jej typ zostanie wydedukowany

## Rozgrzewka

### Zadanie 00
Uruchom system Linux (np. Ubuntu). Sprawdź, która wersja języka Python jest zainstalowana.
W terminalu użyj komend i zaobserwuj wyniki: 
* `which python` - jaki jest wynik działania komendy? 
* `which python3` - jaki jest wynik działania komendy? 
* `python3 -V` - jaki jest wynik działania komendy?
* `python3` - otworzy się shell Pythona  (będziemy używać Pythona w wersji 3, a nie 2)
* sprawdź czy jest zainstalowany pycharm albo choćby program do tworzenia plików tekstowych (np. Notepad++)

### Zadanie 01
1. Napisz w notatniku program, który na ekranie wypisze "hello world!". Zapisz z rozszerzeniem .py
1. Uruchom program z konsoli używając interpretera w wersji 3.7 lub wyższej.
1. Zmodyfikuj plik tak, aby można było go uruchomić z konsoli jak zwykły skrypt 
  * dodaj shebang
  * zmień odpowiednio prawa dostępu do pliku (dodaj możliwość uruchamiania `x` - executable)

## Typy
### Zadanie 02 - w Pythonie wartości (a nie zmienne) posiadają typy
1. Sprawdź jaki typ mają zmienne (użyj funkcji `type(...)`):
`a=1`,
`b=1.02`,
`c=2+1j*3`,
`d=True`,
`e='abc'`.
2. Konwersja typów (automatyczna) - jaki typ ma `c` po wykonaniu działania `c = a + b`? Sprawdź.
3. Konwersja typów (jawana) - wykonaj `d = int(c)`. Wydrukuj `d`. Sprawdź typ `d`.
4. Konwersja na typ str, żeby wyświetlać obiekt jako tekst - wykonaj `s=str(b)`. Wydrukuj: `print(b)`.
5. Wykonaj dodawanie: `z='abc'+s` a następnie `print('text: '+str(c))` - zapamiętaj jak tworzy się tekst z wartościami zmiennych.
6. Wykonaj dodawanie `z = 'abc'+"123"`, sprawdź `print(z)`.
7. Sprawdź, że istnieje wbudowana kowersja złożonych typów. Przypisz `cpx = 2+1j*3` i wydrukuj `print(str(cpx)+' complex\n')`

### Zadanie 03 - Silnia!
Napisz program, który pyta użytkownika o liczbę (użyj metody `input`) a następnie wypisuje wynik silni dla tej liczby.

## Kolekcje
Możliwe sposoby grupowania danych w Pythonie:
* listy (nie są tak efektywne jak tablice w C/C++ ze względu na duży narzut pamięci),
* krotki (tuple),
* słownik (dict),
* tablice (array, NumPy)
* zbiory (set/frozonset)

### Zadanie 04 - lista
1. Utwórz listę nazw kolorów i wypisz na ekranie tylko pierwszy element (nazwę) z listy.
1. Sprawdź czy lista może jednocześnie zawierać różne typy.
1. Sprawdź liczbę elementów listy (`len(...)`).
1. Sprawdź czy dany element znajduje się na liście (`print(_X_ in _listname_)`)
1. Jednym poleceniem utwórz 100-elementową listę wypełnioną zerami i wyświetl na ekranie.
1. Połącz listę kolorów z listą nazw kolejnych cyfr.
1. Wcześniej utowrzoną listę tak zmodyfikuj, aby pierwszym elementem był tekst 'ziemia', a ostatnim elementem lista dni tygodnia. Wypisz listę.
1. Rozszerz listę o nazwę 'merkury' za pomocą funkcji `append`. 

### Zadanie 05 - Listy
Utwórz listę 50 elementów, w której następny element to suma dwóch poprzednich elementów podzielona przez ich różnicę. Pierwszy element to 1, drugi element to 2. Oblicz sumę i medianę tej listy. 

### Zadanie 06 - Wielokrotności
Napisz program, który wypisuje wszystkie liczby z przedziału 2000 do 3200, które wielokrotnością 7, ale nie są wielokrotnością 5.

### Zadanie 06 - Krotka
1. Utwórz krotkę zawierającą kolejne nazwy: "red", "green", "red".
1. Wypisz pierwszy element krotki, wpisz długość krotki, sprawdź ile nazw 'red' zawiera krotka.
1. Sprawdź jaki w krotce ma indeks nazwa 'red'. 
1. Rozszerz krotkę o nazwę 'blue', za pomocą funkcji `append`. Udało się?

### Zadanie 07 - Słownik
1. Utwórz słownik składający się z kilku par (np. nazwy państwa i jego stolicy). Jedną z par niech będzie {'Polska' : 'Warszawa'}
1. Dodaj do tego słownika parę składającą się z cyfry i jej nazwy (słownie). Udało się?
1. Dodaj do tego słownika parę {'Polska' : 'Krakow'}. Udało się? Dlaczego?
1. Zmodyfikuj parę {'Polska' : 'Warszawa'} tak, żeby była następująca: {'Polska' : 'Gniezno'}

### Zadanie 08 - Słownik dla liczb zespolonych
Napisz program, który dla podanej liczby zespolonej _n_ tworzy słownik zawierający pary (i, i*_i_) i wypisuje ten słownik. Sprawdź typy wszystkich wartości.

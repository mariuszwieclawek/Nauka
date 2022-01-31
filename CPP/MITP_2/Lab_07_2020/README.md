# Lab 07 

### Matlab. Wprowadzenie. Instrukcje warunkowe. Funkcje.
wykład do laboratorium:PI_II_01.pdf

### Ex0. Ustawienia i podstawowe informacje
Wprowadź następujące ustawienia interfesju środowiska Matlab:
1. Kofiguracja okien: **Home->Layout->Default**
2. Kofiguracja skrótów klawiaturowych do układu MS Windows: **Home->Preferences->Keyboard->Shortcuts->Active settings: Windows Default Set**
3. Komunikaty błędów kompilacji i wykonania oraz ostrzeżenia (warnings) są wypisywane w `Command window`.
4. Jeśli Matlab przestał reagować na próby wywoływania polecenia (lub całego skryptu) należy sprawdzić czy w lewym dolnym rogu okna głównego nie pojawił się jeden ze statusów (sprawdź co oznaczają):
 - `Busy` 
- `Continue entering statement` 
- `Paused`
5. Przerwanie wykonywania bieżącego polecenia:
- kliknięcie kursorem myszy w obszar `Command window`
- `Ctrl+C `

### Ex1. `Command window`. `Workspace`. Skrypty. Deklarowanie zmiennych. Komentarze. 
1. Utwórz na dysku swój katalog roboczy. Skopiuj do niego skrypt (`m-file`) `Ex_1.m`.
2. Po uruchomieniu Matlab-a, wejdź do utworzonego katalogu roboczego **Home->Browse for folder**   (pasek ze ścieżką do bieżącego folderu). Otwórz skrypt (`m-file`) `Ex_1.m`. 
3. Uruchamiaj kolejne linie kodu (zaznaczenie linii +`F9`). Obserwuj co pojawia się oknach  `Command window` i`Workspace`. Zwróć uwagę na typy zmiennych (okno `Workspace`).
4. Wywołaj (w `Command window`) kolejno polecenia: `whos`, `pwd`,`ls` oraz sprawdź działanie klawisza  `↑` (strzałka do góry).

### Ex2.  Operacje na wektorach i macierzach. 
1. Otwórz skrypt (`m-file`) `Ex_2.m`. 
2. Uruchamiaj kolejne linie kodu (zaznaczenie linii +`F9`). Obserwuj co pojawia się w oknach  `Command window` i`Workspace`. Zwróć uwagę na typy zmiennych (okno `Workspace`).

### Ex3.  Pętle. Instrukcje warunkowe.
1. Otwórz skrypt (`m-file`) `Ex_3.m`.
2. Uruchom cały skrypt (**Editor->Run**,`F5`) lub jego kolejne sekcje (**Editor->Run and Advance**). Przeanalizuj kod i jego działanie.
3. Nastpnie odkomentuj linie 48-58 i ponownie uruchom skrypt. Dlaczego wystąpi bład przy pętli `while` (jaka jest treść komunikatu wyświetlanego w w `Command window`)? 
4. Korzystając z dokumentacji (w `Command window` wpisz `doc while`lub `help while` ) usuń błędy i zmodyfikuj kod tak, aby rezultat wykonania pętli `while`był identyczny jak wykonania pętli`for`.
5. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.

### Ex4.  Funkcje. 
Funkcje w środowisku `MATLAB` mogą zawierać wiele ( w tym 0) argumentów, mogą również zwracać wiele wartości (co zasadniczo odróżnia je od funkcji np. w języku `C/C++`).
1. Utwórz nowy plik komendą **file->new->M-file**. Następnie do tego pliku wpisz instrukcje:

   ```
    function [lista arg. wyjściowych] = nazwa funkcji (lista arg. wyjściowych)
   ```

2. Tworzona funkcja powinna:
- przyjmować 2 argumenty: macierz **A**, macierz **B**, obie tych samych rozmiarów
- zwracać 4 wartości: sumę, rónicę oraz wyznaczniki macierzy **A** i **B**.
3. Uruchom funkcję w oknie `Command Window` oraz z poziomu skryptu (**Editor->Run**,`F5`) .
4. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.


### Ex5.  Funkcje matematyczne. `plot()`, `title()`, opisy osi, legenda.
Utwórz nowy skrypt, w którym:
1. Oblicz wartości wielomianów/funkcji:

     *y1(x) = x^2 + 1*     
     *y2(x) = x^3 + x^2 + x + 1*  
     
    dla *x ∈* <−5, 5>,
    
   Przyjmij krok pomiędzy kolejnymi punktami dziedziny równy 0.01.
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
3. Zmodyfikuj kod tak, aby opisy osi i tytuł odpowiadały zawartości wykresu. Dodaj do wykresu legendę (funkcja `legend()`).
4. W punkcie 2 zostały wykreślone obliczone wartości pierwszego z wielomianów (z punktu 1) w funkcji **indeksów** elementów wektora dziedziny. W oparciu o dokumentację funkcji `plot()` (w oknie `Command Window` wpisz `doc plot`) w nowej figurze (polecenie `figure(3);`) wykreśl (na jednym wykresie) obliczone wartości obu wielomianów (z punktu 1) w funkcji **dziedziny** *x*.
5. Następnie zmodyfikowany kod umieść **W SWOJEJ GAŁĘZI** w repozytorium zdalnym.
    







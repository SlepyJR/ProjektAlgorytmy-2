#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <array>
#include <fstream>
#include <string>


int pobieranie(const char* nazwa_pliku,int *tab, int rz)
// Funkcja pobierajaca dane z pliku
{
    std::fstream ifs(nazwa_pliku, std::ios::in);
    if(!ifs.good())
    {
        return 0;
    }
    int licznik = 0;
    for(std::string line; std::getline(ifs,line,'|');)
    {
        if(licznik>=rz)
        {
            return licznik;
        }
        tab[licznik++]= atoi(line.c_str());
    }
    return licznik;
}
bool zapis(const char* nazwa_pliku,int *tab, int rz)
// Funkcja zapisujaca dane do pliku
{
    std::fstream ofs(nazwa_pliku, std::ios::out);
    if(!ofs.good())
    {
        return false;
    }

    for(int i=0;i<rz;i++)
    {
        ofs << tab[i] << '|';

    }
    return true;

}

void combSort(int *tab, int rz)
{
   int gap = rz, tmp;
   bool swapped = true;
   while (gap > 1 || swapped)
    {
        // jeśli gap = 1 i nie dokonano zamiany - wyjście z pętli
      gap = gap * 10 / 13;
      if(gap==0)
            gap=1;
      swapped = false;
      for ( int i = 0; i + gap < rz; ++i )
      {
          // wykonuj od 0 do ostatniego elementu tablicy
         if ( tab[i + gap] < tab[i] )
            {
            // porównanie elementów odległych o rozpiętość
            tmp = tab[i];
            // zamiana elementów
            tab[i] = tab[i + gap];
            tab[i + gap] = tmp;
            swapped = true;
           }
      }
   }
}
void selection_sort(int *tab,int rz)
//n - ilość elementów do posortowania
{
int mn_index;
//zmienna pomocnicza przechowująca indeks komórki
//z minimalną wartością
  for(int i=0;i<rz-1;i++)
  {
  	mn_index = i;
    for(int j=i+1;j<rz;j++)
    //pętla wyszukuje najmniejszy
    //element w podzbiorze nieposortowanym
    if(tab[j]<tab[mn_index])
      mn_index = j;

    //zamiana elementu najmniejszego
    //w podzbiorze z pierwszą pozycją nieposortowaną
	std::swap(tab[i], tab[mn_index]);
  }
}

void testy(int *tab, int rz)
{
    if(rz <= 0)
	{
		std::cout << "Tablica nie moze miec wartosci mniejszej od 0 lub rownej 0"<<std::endl;
	}
	else{
            std::cout << "\n";
    std::cout << "Algorytm sortowania grzebieniowego:";
	std::cout << "\n";
	std::cout << "|";
	for (int i = 0; i < rz; i++)
	{
		std::cout << tab[i] << "|";
		// Pêtla wypisuj¹ca wartoœci tabeli "tab"
	}
    int tab2[rz];
        for (int i=0; i<rz; i++)
            {
                tab2[i] = tab[i];
            }
	auto begin = std::chrono::high_resolution_clock::now();
	// Rozpoczêcie pomiaru czasu dzialania algorytmu
    combSort(tab,rz);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::cout << "\n";
    std::cout << "|";
    for (int i = 0; i < rz; i++)
	{
		std::cout << tab[i] << "|";
		// Pêtla wypisuj¹ca wartoœci wektora "tab2"
	}
	std::cout <<"\n";

	std::cout << "Czas algorytmu:\n";
	// Wyœwietlanie czasu dzialania algorytmu
    std::cout << (" %.3f seconds.\n", elapsed.count() * 1e-9);
    std::cout << "\n";
    std::cout << "Algorytm sortowania przez wstawianie:";
    std::cout << "\n";
    std::cout << "|";
    for (int i = 0; i < rz; i++)
	{
		std::cout << tab2[i] << "|";
		// Pêtla wypisuj¹ca  wartoœci wektora "tablica"
	}

	auto start = std::chrono::high_resolution_clock::now();
	selection_sort(tab2,rz);
	auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "\n";
    std::cout << "|";
	for (int i = 0; i < rz; i++)
	{
		std::cout << tab2[i] << "|";
		// Pêtla wypisujaca wartoœci tablicy "tab2"
	}

	std::cout << "\n";
	std::cout << "Czas algorytmu:\n";
	// Wyœwietlanie czasu dzialania algorytmu
    std::cout << (" %.3f seconds.\n", duration.count() * 1e-9);
    std::cout << "\n";

}

}

int tworzenie(int *tab, int rz)
{
    if(rz <= 0)
	{
		std::cout << "Tablica nie moze miec ";
		std::cout << "wartosci mniejszej od 0 lub rownej 0"<<std::endl;
		return 0;
	}
	else
    {
        for(int i=0;i<rz;i++)
            // Utworzenie pêtli, która kazdemu indeksowi
            //tablicy przypisuje losowe wartosci od 0 do 100;
        {
            tab[i] = rand() %1000;
        }
    }
    return rz;
}

int main()
{
    srand((unsigned int)time(NULL));
    //Funkcja resetujaca losowania liczb za ka¿dym uruchomianiem programu.
    int rz;
	std::cout << "Wprowadz zadany rozmiar tablicy z liczbami: \n" <<std::endl;
	std::cin >> rz;
	int tab[rz];
	int tab2[rz];
	int rozmiar2 = pobieranie("tabliczka2.txt", tab2, rz);
    int rozmiar = pobieranie("tabliczka.txt", tab, rz);
    if(rozmiar==0)
    {
        std::cout << "Nie znaleziono pliku tabliczka.txt. ";
        std::cout << "Generowane sa losowe wartosci.";
        rozmiar = tworzenie(tab,rz);
    }
    if(rozmiar>0)
    {
        testy(tab,rozmiar);
        zapis("tabliczka_zapis.txt",tab,rozmiar);
    }
    else
    {
        std::cout <<"Blad" ;
    }
    return 0;
}






/*Pseudokod funkcji sortującej grzebieniowo

Funkcja void combSort()
stwórz zmienną int gap = rz, tmp;
stwórz bool swapped = true;

dopóki gap > 1 i swapped
{
    gap = gap * 10/13;
    jeśli gap ==0
        zamian gap na 1
    swapped = false;
    dla (int i = 0; i + gap <rz; ++i)
    {
        jeśli (tab[i +gap] < tab[i])
        stwórz zmienną tmp = tab[i];

        tab[i] = tab[i + gap];
        tab[i + gap] = tmp;
        swapped = true;
    }
}
*/



/*Funkcja selection_sort Wprowadz int *tab, int rz
{
	wprowadz int mn_index;

	dla int i = 0; i<rz-1;i++
		{
			przypisz i do mn_index;
			dla int j=i+1;j<rz;j++

			jesli tab[j]>tab[mn_index
				przypisz j do mn_index
		}
		zamien najmniejszy element tab[i],
		z  tab[mn_index]
*/









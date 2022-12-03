#include <iostream>
#include <vector>
#include <ctime>
void combSort(int *tab, int rz)
{
   int gap = rz, tmp;
   bool swapped = true;
   while (gap > 1 || swapped){
        // jeśli gap = 1 i nie dokonano zamiany - wyjście z pętli
      gap = gap * 10 / 13;
      if(gap==0)
            gap=1;
      swapped = false;
      for ( int i = 0; i + gap < rz; ++i ) {
          // wykonuj od 0 do ostatniego elementu tablicy
         if ( tab[i + gap] < tab[i] ) {
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

void tworzenie(int rz)
{
    if(rz <= 0)
	{
		std::cout << "Tablica nie moze miec wartosci mniejszej od 0 lub rownej 0"<<std::endl;

	}
	else{

	srand((unsigned int)time(NULL));
	//Funkcja resetujaca losowania liczb za ka¿dym uruchomianiem programu.

	int tab[rz];
	// Utworzenie tablicy


	for(int i=0;i<rz;i++)
        // Utworzenie pêtli, która kazdemu indeksowi
        //tablicy przypisuje losowe wartosci od 0 do 100;
	{
		tab[i] = rand() %100;
	}
	for (int i = 0; i < rz; i++)
	{
		std::cout << tab[i] << "|";
		// Pêtla wypisuj¹ca indeksy oraz wartoœci wektora "tablica"
	}
	combSort(tab,rz);
	std::cout <<"\n";
	for (int i = 0; i < rz; i++)
	{
		std::cout << tab[i] << "|";
		// Pêtla wypisuj¹ca indeksy oraz wartoœci wektora "tablica"
	}
}
}

int main()
{

    int rz;
	std::cout << "Wprowadz zadany rozmiar tablicy z liczbami: \n" <<std::endl;
	std::cin >> rz;
    tworzenie(rz);

    return 0;
}

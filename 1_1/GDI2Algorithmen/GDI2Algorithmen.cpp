// GDI2Algorithmen.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>

//Prototypen
void DasSiebDesEratostenes(int * pZahlenFeld, int maximalWert);
void AusgabeIntFeld(int * pIntFeld, int maxwert);


int main()
{
	int maxwert = 130;
	int * zahlenReihe = new int[maxwert];
	int * primzahlen = new int[maxwert];
	int zahlenWert = 2;

	//belegen
	zahlenReihe[0] = 0;
	for (int i = 1; i < 130; i++)
	{
		primzahlen[i] = 0;
		zahlenReihe[i] = zahlenWert;
		zahlenWert++;
	}

	AusgabeIntFeld(zahlenReihe, maxwert);
	
	std::cout << std::endl << "Primzahlen: " << std::endl;

	DasSiebDesEratostenes(zahlenReihe, maxwert);

	//freigeben
	delete[]zahlenReihe;

	//konsole aufhalten
	int k;
	std::cin >> k;
	return 0;
}


void DasSiebDesEratostenes(int * pZahlenFeld, int maximalWert)
{
	for (int i = 1; i < maximalWert; i++) 
	{
		//Wenn nicht mit 0 markiert -> Primzahl
		if(pZahlenFeld[i]!=0)
			//Ab der besagten Primzahl rest durchlaufen
			for (int j = 2*i; j < maximalWert; j++)
			{
				//Wenn nicht markiert
				if (pZahlenFeld[j]!=0)
					//Und wenn vielfaches von der ersten Primzahl, dann mit 0 markieren
					if((pZahlenFeld[j] % pZahlenFeld[i]) == 0)
					pZahlenFeld[j] = 0;
			}
		//alle nicht markierten zahlen zurückgeben
		if (pZahlenFeld[i] != 0)
			std::cout << std::setw(4) << pZahlenFeld[i];
	}
}

void AusgabeIntFeld(int * pIntFeld, int maxwert) 
{
	for (int i = 0; i < maxwert; i++)
	{
		std::cout << std::setw(4)<< pIntFeld[i];
		if (i % 9 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}




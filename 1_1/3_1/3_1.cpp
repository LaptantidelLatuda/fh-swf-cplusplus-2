/*
* File:   3_1.cpp
* Author: Tobias Steppan
* Description:	Lösung zur Aufgabe: 3.1. Einfach verkettete Liste aus statischem Element
* Created on 06. April 2018, 16:53
*/

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


struct Element {
	long key; //Schluessel des Elements
	long info; //verwaltete Information
	struct Element *next; //Zeiger auf nächstes Element
};

int main()
{
	//Zwei Listenzeiger
	Element * L;
	Element * cursor;

	//Vier Elemente
	Element x1 = { 1, 11 };
	Element x2 = { 2, 22 };
	Element x3 = { 3, 33 };
	Element x4 = { 4, 44 };

	//Pointer auf die nächsten elemente
	Element * p_x2 = &x2;
	Element * p_x3 = &x3;
	Element * p_x4 = &x4;

	//Verketten
	x1.next = p_x2;
	x2.next = p_x3;
	x3.next = p_x4;
	x4.next = nullptr;

	//Zeiger cursor auf Listenanfang
	L = &x1;
	cursor = L;

	bool endOfList = false;

	//Element mit schlüsselwert 3 suchen
	while (cursor->key != 1)
	{
		if (cursor->next == nullptr)
		{
			endOfList = true;
			break;
		}
		cursor = cursor->next;
	}

	//Ausgabe
	if (endOfList)
		std::cout << "Ende der Liste erreicht ohne den Wert zu finden";
	else
	{
		std::cout << "Listenelemente geunfden : " << cursor << std::endl << std::endl;
		std::cout << std::setw(12) << "key =" << cursor->key << std::endl;
		std::cout << std::setw(12) << "info =" << cursor->info << std::endl;
		std::cout << std::setw(12) << "next =" << cursor->next << std::endl;
	}

	//Konsole offen halten
	int i = 0;
	std::cin >> i;

	return 0;
}


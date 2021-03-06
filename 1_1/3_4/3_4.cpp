/*
* File:   3_3.cpp
* Author: Tobias Steppan
* Description:	Lösung zur Aufgabe: 3.4 Personenbeschreibung in einer Liste
* Created on 06. April 2018, 16:53
*/

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct mitarbeiter {
	string identnummer;
	string nachname;
	string vorname;
	string abteilung;
	unsigned int durchwahl;
	mitarbeiter *next;
};

mitarbeiter *ma = 0;
mitarbeiter *cursor = 0;

int main()
{
	string inputFilePath = "personen.dat";
	ifstream ifs;
	ifs.open(inputFilePath);
	if (!ifs)
	{
		cerr << "\nError: could not load file";
	}

	int i = 0;

	//Einlesen und Ausgabe
	while (!ifs.eof())
	{
		//neuer struct
		mitarbeiter *maNeu = new mitarbeiter;

		//pointer auf erstes element setzen
		if (ma == 0)
		{
			ma = maNeu;
			cursor = maNeu;
		}

		//cursor auf nächstes element richten
		//cursor = cursor+sizeof(mitarbeiter);

		//einlesen
		ifs >> maNeu->identnummer;
		ifs >> maNeu->nachname;
		ifs >> maNeu->vorname;
		ifs >> maNeu->abteilung;
		ifs >> maNeu->durchwahl;
		maNeu->next = cursor;

		//wenn letzter datensatz nullpointer setzen
		if (ifs.eof())
			maNeu->next = nullptr;
	}

	ifs.close();

	//Cursor auf listenanfang
	cursor = ma;

	bool endOfList = false;

	//Element mit schlüsselwert 3 suchen
	while (cursor->durchwahl != 4731)
	{
		if (cursor->next == nullptr)
		{
			endOfList = true;
			break;
		}
		cursor = cursor->next;
	}

	if (endOfList)
		cout << "Ende der Liste erreicht" << endl;
	cout << "Datensatz: " << endl;
	cout << setw(9) << ma[i].identnummer;
	cout << setw(12) << left << ma[i].nachname << "\t";
	cout << setw(12) << left << ma[i].vorname << "\t";
	cout << setw(5) << ma[i].abteilung << ma[i].durchwahl << endl;


	//Konsole offen halten
	int j = 0;
	cin >> i;

	return 0;
}


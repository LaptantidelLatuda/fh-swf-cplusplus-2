/*
* File:   3_3.cpp
* Author: Tobias Steppan
* Description:	Lösung zur Aufgabe: 3.3 Personenbeschreibung als Struktur
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
};

const unsigned int MitarbeiterMax = 1000;
mitarbeiter ma[MitarbeiterMax];



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
	while (ifs >> ma[i].identnummer >> ma[i].nachname >> ma[i].vorname >> ma[i].abteilung >> ma[i].durchwahl)
	{
		cout << setw(9) << ma[i].identnummer;
		cout << setw(12) << left << ma[i].nachname << "\t";
		cout << setw(12) << left << ma[i].vorname << "\t";
		cout << setw(5) << ma[i].abteilung << ma[i].durchwahl << endl;
	}

	ifs.close();

	//Konsole offen halten
	int j = 0;
	cin >> i;

	return 0;
}


/*
* File:   3_2.cpp
* Author: Tobias Steppan
* Description:	Lösung zur Aufgabe: 3.2: Rohdatei aus einer Datei einlesen
* Created on 06. April 2018, 16:53
*/

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

string identnummer;
string nachname;
string vorname;
string abteilung;
unsigned int durchwahl;

int main()
{
	string inputFilePath = "personen.dat";
	ifstream ifs;
	ifs.open(inputFilePath);
	if (!ifs) 
	{
		cerr << "\nError: could not load file";
	}

	//Einlesen und Ausgabe
	while (ifs >> identnummer >> nachname >> vorname >> abteilung >> durchwahl)
	{
		cout << setw(9) << identnummer;
		cout << setw(12) << left << nachname << "\t";
		cout << setw(12) << left << vorname << "\t";
		cout << setw(5) << abteilung << durchwahl << endl;
	}

	ifs.close();

	//Konsole offen halten
	int i = 0;
	cin >> i;

	return 0;
}


/*
* File:   2_1.cpp
* Author: Tobias Steppan
* Description:	Lösung zur Aufgabe: 2.1. Tha Game of Life

* Created on 27. Febrauar 2018, 09:51
*/

//Includes
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>

//benötigt für thread sleep
#include <chrono>
#include <thread>

//using
using namespace std;

//typedef
typedef unsigned int uint;

//Prototypen
void zufallsbelegung(int **feld, uint hoehe, uint breite);
uint next_generation(int **feld1, int **feld2, uint breite, uint hoehe);
void print_feld(int **feld, uint hoehe, uint breite);
int **new_int_matrix(int rows, int columns);
void delete_int_matrix(int **m);

//Eigene Prototypen
int ReadUserInput(int maxMap, int minMap);
void AutomaticGameOfLife(int **feld1, int **feld2, uint hoehe, uint breite, uint systemWait);
void GameOfLife(int **feld1, int **feld2, uint hoehe, uint breite);

//Variablen
int spielfeldgroesse = 30;

int main()
{
	//Eingabe und Überprüfung. Zwei addierenm, da das zu erzeugende Array einen Rand aus Nullen bekommen soll.
	spielfeldgroesse = ReadUserInput(100, 30) + 2;

	//Zwei Felder erstellen
	int **feld1 = new_int_matrix(spielfeldgroesse, spielfeldgroesse);
	int **feld2 = new_int_matrix(spielfeldgroesse, spielfeldgroesse);

	//Initialisiere feld1 mit zufallszahlen - erste generation des game of life
	zufallsbelegung(feld1, spielfeldgroesse, spielfeldgroesse);

	//Game of Life Automatisch ausführen(sieht gut aus entspricht nicht der aufgabe)
	AutomaticGameOfLife(feld1, feld2, spielfeldgroesse, spielfeldgroesse, 250);

	//Aufgaben konformes Game of life
	//GameOfLife(feld1, feld2, spielfeldgroesse, spielfeldgroesse);


	//Felder freigeben
	delete_int_matrix(feld1);
	delete_int_matrix(feld2);

	//Ausgabe offen halten
	int test = 0;
	cin >> test;

	return 0;
}

/*
Beschreibung:	Berechnung der nächsten Generation des "Game of Life"
@feld1 vorläufergenerationen, am ende der funktion gleichzeitig nachfolgegeneration
@feld2 array in dem die nächste generation aufgebaut wird
@breite breite der Spielfeldmatrix
@hoehe hoehe der Spielfeldmatrix
@return Anzahl der lebenden Zellen
*/
uint next_generation(int **feld1, int **feld2, uint breite, uint hoehe)
{
	int populationsGroesse = 0, anzahlDerNachbarn = 0;
	//Iterationsvariablen
	int i, j;


	//nur innere plätze besetzten
	for (i = 1; i < (breite - 1); i++)
	{
		for (j = 1; j < (hoehe - 1); j++)
		{
			//Anzahl der Nachbarn ermitteln
			anzahlDerNachbarn = feld1[i - 1][j] + feld1[i + 1][j] + feld1[i][j - 1] + feld1[i][j + 1] +
				feld1[i - 1][j - 1] + feld1[i + 1][j + 1] + feld1[i - 1][j + 1] + feld1[i + 1][j - 1];

			//Populationsgroesse bestimmen
			if (feld1[i][j] == 1)
				populationsGroesse++;

			//Regel 1 Eine tote Zelle mit genu der Nachbarn wird in der nächsten Generation neu geboren
			if (feld1[i][j] == 0 && (anzahlDerNachbarn == 3))
				feld2[i][j] = 1;

			//Regel 2 Eine lebende Zelle mit weniger als zwei Nachbarn stirbt in der folgenden Generation an Verinsamung
			else if (feld1[i][j] == 1 && (anzahlDerNachbarn < 2))
				feld2[i][j] = 0;

			//Regel 3 Eine lebende Zelle mit zwei oder drei Nachgbarn bleibt in der folgenden Generation am Leben
			else if (feld1[i][j] == 1 && ((anzahlDerNachbarn == 3) || (anzahlDerNachbarn == 2)))
				feld2[i][j] = 1;

			//Regel 4 Eine lebende Zelle mit mehr als drei Nachbarn stirbt in der folgenden Generation an Überbevölkerung
			else if (feld1[i][j] == 1 && (anzahlDerNachbarn > 3))
				feld2[i][j] = 0;

			//Default Regel: Alle Zellen auf die keine Regel anzuwenden ist, werden unverändert in die nächste Generation übernommen
			else
				feld2[i][j] = feld1[i][j];
		}
	}

	//feld 1 mit feld 2 überschreiben
	for (i = 0; i < breite; i++)
	{
		for (j = 0; j < hoehe; j++)
		{
			feld1[i][j] = feld2[i][j];
		}
	}
	return populationsGroesse;
}

/*
Beschreibung:	Ausgabe eine zweidimensionalen Arrays das mit Nullen und Einsen belegt ist.
				Nullen werden mit einem Leerzeichen ausgegeben, Einsen mit einem '#'
				Der äußere Rand des Arrays wird nicht ausgegeben.
@feld auszugebende Spielfeldmatrix
@hoehe hoehe der Spielfeldmatrix
@breite breite der Spielfeldmatrix
*/
void print_feld(int **feld, uint hoehe, uint breite)
{
	for (int i = 1; i < (hoehe - 1); i++)
	{
		for (int j = 1; j < (breite - 1); j++)
		{
			if (feld[i][j] == 0)
				cout << "  ";
			else
				cout << "# ";
		}
		cout << endl;
	}
}

/**
* Allokiere eine neue Pixelmatrix mit der Größe rows*columns
* @param rows reihen
* @param columns spalten
* @return pointer auf array von pointern die auf zeilen der pixelmatrix zeigen
*/
int **new_int_matrix(int rows, int columns)
{
	size_t i;
	int **m;

	//pointer array
	m = new int *[rows];

	//Daten Array
	*m = new int[rows * columns];

	for (i = 1; i < rows; i++)
		m[i] = m[i - 1] + columns;
	return m;
}

/**
* Gibt allkokierten Speicher eines 2d Arrays frei
* m: pointer auf arraypointer auf zeilen des freizugebenden arrays
*/
void delete_int_matrix(int **m)
{
	//lösche daten array
	delete[] * m;

	//lösche pointer array
	delete[] m;
}

/*
Beschreibung: Initialisiert äußere Felder eine Spielfeldmatrix mit 0 und die inneren Felder zufällig mit 0 und 1
@feld zu belegende Spielfeldmatrix
@hoehe hoehe der Spielfeldmatrix
@breite breite der Spielfeldmatrix
*/
void zufallsbelegung(int **feld, uint hoehe, uint breite)
{
	for (int i = 0; i < hoehe; i++)
	{
		for (int j = 0; j < breite; j++)
		{
			//Rand mit Nullen initialisieren
			if (i == 0 || i == hoehe || j == 0 || j == breite)
				feld[i][j] = 0;

			//Zufallszahlen
			if (rand() % 2 == 0)
				feld[i][j] = 0;
			else
				feld[i][j] = 1;
		}
	}
}

/*
Beschreibung:	Fordert den Nutzer so lange auf eine Zahl einzugeben bis sie den Kriterien:
				- liegt zwischen maxMap und minMap
				- ist eine Ziffer
				entspricht
				Setzt auch den Seed für die Zufallsberechnung nach der Eingabe -> "zufälliger"
@maxMap maximale einzulesende Zahl
@minMap minimale einzulesende Zahl
@return Überprüfte Eingabe
*/
int ReadUserInput(int maxMap, int minMap)
{
	int result = 0;
	string readInput;

	//Aufforderung zur Eingabe
	cout << "Bitte geben Sie eine Spielfeldgroesse zwischen " << minMap << " und " << maxMap << " ein." << endl;
	while (!result)
	{
		bool containsOnlyDigits = true;

		//Einlesen
		cin >> readInput;

		//Überprüfung ob Ziffer und zwischen Grenzen
		for (int i = 0; i < readInput.length(); i++)
		{
			if (!isdigit(readInput[i]))
			{
				containsOnlyDigits = false;
				break;
			}
		}

		//Überprüfung ob Zahl zwischen Grenzen liegt
		if (containsOnlyDigits)
			if (stoi(readInput) >= minMap && stoi(readInput) <= maxMap)
				result = stoi(readInput);

		if (!result)
			cout << "Bitte nur Zahlen (0-9) eingeben" << endl;
	}

	//Zufallsgenerator initialisieren um unterschiedliche random folgen zu erhalten
	srand((unsigned)time(NULL));

	return result;
}

/*
Beschreibung:	Erweiterung zur Aufgabenstellung. Führt das Game of Life automatisch auf ohne Benutzereingabe.

@feld1 vorläufergeneration - wird am ende der funktion mit nachfolgegeneration überschrieben
@feld2 nachfolgergeneration
@hoehe hoehe des arrays
@breite breite des arrays
@systemWait zeit in millisekunde, die zwischen den generationen gewartet wird
*/
void AutomaticGameOfLife(int **feld1, int **feld2, uint hoehe, uint breite, uint systemWait)
{
	int generation = 0;
	int lebendeZellen = 0;

	while (true)
	{
		//Konsole löschen
		system("cls");

		//Ausgabe
		print_feld(feld1, hoehe, breite);

		cout << endl << endl << "Generation: " << generation << " Lebende Zellen: " << lebendeZellen << " Spielfeldgroesse: [" << hoehe - 2 << "][" << breite - 2 << "]";

		//System 1000ms warten
		std::this_thread::sleep_for(std::chrono::milliseconds(systemWait));

		//nächste Generation erzeugen
		lebendeZellen = next_generation(feld1, feld2, hoehe, breite);

		generation++;
	}
}

/*
Beschreibung:	Der Aufgabenstellung entsprechnde Ablauf des Game of Life

@feld1 vorläufergeneration - wird am ende der funktion mit nachfolgegeneration überschrieben
@feld2 nachfolgergeneration
@hoehe hoehe des arrays
@breite breite des arrays
*/
void GameOfLife(int **feld1, int **feld2, uint hoehe, uint breite)
{
	int generation = 0;
	int lebendeZellen = 0;
	char input;

	//wird abgebrochen wenn ein q eingelesen wird
	while (true)
	{
		lebendeZellen = next_generation(feld1, feld2, hoehe, breite);
		generation++;

		//Konsole löschen
		system("cls");

		//Ausgabe
		print_feld(feld1, hoehe, breite);

		cout << endl << endl << "Generation: " << generation << " Lebende Zellen: " << lebendeZellen << " Spielfeldgroesse: [" << hoehe - 2 << "][" << breite - 2 << "] Q druecken zum abbrechen";

		cin >> input;
		if (input == 'q' || input == 'Q')
			break;
	}
}
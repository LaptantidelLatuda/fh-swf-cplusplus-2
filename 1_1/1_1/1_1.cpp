/*
* File:   1_1.cpp
* Author: Tobias Steppan
* Description: Lösung zur Aufgabe: 1.1. Bildverarbeitung 3 Verwendung von Strukturen
* Created on 27. Febrauar 2018, 09:51
*/

//Includes
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>

//using
using namespace std;

//Typdefinitionen
typedef unsigned char Pixel;

//Datentyp
struct pgm_bild
{
	char magic[2]; //Bildtyp
	int nx; //Zeilenzahl
	int ny; //Spaltenzahl
	int graumax; //maximaler Grauwert
	Pixel **bild; //Bildmatrix
};

//Prototypen
void bild_lesen(pgm_bild *bild, string ifs_file_name);
void bild_schreiben(pgm_bild *bild, string ofs_file_name);
void delete_pixel_matrix(Pixel **m);
Pixel** new_pixel_matrix(size_t rows, size_t columns);
void glaetten(pgm_bild *bild1, pgm_bild *bild2);
void invertieren(pgm_bild *bild1, pgm_bild *bild2);
void kantenbildung(pgm_bild *bild1, pgm_bild *bild2);
void kopiere_bildkopf(pgm_bild *bild1, pgm_bild *bild2);
void schaerfen(pgm_bild *bild1, pgm_bild *bild2);

int main(int argc, char** argv)
{
	//neuer struct pgm_bild
	pgm_bild * bild1 = new pgm_bild;
	pgm_bild * bild2 = new pgm_bild;

	bild_lesen(bild1, "dreifach.pgm");

	//neues Array für die zu bearbeitende Datei erstellen
	bild2->bild = new_pixel_matrix(bild1->nx, bild1->ny);

	//pgm header Informationen kopieren
	kopiere_bildkopf(bild1, bild2);

	////Aufforderung zur Eingabe
	cout << "Auswahl der Funktion:" << endl << "g Glättung" << endl << "i Invertierung" << endl;
	cout << "k Kantenbildung" << endl << "s Schärfung" << endl << "e ENDE" << endl;

	//Engabevariable
	char inputChar;
	cin >> inputChar;

	//Eingabemenü
	switch (inputChar)
	{
	case 'i': invertieren(bild1, bild2);
		break;
	case 'g': glaetten(bild1, bild2);
		break;
	case 'k': kantenbildung(bild1, bild2);
		break;
	case 's': schaerfen(bild1, bild2);
		break;
	case 'e': exit(0);
	}

	bild_schreiben(bild2, "dreifach.out.pgm");

	/*speicher freigeben*/
	delete_pixel_matrix(bild1->bild);
	delete_pixel_matrix(bild2->bild);

	return 0;
}

/**
* Liest ein pgm Bild ein und speichert es in dem struct ab auf den bild zeigt
* bild: pointer auf struct in den gespeichert wird
* ifs_file_name: dateiname des einzulesenden pgm bilds
*/
void bild_lesen(pgm_bild *bild, string ifs_file_name)
{
	//ifstream Objekt erstellen
	ifstream eingabeDatei;

	//Datei öffnen
	eingabeDatei.open(ifs_file_name);

	//Abfragen ob eingabeDatei geöffnet werden konnte
	if (!eingabeDatei)
	{
		cerr << endl << "Error: failed to open input file ! " << endl;
		exit(1);
	}

	//Einzulesendes Element
	string element;

	//Array dynamisch allokieren und mit Nullpointer initialisieren.
	//Sonst ist die Zuweisung später nicht möglich.
	Pixel **eingabeFeld = nullptr;

	//ElementZähler ersten 4 elemente abziehen
	int elementCounter = -3;

	int i = 0, j = 0, maxZeilen = 1000;

	//eingabeDatei einlesen
	while (eingabeDatei >> element)
	{

		//Array füllen nach dem header
		if (elementCounter > 0)
		{
			eingabeFeld[i][j] = stoi(element);
			j++;
			//Nach x Zeilen in nächste Spalte springen
			if (j == bild->ny)
			{
				i++;
				j = 0;
			}
		}
		else
		{
			//Ausgabe
			cout << element;

			//Kodierung überprüfen
			if (elementCounter == -3)
			{
				//Kodierung in Struct übernehmen
				bild->magic[0] = element[0];
				bild->magic[1] = element[1];
				if (element != "P2")
				{
					cout << "Falsche Kodierung";
					break;
				}
				//newline nach kodierung
				cout << endl;
			}
			//Zeilenanzahl lesen und neues Feld allokieren
			if (elementCounter == -1)
			{
				cout << endl;
				bild->nx = stoi(element);

				//sobald zeilen und spalten infos gelesen wurden wird ein neues feld dynamisch allokiert
				eingabeFeld = new_pixel_matrix(bild->nx, bild->ny);
			}

			//Spaltenanzahl lesen und überprüfen
			if (elementCounter == -2)
			{
				cout << " ";
				bild->ny = stoi(element);
			}
			//nach Element graustufen nächste zeile
			if (elementCounter == 0)
			{
				bild->graumax = stoi(element);
				cout << endl;
			}
		}
		elementCounter++;
	}
	//Stream schließen
	eingabeDatei.close();

	//Array an Struct übergeben
	bild->bild = eingabeFeld;

	//eingabeFeld speicher freigeben
	/*delete_pixel_matrix(eingabeFeld);*/
}

/*
Schreibt alle informationen des structs auf den bild zeigt in eine datei mit dem namen ofs_file_name
bild: pointer auf struct mit zu speichernden informationen
ofs_file_name: name der datei die erstellt werden soll
*/
void bild_schreiben(pgm_bild *bild, string ofs_file_name)
{
	//ofstream Objekt erstelln
	ofstream ausgabeDatei;

	//Datei öffnen
	ausgabeDatei.open(ofs_file_name);

	//Abfrage ob ausgabeDateien geöffnet werden können
	if (!ausgabeDatei)
	{
		cerr << endl << "Error: failt to open output file! " << endl;
		exit(2);
	}

	//Header in AusgabeDatei schreiben
	ausgabeDatei << bild->magic[0] << bild->magic[1] << '\n' << bild->ny << " " << bild->nx << '\n' << bild->graumax << '\n';

	//Bild schreiben
	for (int i = 0; i < bild->nx; i++)
	{
		for (int j = 0; j < bild->ny; j++)
		{
			ausgabeDatei << setfill(' ') << setw(4) << (int)bild->bild[i][j];
		}
		ausgabeDatei << '\n';
	}

	//Stream schließen
	ausgabeDatei.close();
}

/*
Kopiert die pgm header Informationen aus dem Struct 
auf den bild1 zeigt in den Struct auf den bild2 zeigt
*/
void kopiere_bildkopf(pgm_bild *bild1, pgm_bild *bild2)
{
	bild2->graumax = bild1->graumax;
	bild2->magic[0] = bild1->magic[0];
	bild2->magic[1] = bild1->magic[1];
	bild2->nx = bild1->nx;
	bild2->ny = bild1->ny;
}

/**
* Allokiere eine neue Pixelmatrix mit der Größe rows*columns
* @param rows reihen
* @param columns spalten
* @return pointer auf array von pointern die auf zeilen der pixelmatrix zeigen
*/
Pixel ** new_pixel_matrix(size_t rows, size_t columns)
{
	size_t i;
	Pixel **m;

	//pointer array
	m = new Pixel *[rows];

	//Daten Array
	*m = new Pixel[rows * columns];

	for (i = 1; i < rows; i++)
		m[i] = m[i - 1] + columns;
	return m;
}

/**
* Gibt allkokierten Speicher eines 2d Arrays frei
* m: pointer auf arraypointer auf zeilen des freizugebenden arrays
*/
void delete_pixel_matrix(Pixel **m)
{
	//lösche daten array
	delete[] *m;

	//lösche pointer array
	delete[] m;
}

/*Beschreibung: invertiert ein bild (zweidimensionales pixel array)
bild1: pointer auf struct dessen pixelmatrix vorlage ist
bild2: pointer auf struct dessen pixelmatrix manipuliert wird
*/
void invertieren(pgm_bild *bild1, pgm_bild *bild2)
{
	for (int i = 0; i < bild1->nx; i++)
	{
		for (int j = 0; j < bild1->ny; j++)
		{
			bild2->bild[i][j] = bild1->graumax - bild1->bild[i][j];
		}
	}
}

/*Beschreibung: glättet ein bild (zweidimensionales pixel array)
bild1: pointer auf struct dessen pixelmatrix vorlage ist
bild2: pointer auf struct dessen pixelmatrix manipuliert wird
*/
void glaetten(pgm_bild *bild1, pgm_bild *bild2)
{
	int mittelWert = 0;

	for (int i = 0; i < bild1->nx; i++)
	{
		for (int j = 0; j < bild1->ny; j++)
		{
			//Wenn mittelwertbildung möglich
			if (i > 0 && j > 0 && i < (bild1->nx-1) && j < (bild1->ny-1))
			{
				mittelWert = ((int)bild1->bild[i][j] + (int)bild1->bild[i][j - 1] +
					(int)bild1->bild[i][j + 1] + (int)bild1->bild[i - 1][j]
					+ (int)bild1->bild[i - 1][j - 1] + (int)bild1->bild[i - 1][j +
					1] + (int)bild1->bild[i + 1][j - 1] + (int)bild1->bild[i + 1][j]
					+ (int)bild1->bild[i + 1][j + 1]) / 9;
			}
			else //sonst originalpixel
			{
				mittelWert = bild1->bild[i][j];
			}
			bild2->bild[i][j] = mittelWert;
		}
	}
}

/*Beschreibung: zeichnet kanten eines bildes (zweidimensionales pixel array)
bild1: pointer auf struct dessen pixelmatrix vorlage ist
bild2: pointer auf struct dessen pixelmatrix manipuliert wird
*/
void kantenbildung(pgm_bild *bild1, pgm_bild *bild2)
{
	int gewichtung = 0;
	for (int i = 0; i < bild1->nx; i++)
	{
		for (int j = 0; j < bild1->ny; j++)
		{
			//Wenn mittelwertbildung möglich
			if (i > 0 && j > 0 && i < (bild1->nx-1) && j < (bild1->ny-1))
			{
				gewichtung = (4 * (int)bild1->bild[i][j] - (int)bild1->bild[i][j - 1] -
					(int)bild1->bild[i][j + 1] - (int)bild1->bild[i - 1][j]
					- (int)bild1->bild[i + 1][j]) / 9;
			}
			else //sonst schwarz
			{
				gewichtung = 0;
			}

			bild2->bild[i][j] = abs(gewichtung);
		}
	}
}

/*Beschreibung: schärft ein bild (zweidimensionales pixel array)
bild1: pointer auf struct dessen pixelmatrix vorlage ist
bild2: pointer auf struct dessen pixelmatrix manipuliert wird
*/
void schaerfen(pgm_bild *bild1, pgm_bild *bild2)
{
	int gewichtung = 0;
	for (int i = 0; i < bild1->nx; i++)
	{
		for (int j = 0; j < bild1->ny; j++)
		{
			//Wenn wertbildung möglich
			if (i > 0 && j > 0 && i < (bild1->nx-1) && j < (bild1->ny-1))
			{
				gewichtung = (9 * (int)bild1->bild[i][j] - (int)bild1->bild[i][j - 1] -
					(int)bild1->bild[i][j + 1] - (int)bild1->bild[i - 1][j]
					- (int)bild1->bild[i - 1][j - 1] - (int)bild1->bild[i - 1][j +
					1] - (int)bild1->bild[i + 1][j - 1] - (int)bild1->bild[i + 1][j]
					- (int)bild1->bild[i + 1][j + 1]);
				if (gewichtung < 0) //falls wert kleiner als 0 auf schwarz werden
				{
					gewichtung = 0;
				}
				else if (gewichtung > bild1->graumax) //falls größer als graumax auf weiß
				{
					gewichtung = bild1->graumax;
				}
			}
			else //sonst schwarz
			{
				gewichtung = 0;
			}
			bild2->bild[i][j] = abs(gewichtung);
		}
	}
}
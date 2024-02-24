
#ifndef FOGADAS
#define FOGADAS
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;
class Nevek               //osztályok
{
public:
    string nev;
    int pont{ 100 };
};

class Esemeny
{
public:
    string ertek = "";
    double szorzo = 0;
    double hanyan = 1;
    double aktualis_nyeremeny = 0;
};
class Jatek
{
public:
    string szervezo, jateknev;
    vector<string> alanyok;
    vector<string> esemenyek;
    vector<vector<double>> darab; //zárás után: szorzó
    vector<vector<string>> vegeredmeny;
    bool lezart{ false };
    vector<vector<vector<Esemeny>>> esemenyter;
};
class Fogadas
{
public:
    string fogadonev, jateknev, alany, esemeny, vart_ertek;
    int tet_osszeg;
};


void menu_kiir(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
void menu_kiir_szervezo(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
void menu_kiir_fogado(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
Jatek jatek_csinal(vector<Nevek>& pontszamok);
void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);
void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);

void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);

#endif

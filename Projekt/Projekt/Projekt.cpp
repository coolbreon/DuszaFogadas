#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
//CSAPATN�V - :::kett�spont:::
using namespace std;
class Nevek               //oszt�lyok
{
public:
    string nev;
    int pont{ 100 };
};
class Jatek
{
public:
    string szervezo, jateknev;
    vector<string> alanyok;
    vector<string> esemenyek;
    vector<vector<double>> darab; //z�r�s ut�n: szorz�
    vector<vector<string>> vegeredmeny;
    bool lezart{ false };
};
class Fogadas
{
public:
    string fogadonev, jateknev, alany, esemeny, vart_ertek;
    int tet_osszeg;
};

void menu_kiir(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
Jatek jatek_csinal();
void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);
void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
double szorzo(int darab);

void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);
void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);

//BEM�S�������������L
bool operator<(Nevek bal, Nevek jobb)
{
    return bal.pont > jobb.pont;
}
bool operator>(Nevek bal, Nevek jobb)
{
    return bal.pont < jobb.pont;
}
bool operator==(Nevek bal, Nevek jobb)
{
    return bal.pont == jobb.pont;
}
int main()
{
    setlocale(LC_ALL, "");
    vector<Jatek> jatekok;
    vector<Fogadas> fogadasok;
    vector<Nevek> pontszamok;
    menu_kiir(jatekok, fogadasok, pontszamok);
}

void menu_kiir(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 5) //ADDIG L�P�NK VISSZA A MEN�BE, AM�G NEM A KIL�P�SRE NYOMUNK
    {
        if (input == 1)
        {
            jatekok.push_back(jatek_csinal());
        }
        else if (input == 2)
            fogadas_csinal(pontszamok, fogadasok, jatekok);

        else if (input == 3)
            jatek_lezarasa(jatekok, fogadasok, pontszamok);

        else if (input == 4)
            lekerdezesek(pontszamok, fogadasok, jatekok);

        system("cls");
        std::cout << "[1] J�t�k l�trehoz�sa\n";
        std::cout << "[2] Fogad�s l�trehoz�sa\n";
        std::cout << "[3] J�t�k lez�r�sa\n";
        std::cout << "[4] Lek�rdez�sek\n";
        std::cout << "[5] Kil�p�s\n";
        cout << "V�lasszon men�pontot: ";
        cin >> input;
    }
}

Jatek jatek_csinal() //Sor: Alany, Oszlop: Esem�ny
{
    Jatek sv;
    cout << "Szervez�: ";
    cin.get();
    getline(cin, sv.szervezo);
    cout << "J�t�k neve: ";
    getline(cin, sv.jateknev);
    string sv2;
    cout << "Alanyok: (nyomjon ENTER-t ha a list�nak v�ge)\n";
    getline(cin, sv2);
    while (sv2 != "")
    {
        sv.alanyok.push_back(sv2);
        getline(cin, sv2);
    }
    cout << "Esemeny�k: (nyomjon ENTER-t ha a list�nak v�ge\n";
    getline(cin, sv2);
    while (sv2 != "")
    {
        sv.esemenyek.push_back(sv2);
        getline(cin, sv2);
    }

    sv.darab.resize(sv.alanyok.size());
    for (int i = 0; i < sv.darab.size(); i++)
    {
        sv.darab[i].resize(sv.esemenyek.size());
    }

    //F�JLBA �R�S
    ofstream fki("jatekok.txt", std::ios::app);
    fki << sv.szervezo << ';' << sv.jateknev << ';' << sv.alanyok.size() << ';' << sv.esemenyek.size() << '\n';
    for (int i = 0; i < sv.alanyok.size(); i++)
    {
        fki << sv.alanyok[i] << '\n';
    }
    for (int i = 0; i < sv.esemenyek.size(); i++)
    {
        fki << sv.esemenyek[i] << '\n';
    }
    fki.close();
    //F�JLBA �R�S V�GE

    return sv;
}


void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    Fogadas sv;

    cout << "K�rem v�lasszon az al�bbi, m�g folyamatban lev� j�t�kok k�z�l!: (a sorsz�m megad�s�val)" << endl;
    for (int i = 0; i < jatekok.size(); i++)
    {
        if (!jatekok[i].lezart)
        {
            cout << i + 1 << ".: " << jatekok[i].jateknev << endl;
        }
    }
    int sorsz;
    cin >> sorsz;
    sv.jateknev = jatekok[sorsz - 1].jateknev;

    cin.get();
    cout << "Fogad� n�v: ";
    getline(cin, sv.fogadonev);
    int i = 0;
    while (i < pontszamok.size() && pontszamok[i].nev != sv.fogadonev) //el�fordult m�r ez a az ember fogad�k�nt?
    {
        i++;
    }
    if (i == pontszamok.size()) //ha m�g nem, akkor hozz�adjuk, mint �j embert
        pontszamok.push_back({ sv.fogadonev,100 });

    cout << "Pontok: " << pontszamok[i].pont << '\n';  //fogad� ember aktu�lis p�nze


    cout << "Alany: ";     //fogad�s
    getline(cin, sv.alany);
    cout << "Esem�ny: ";
    getline(cin, sv.esemeny);

    cout << "V�rt �rt�k: ";
    getline(cin, sv.vart_ertek);
    cout << "T�t: ";
    cin >> sv.tet_osszeg;

    if (sv.tet_osszeg <= pontszamok[i].pont)     //ellen�rizni, hogy van-e el�g pontja
    {

        bool talalt = false;
        int j = 0;

        while (!talalt && j < fogadasok.size())
        {
            if (fogadasok[j].fogadonev == sv.fogadonev && fogadasok[j].esemeny == sv.esemeny && fogadasok[j].alany == sv.alany) //ellen�rizni, hogy fogadott-e m�r az adott ember az adott alany+esemeny parra
            {
                talalt = true;
            }
            j++;
        }
        if (!talalt) //HA MINDEN FELT�TEL TELJES�L:
        {
            pontszamok[i].pont -= sv.tet_osszeg;
            fogadasok.push_back(sv);
            ofstream fki("fogadasok.txt", ios::app);
            fki << sv.fogadonev << ';' << sv.jateknev << ';' << sv.tet_osszeg << ';'
                << sv.alany << ';' << sv.esemeny << ';' << sv.vart_ertek << '\n'; //F�JLBA �R�S
            fki.close();
            int srsz1{}, srsz2{};
            while (srsz1 < jatekok[sorsz - 1].alanyok.size() && jatekok[sorsz - 1].alanyok[srsz1] != sv.alany)
            {
                srsz1++;
            }
            while (srsz2 < jatekok[sorsz - 1].esemenyek.size() && jatekok[sorsz - 1].esemenyek[srsz2] != sv.esemeny)
            {
                srsz2++;
            }
            jatekok[sorsz - 1].darab[srsz1][srsz2]++;
        }
        else
        {
            cout << "Erre az alany+esem�ny p�rra a j�t�kos m�r fogadott." << endl;
            cin.get();

        }


    }
    else
    {
        cout << "A j�t�kosnak nincs el�g pontja." << endl;
        cin.get();

    }

    cin.get(); //BEFAGYASZT�S, HOGY OLVASHAT� LEGYEN A HIBA�ZENET




}

void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    string sv_szervezo, sv_jatek;
    cout << "Szervez� neve: ";
    cin.get();
    getline(cin, sv_szervezo);

    cout << "J�t�k neve: ";
    getline(cin, sv_jatek);

    //megkeresi szervez� neve, �s j�t�k neve -> esem�nyeit �s neveit
    int i = 0;
    while (i < jatekok.size() && jatekok[i].szervezo != sv_szervezo && jatekok[i].jateknev != sv_jatek)
        i++;
    ofstream fki("eredmenyek.txt", ios::app);
    fki << jatekok[i].jateknev << '\n';
    if (i < jatekok.size() && !(jatekok[i].lezart))
    {

        //helyes adat, j�t�k lez�r�sa
        jatekok[i].vegeredmeny.resize(jatekok[i].alanyok.size());  //v�geredm�ny m�trix resize-ol�sa
        for (int j = 0; j < jatekok[i].alanyok.size(); j++)
        {
            jatekok[i].vegeredmeny[j].resize(jatekok[i].esemenyek.size());
        }

        //v�geredm�nyek r�gz�t�se �s pontsz�m�t�s
        for (int a = 0; a < jatekok[i].alanyok.size(); a++)
        {
            for (int b = 0; b < jatekok[i].esemenyek.size(); b++)
            {
                //r�gz�t�s
                cout << jatekok[i].alanyok[a] << " " << jatekok[i].esemenyek[b] << " eredm�nye: ";
                getline(cin, jatekok[i].vegeredmeny[a][b]);

                //szorz�
                jatekok[i].darab[a][b] = (round(100 * szorzo(jatekok[i].darab[a][b]))) / 100;
                fki << jatekok[i].alanyok[a] << ';' << jatekok[i].esemenyek[b] << ';' << jatekok[i].vegeredmeny[a][b] << ';' << jatekok[i].darab[a][b] << '\n';

                //pontsz�m�t�s
                //alany, esem�ny, v�rt �rt�k �s j�t�k egyez�se
                //els� alany, m�sodik esem�ny
                for (auto elem : fogadasok)
                {
                    if (jatekok[i].alanyok[a] == elem.alany && jatekok[i].esemenyek[b] == elem.esemeny && elem.vart_ertek == jatekok[i].vegeredmeny[a][b] && jatekok[i].jateknev == elem.jateknev)
                    {

                        //pontsz�m n�vel�se
                        for (int k = 0; k < pontszamok.size(); k++)
                        {
                            if (pontszamok[k].nev == elem.fogadonev)
                            {
                                pontszamok[k].pont += elem.tet_osszeg * jatekok[i].darab[a][b];
                            }
                        }
                    }
                }
            }
        }

        //j�t�k lez�r�sa
        jatekok[i].lezart = true;
        fki.close();
    }

    else
    {
        //nem helyes adat, nem tud j�t�kot lez�rni
        cout << "Helytelen a szervez� neve vagy a j�t�k neve! " << endl;
        cin.get();
        cin.get();
    }

}
void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    cout << "K�rem, v�lasszon az al�bbi pontok k�z�l a sorsz�m megad�s�val: " << endl;
    cout << 1 << ". :Ranglista" << endl;
    cout << 2 << ". :J�t�k statisztika" << endl;
    cout << 3 << ". :Fogad�si statisztika" << endl;
    int sorsz;
    cin >> sorsz;
    if (sorsz == 1)
    {
        sort(pontszamok.begin(), pontszamok.end());
        sorsz = 1;

        for (int i = 1; i < pontszamok.size(); i++)
        {
            if (round(pontszamok[i].pont) == round(pontszamok[i - 1].pont))
            {
                cout << sorsz << ".: " << pontszamok[i - 1].nev << endl;
            }
            if (round(pontszamok[i].pont) != round(pontszamok[i - 1].pont))
            {
                cout << sorsz << ".: " << pontszamok[i - 1].nev << endl;
                sorsz++;
            }

        }
        if (pontszamok.size() == 1)
        {
            cout << 1 << ".: " << pontszamok[0].nev;
        }
        else
        {
            if (round(pontszamok[pontszamok.size() - 1].pont) == round(pontszamok[pontszamok.size() - 2].pont))
            {
                cout << sorsz << ".: " << pontszamok[pontszamok.size() - 1].nev << endl;
            }
            else
            {
                cout << sorsz + 1 << ".: " << pontszamok[pontszamok.size() - 1].nev << endl;
            }
        }

    }
    else if (sorsz == 2)
    {
        for (int i = 0; i < jatekok.size(); i++)
        {



            int osszfogadas = 0;
            int ossztet = 0;
            int ossznyeremeny = 0;
            for (int j = 0; j < fogadasok.size(); j++)
            {
                if (jatekok[i].jateknev == fogadasok[j].jateknev)
                {
                    osszfogadas++;
                    ossztet += fogadasok[j].tet_osszeg;
                    int k = 0;
                    while (jatekok[i].alanyok[k] != fogadasok[j].alany)
                    {
                        k++;
                    }
                    int l = 0;
                    while (jatekok[i].esemenyek[l] != fogadasok[j].esemeny)
                    {
                        l++;
                    }
                    if (jatekok[i].lezart == true)
                    {
                        ossznyeremeny += jatekok[i].darab[k][l] * fogadasok[j].tet_osszeg;

                    }
                    else
                    {
                        cout << i + 1 << ". j�t�k �ssznyerem�nye: " << 0 << endl;
                    }

                }
            }


        }
    }
}
double szorzo(int darab)
{
    double sv_szorzo;

    if (darab > 0)
        sv_szorzo = (1 + (5 / (pow(2, darab - 1))));
    else
        sv_szorzo = 0;

    return sv_szorzo;
}

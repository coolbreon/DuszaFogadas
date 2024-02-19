#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
//CSAPATNÉV - :::kettõspont:::
using namespace std;
class Nevek               //osztályok
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
    vector<vector<double>> darab; //zárás után: szorzó
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
void menu_kiir_szervezo(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
void menu_kiir_fogado(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
Jatek jatek_csinal();
void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);
void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok);
double szorzo(int darab);

void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);
void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok);

//BEMÁSÓÓÓÓÓÓÓÓÓÓÓÓÓL
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
    while (input != 3) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            menu_kiir_fogado(jatekok, fogadasok, pontszamok);
        }
        else if (input == 2)
            menu_kiir_szervezo(jatekok, fogadasok, pontszamok);


        system("cls");
        std::cout << "Kérem válasszon egy felhasználó típust: \n";
        std::cout << "[1] Fogadó\n";
        std::cout << "[2] Szervező\n";
        std::cout << "[3] Kilépés\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}

void menu_kiir_szervezo(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 4) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            jatekok.push_back(jatek_csinal());
        }
        else if (input == 2)
            jatek_lezarasa(jatekok, fogadasok, pontszamok);

        else if (input == 3)
            lekerdezesek(pontszamok, fogadasok, jatekok);


        system("cls");
        std::cout << "[1] Játék létrehozása\n";
        std::cout << "[2] Játék lezárása\n";
        std::cout << "[3] Lekérdezések\n";
        std::cout << "[4] Kilépés a főmenübe (Felhasználóváltás)\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}

void menu_kiir_fogado(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 2) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            fogadas_csinal(pontszamok, fogadasok, jatekok);
        }

        system("cls");
        std::cout << "[1] Fogadás létrehozása\n";
        std::cout << "[2] Kilépés a főmenübe (Felhasználóváltás)\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}

Jatek jatek_csinal() //Sor: Alany, Oszlop: Esemény
{
    Jatek sv;
    cout << "Szervezõ: ";
    cin.get();
    getline(cin, sv.szervezo);
    cout << "Játék neve: ";
    getline(cin, sv.jateknev);
    string sv2;
    cout << "Alanyok: (nyomjon ENTER-t ha a listának vége)\n";
    getline(cin, sv2);
    while (sv2 != "")
    {
        sv.alanyok.push_back(sv2);
        getline(cin, sv2);
    }
    cout << "Esemenyék: (nyomjon ENTER-t ha a listának vége\n";
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

    //FÁJLBA ÍRÁS
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
    //FÁJLBA ÍRÁS VÉGE

    return sv;
}


void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    Fogadas sv;

    cout << "Kérem válasszon az alábbi, még folyamatban levõ játékok közül!: (a sorszám megadásával)" << endl;
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
    cout << "Fogadó név: ";
    getline(cin, sv.fogadonev);
    int i = 0;
    while (i < pontszamok.size() && pontszamok[i].nev != sv.fogadonev) //elõfordult már ez a az ember fogadóként?
    {
        i++;
    }
    if (i == pontszamok.size()) //ha még nem, akkor hozzáadjuk, mint új embert
        pontszamok.push_back({ sv.fogadonev,100 });

    cout << "Pontok: " << pontszamok[i].pont << '\n';  //fogadó ember aktuális pénze


    cout << "Alany: ";     //fogadás
    getline(cin, sv.alany);
    cout << "Esemény: ";
    getline(cin, sv.esemeny);

    cout << "Várt érték: ";
    getline(cin, sv.vart_ertek);
    cout << "Tét: ";
    cin >> sv.tet_osszeg;

    if (sv.tet_osszeg <= pontszamok[i].pont)     //ellenõrizni, hogy van-e elég pontja
    {

        bool talalt = false;
        int j = 0;

        while (!talalt && j < fogadasok.size())
        {
            if (fogadasok[j].fogadonev == sv.fogadonev && fogadasok[j].esemeny == sv.esemeny && fogadasok[j].alany == sv.alany) //ellenõrizni, hogy fogadott-e már az adott ember az adott alany+esemeny parra
            {
                talalt = true;
            }
            j++;
        }
        if (!talalt) //HA MINDEN FELTÉTEL TELJESÜL:
        {
            pontszamok[i].pont -= sv.tet_osszeg;
            fogadasok.push_back(sv);
            ofstream fki("fogadasok.txt", ios::app);
            fki << sv.fogadonev << ';' << sv.jateknev << ';' << sv.tet_osszeg << ';'
                << sv.alany << ';' << sv.esemeny << ';' << sv.vart_ertek << '\n'; //FÁJLBA ÍRÁS
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
            cout << "Erre az alany+esemény párra a játékos már fogadott." << endl;
            cin.get();

        }


    }
    else
    {
        cout << "A játékosnak nincs elég pontja." << endl;
        cin.get();

    }

    cin.get(); //BEFAGYASZTÁS, HOGY OLVASHATÓ LEGYEN A HIBAÜZENET




}

void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    string sv_szervezo, sv_jatek;
    cout << "Szervezõ neve: ";
    cin.get();
    getline(cin, sv_szervezo);

    cout << "Játék neve: ";
    getline(cin, sv_jatek);

    //megkeresi szervezõ neve, és játék neve -> eseményeit és neveit
    int i = 0;
    while (i < jatekok.size() && jatekok[i].szervezo != sv_szervezo && jatekok[i].jateknev != sv_jatek)
        i++;
    ofstream fki("eredmenyek.txt", ios::app);
    fki << jatekok[i].jateknev << '\n';
    if (i < jatekok.size() && !(jatekok[i].lezart))
    {

        //helyes adat, játék lezárása
        jatekok[i].vegeredmeny.resize(jatekok[i].alanyok.size());  //végeredmény mátrix resize-olása
        for (int j = 0; j < jatekok[i].alanyok.size(); j++)
        {
            jatekok[i].vegeredmeny[j].resize(jatekok[i].esemenyek.size());
        }

        //végeredmények rögzítése és pontszámítás
        for (int a = 0; a < jatekok[i].alanyok.size(); a++)
        {
            for (int b = 0; b < jatekok[i].esemenyek.size(); b++)
            {
                //rögzítés
                cout << jatekok[i].alanyok[a] << " " << jatekok[i].esemenyek[b] << " eredménye: ";
                getline(cin, jatekok[i].vegeredmeny[a][b]);

                //szorzó
                jatekok[i].darab[a][b] = (round(100 * szorzo(jatekok[i].darab[a][b]))) / 100;
                fki << jatekok[i].alanyok[a] << ';' << jatekok[i].esemenyek[b] << ';' << jatekok[i].vegeredmeny[a][b] << ';' << jatekok[i].darab[a][b] << '\n';

                //pontszámítás
                //alany, esemény, várt érték és játék egyezése
                //elsõ alany, második esemény
                for (auto elem : fogadasok)
                {
                    if (jatekok[i].alanyok[a] == elem.alany && jatekok[i].esemenyek[b] == elem.esemeny && elem.vart_ertek == jatekok[i].vegeredmeny[a][b] && jatekok[i].jateknev == elem.jateknev)
                    {

                        //pontszám növelése
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

        //játék lezárása
        jatekok[i].lezart = true;
        fki.close();
    }

    else
    {
        //nem helyes adat, nem tud játékot lezárni
        cout << "Helytelen a szervezõ neve vagy a játék neve! " << endl;
        cin.get();
        cin.get();
    }

}
void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    cout << "Kérem, válasszon az alábbi pontok közül a sorszám megadásával: " << endl;
    cout << 1 << ". :Ranglista" << endl;
    cout << 2 << ". :Játék statisztika" << endl;
    cout << 3 << ". :Fogadási statisztika" << endl;
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
                        cout << i + 1 << ". játék össznyereménye: " << 0 << endl;
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

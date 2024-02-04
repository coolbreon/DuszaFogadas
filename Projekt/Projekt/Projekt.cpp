#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
//CSAPATN…V - :::kettıspont:::
using namespace std;
class Nevek               //oszt·lyok
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
    vector<vector<double>> darab; //z·r·s ut·n: szorzÛ
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

//BEM¡S”””””””””””””L
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
    while (input != 5) //ADDIG L…P‹NK VISSZA A MEN‹BE, AMÕG NEM A KIL…P…SRE NYOMUNK
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
        std::cout << "[1] J·tÈk lÈtrehoz·sa\n";
        std::cout << "[2] Fogad·s lÈtrehoz·sa\n";
        std::cout << "[3] J·tÈk lez·r·sa\n";
        std::cout << "[4] LekÈrdezÈsek\n";
        std::cout << "[5] KilÈpÈs\n";
        cout << "V·lasszon men¸pontot: ";
        cin >> input;
    }
}

Jatek jatek_csinal() //Sor: Alany, Oszlop: EsemÈny
{
    Jatek sv;
    cout << "Szervezı: ";
    cin.get();
    getline(cin, sv.szervezo);
    cout << "J·tÈk neve: ";
    getline(cin, sv.jateknev);
    string sv2;
    cout << "Alanyok: (nyomjon ENTER-t ha a list·nak vÈge)\n";
    getline(cin, sv2);
    while (sv2 != "")
    {
        sv.alanyok.push_back(sv2);
        getline(cin, sv2);
    }
    cout << "EsemenyÈk: (nyomjon ENTER-t ha a list·nak vÈge\n";
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

    //F¡JLBA ÕR¡S
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
    //F¡JLBA ÕR¡S V…GE

    return sv;
}


void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    Fogadas sv;

    cout << "KÈrem v·lasszon az al·bbi, mÈg folyamatban levı j·tÈkok kˆz¸l!: (a sorsz·m megad·s·val)" << endl;
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
    cout << "FogadÛ nÈv: ";
    getline(cin, sv.fogadonev);
    int i = 0;
    while (i < pontszamok.size() && pontszamok[i].nev != sv.fogadonev) //elıfordult m·r ez a az ember fogadÛkÈnt?
    {
        i++;
    }
    if (i == pontszamok.size()) //ha mÈg nem, akkor hozz·adjuk, mint ˙j embert
        pontszamok.push_back({ sv.fogadonev,100 });

    cout << "Pontok: " << pontszamok[i].pont << '\n';  //fogadÛ ember aktu·lis pÈnze


    cout << "Alany: ";     //fogad·s
    getline(cin, sv.alany);
    cout << "EsemÈny: ";
    getline(cin, sv.esemeny);

    cout << "V·rt ÈrtÈk: ";
    getline(cin, sv.vart_ertek);
    cout << "TÈt: ";
    cin >> sv.tet_osszeg;

    if (sv.tet_osszeg <= pontszamok[i].pont)     //ellenırizni, hogy van-e elÈg pontja
    {

        bool talalt = false;
        int j = 0;

        while (!talalt && j < fogadasok.size())
        {
            if (fogadasok[j].fogadonev == sv.fogadonev && fogadasok[j].esemeny == sv.esemeny && fogadasok[j].alany == sv.alany) //ellenırizni, hogy fogadott-e m·r az adott ember az adott alany+esemeny parra
            {
                talalt = true;
            }
            j++;
        }
        if (!talalt) //HA MINDEN FELT…TEL TELJES‹L:
        {
            pontszamok[i].pont -= sv.tet_osszeg;
            fogadasok.push_back(sv);
            ofstream fki("fogadasok.txt", ios::app);
            fki << sv.fogadonev << ';' << sv.jateknev << ';' << sv.tet_osszeg << ';'
                << sv.alany << ';' << sv.esemeny << ';' << sv.vart_ertek << '\n'; //F¡JLBA ÕR¡S
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
            cout << "Erre az alany+esemÈny p·rra a j·tÈkos m·r fogadott." << endl;
            cin.get();

        }


    }
    else
    {
        cout << "A j·tÈkosnak nincs elÈg pontja." << endl;
        cin.get();

    }

    cin.get(); //BEFAGYASZT¡S, HOGY OLVASHAT” LEGYEN A HIBA‹ZENET




}

void jatek_lezarasa(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    string sv_szervezo, sv_jatek;
    cout << "Szervezı neve: ";
    cin.get();
    getline(cin, sv_szervezo);

    cout << "J·tÈk neve: ";
    getline(cin, sv_jatek);

    //megkeresi szervezı neve, Ès j·tÈk neve -> esemÈnyeit Ès neveit
    int i = 0;
    while (i < jatekok.size() && jatekok[i].szervezo != sv_szervezo && jatekok[i].jateknev != sv_jatek)
        i++;
    ofstream fki("eredmenyek.txt", ios::app);
    fki << jatekok[i].jateknev << '\n';
    if (i < jatekok.size() && !(jatekok[i].lezart))
    {

        //helyes adat, j·tÈk lez·r·sa
        jatekok[i].vegeredmeny.resize(jatekok[i].alanyok.size());  //vÈgeredmÈny m·trix resize-ol·sa
        for (int j = 0; j < jatekok[i].alanyok.size(); j++)
        {
            jatekok[i].vegeredmeny[j].resize(jatekok[i].esemenyek.size());
        }

        //vÈgeredmÈnyek rˆgzÌtÈse Ès pontsz·mÌt·s
        for (int a = 0; a < jatekok[i].alanyok.size(); a++)
        {
            for (int b = 0; b < jatekok[i].esemenyek.size(); b++)
            {
                //rˆgzÌtÈs
                cout << jatekok[i].alanyok[a] << " " << jatekok[i].esemenyek[b] << " eredmÈnye: ";
                getline(cin, jatekok[i].vegeredmeny[a][b]);

                //szorzÛ
                jatekok[i].darab[a][b] = (round(100 * szorzo(jatekok[i].darab[a][b]))) / 100;
                fki << jatekok[i].alanyok[a] << ';' << jatekok[i].esemenyek[b] << ';' << jatekok[i].vegeredmeny[a][b] << ';' << jatekok[i].darab[a][b] << '\n';

                //pontsz·mÌt·s
                //alany, esemÈny, v·rt ÈrtÈk Ès j·tÈk egyezÈse
                //elsı alany, m·sodik esemÈny
                for (auto elem : fogadasok)
                {
                    if (jatekok[i].alanyok[a] == elem.alany && jatekok[i].esemenyek[b] == elem.esemeny && elem.vart_ertek == jatekok[i].vegeredmeny[a][b] && jatekok[i].jateknev == elem.jateknev)
                    {

                        //pontsz·m nˆvelÈse
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

        //j·tÈk lez·r·sa
        jatekok[i].lezart = true;
        fki.close();
    }

    else
    {
        //nem helyes adat, nem tud j·tÈkot lez·rni
        cout << "Helytelen a szervezı neve vagy a j·tÈk neve! " << endl;
        cin.get();
        cin.get();
    }

}
void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    cout << "KÈrem, v·lasszon az al·bbi pontok kˆz¸l a sorsz·m megad·s·val: " << endl;
    cout << 1 << ". :Ranglista" << endl;
    cout << 2 << ". :J·tÈk statisztika" << endl;
    cout << 3 << ". :Fogad·si statisztika" << endl;
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
                        cout << i + 1 << ". j·tÈk ˆssznyeremÈnye: " << 0 << endl;
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

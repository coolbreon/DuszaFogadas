#include "fogadas.h"

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

void lekerdezesek(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    cout << "Kérem, válasszon az alábbi pontok közül a sorszám megadásával: " << endl;
    cout <<"["<< 1 << "] Ranglista" << endl;
    cout <<"["<< 2 << "] Játék statisztika" << endl;
    cout <<"["<< 3 << "] Fogadási statisztika" << endl;
    cout <<"["<< 4 << "] Kilépés a menübe" << endl;
    int sorsz;
    cin >> sorsz;
    if (sorsz == 1)
    {
        if (!pontszamok.empty())
        {
        sort(pontszamok.begin(), pontszamok.end());
        sorsz = 1;
        for (int i = 1; i < pontszamok.size(); i++)
        {
            if (round(pontszamok[i].pont) == round(pontszamok[i - 1].pont))
            {
                cout <<"["<< sorsz << "] " << pontszamok[i - 1].nev << " - " << round(pontszamok[i-1].pont) <<"pont\n";
            }
            if (round(pontszamok[i].pont) != round(pontszamok[i - 1].pont))
            {
                cout << "["<< sorsz << "] " << pontszamok[i - 1].nev  << " - " << round(pontszamok[i-1].pont) <<"pont\n";
                sorsz++;
            }
        }
        if (pontszamok.size() == 1)
        {
            cout <<"["<< 1 << "] " << pontszamok[0].nev << " - " << round(pontszamok[0].pont) <<"pont\n";
        }
        else
        {
            if (round(pontszamok[pontszamok.size() - 1].pont) == round(pontszamok[pontszamok.size() - 2].pont))
            {
                cout <<"["<< sorsz << "] " << pontszamok[pontszamok.size() - 1].nev << " - " << round(pontszamok[pontszamok.size()-1].pont) <<"pont\n";
            }
            else
            {
                cout <<"["<< sorsz + 1 << "] " << pontszamok[pontszamok.size() - 1].nev << " - " << round(pontszamok[pontszamok.size()-1].pont) <<"pont\n";
            }
        }
        }
        else cout << "Még senki sem fogadott.\n"; cin.get(); cin.get();
    }
    else if (sorsz == 2)
    {
        if (jatekok.size()==0)
        {
            cout << "Nincs még játék, amelyre fogadtak volna.";
            cin.get();
        }
        for (int i = 0; i < jatekok.size(); i++)
        {



            double osszfogadas = 0;
            double ossztet = 0;
            double ossznyeremeny = 0;


            
            //fogadások száma
            for (int k = 0; k <jatekok[i].darab.size(); k++)
            {
                for (int l = 0; l < jatekok[i].darab[k].size(); l++)
                {
                    osszfogadas += jatekok[i].darab[k][l];
                }
            }
            //össztét száma
            for (int k = 0; k < jatekok[i].esemenyter.size(); k++)
            {
                for (int l = 0; l < jatekok[i].esemenyter[k].size(); l++)
                {
                    for (int m = 0; m < jatekok[i].esemenyter[k][l].size(); m++)
                    {
                        ossztet += jatekok[i].esemenyter[k][l][m].mennyit;
                    }
                    
                }
            }
           
            
            cout << i + 1 << ". játék statisztikái:\n";
            cout << "Fogadások száma: " << osszfogadas << " db\n";
            cout << "Feltett tétek: " << ossztet << " pont\n";

            if (jatekok[i].lezart)
            {
                //össznyeremény számol
                for (int k = 0; k < jatekok[i].esemenyter.size(); k++)
                {
                    for (int l = 0; l < jatekok[i].esemenyter[k].size(); l++)
                    {
                        int m = 0;
                        while (jatekok[i].esemenyter[k][l][m].ertek != jatekok[i].vegeredmeny[k][l] && m < jatekok[i].esemenyter[k][l].size())
                        {
                            m++;
                        }
                        ossznyeremeny += jatekok[i].esemenyter[k][l][m].aktualis_nyeremeny;

                    }
                }
                
                cout << "Összes nyeremény: " << ossznyeremeny << " pont\n";
            }
            else
            {
                cout << i + 1 << ". játék össznyereménye: " << 0 << ", mivel a játék még lezáratlan." << endl;
            }
            
        }
        cin.get(); cin.get();
    }
    else if (sorsz==3)
    {
        if (!fogadasok.empty())
        {
        cout << "Kérem válasszon az alábbi játékok közül: ";
        for (int i = 0; i < jatekok.size(); i++)
        {
                cout << "["<< i + 1 << "] " << jatekok[i].jateknev << endl;
        }
        int jatek_index;
        cin >> jatek_index;
        jatek_index--;
        int vart_ertek_i{};
        int ossztet{};
        int ossznyer{};
        int fog_n{};
        for (int i=0; i<jatekok[jatek_index].alanyok.size(); i++)
        {
            for (int j=0; j<jatekok[jatek_index].esemenyek.size(); j++)
            {
                cout << jatekok[jatek_index].alanyok[i] << " + " <<jatekok[jatek_index].esemenyek[j] << " páros:\n";
                for (int k=0; k<fogadasok.size(); k++)
                {    
                    if (jatekok[jatek_index].jateknev==fogadasok[k].jateknev && jatekok[jatek_index].alanyok[i]==fogadasok[k].alany && jatekok[jatek_index].esemenyek[j]==fogadasok[k].esemeny)
                    {
                    fog_n++;
                    ossztet+=fogadasok[k].tet_osszeg;
                    if (jatekok[jatek_index].lezart==true && jatekok[jatek_index].vegeredmeny[i][j]==fogadasok[k].vart_ertek)
                        {
                        while (jatekok[jatek_index].esemenyter[i][j][vart_ertek_i].ertek!=fogadasok[k].vart_ertek)
                            {
                            vart_ertek_i++;
                            }
                        ossznyer += jatekok[jatek_index].esemenyter[i][j][vart_ertek_i].aktualis_nyeremeny;
                        }
                   
                    }
                }
                cout << "-Fogadások száma: " << fog_n << endl;
                cout << "-Tétek összege: " << ossztet << endl;
                cout << "-Nyeremények összege: " << ossznyer << "\n\n";
                fog_n=0;
                ossztet=0;
                ossznyer=0;
            }

        }
        cin.get();
        }
        else
        {
            cout << "Nincs még játék, amelyre fogadtak volna.";
            cin.get();
        }
        cin.get();
    }
}
#include "fogadas.h"
Jatek jatek_csinal(vector<Nevek>& pontszamok) //Sor: Alany, Oszlop: Esemény
{
    Nevek s_jatekos;
    Jatek sv;
    cout << "Szervezõ: ";
    cin.get();
    getline(cin, sv.szervezo);
    s_jatekos.nev = sv.szervezo;
    pontszamok.push_back(s_jatekos);
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
    sv.esemenyter.resize(sv.alanyok.size());
    for (int i = 0; i < sv.darab.size(); i++)
    {
        sv.darab[i].resize(sv.esemenyek.size());
        sv.esemenyter[i].resize(sv.esemenyek.size());
    }
    Esemeny s_esemeny;
    for (int i = 0; i < sv.alanyok.size(); i++) //szervező megadja a lehetséges végkimeneteleket, szorzók automatikusan beállítva 1/p-re 
    {
        for (int j = 0; j < sv.esemenyek.size(); j++)
        {
            system("cls");

            cout << "Adja meg a lehetséges végkimeneteleket minden alany-esemény párra vonatkozóan (legalább 2 végkimenetel páronként), enterrel elválasztva. Ezután nyomjon még egy entert!" << endl;
            cout << "Alany: " << sv.alanyok[i] << endl;
            cout << "Esemeny: " << sv.esemenyek[j] << endl;
            getline(cin, s_esemeny.ertek);
            while (s_esemeny.ertek != "")
            {
                sv.esemenyter[i][j].push_back(s_esemeny);
                getline(cin, s_esemeny.ertek);
            }
            for (int k = 0; k < sv.esemenyter[i][j].size(); k++)
            {
                sv.esemenyter[i][j][k].szorzo = sv.esemenyter[i][j].size(); //hányszor 1/p? ->kezdetben mindig 1/p
            }

        }

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

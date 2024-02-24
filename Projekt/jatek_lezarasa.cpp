#include "fogadas.h"
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
                 // (régi szorzó: jatekok[i].darab[a][b] = (round(100 * szorzo(jatekok[i].darab[a][b]))) / 100;)
                fki << jatekok[i].alanyok[a] << ';' << jatekok[i].esemenyek[b] << ';' << jatekok[i].vegeredmeny[a][b]; // << ';' << jatekok[i].darab[a][b] << '\n'; erre már nincs szükség

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
                                pontszamok[k].pont += elem.tet_osszeg * jatekok[i].esemenyter[a][b][k].szorzo; //új szorzóval növeljük a pontszámot
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
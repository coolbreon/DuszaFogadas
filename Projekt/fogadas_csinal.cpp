#include "fogadas.h"
void fogadas_csinal(vector<Nevek>& pontszamok, vector<Fogadas>& fogadasok, vector<Jatek>& jatekok)
{
    Fogadas sv;
    cout << "Kérem válasszon az alábbi, még folyamatban levõ játékok közül!: (a sorszám megadásával)" << endl; //játék választás
    for (int i = 0; i < jatekok.size(); i++)
    {
        if (!jatekok[i].lezart)
        {
            cout << "["<< i + 1 << "] " << jatekok[i].jateknev << endl;
        }
    }
    int jatek_index;
    cin >> jatek_index;
    jatek_index--;
    sv.jateknev = jatekok[jatek_index].jateknev;

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


    cout << "Lehetséges alanyok:\n";
    for (int i=0; i<jatekok[jatek_index].alanyok.size(); i++)
    {
        cout << "[" << jatekok[jatek_index].alanyok[i] << "]" << endl;
    }
    cout << "Választott alany: ";     //fogadás
    getline(cin, sv.alany);
    
    cout << "Lehetséges események:\n";
    for (int i=0; i<jatekok[jatek_index].esemenyek.size(); i++)
    {
        cout << "[" << jatekok[jatek_index].esemenyek[i] << "]" << endl;
    }
    cout << "Választott esemény: ";
    getline(cin, sv.esemeny);

    int alany_index = 0;
    int esemeny_index = 0;
    while (alany_index < jatekok[jatek_index].alanyok.size() && jatekok[jatek_index].alanyok[alany_index] != sv.alany)
    {
        alany_index++;
    }
    while (esemeny_index < jatekok[jatek_index].esemenyek.size() && jatekok[jatek_index].esemenyek[esemeny_index] != sv.esemeny)
    {
        esemeny_index++;
    }
   

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
            cout << "Kérem válasszon az alábbi értékek közül (gépelje be az értéket): " << endl; //választási lehetőségek megadása
            for (int k = 0; k < jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size(); k++)
            {
                cout << k + 1 << ". érték:   [" << jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].ertek << "]   szorzó: " << jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].szorzo << endl;
            }


            cout << "Várt érték: ";
            getline(cin, sv.vart_ertek);


            int ertek_index = 0; //tudjuk, hányadik értéket jelölte meg
            while (ertek_index < jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size() && jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].ertek != sv.vart_ertek)
            {
                ertek_index++;
            }

            int szervezo_index = 0;
            string s_szervezo = jatekok[jatek_index].szervezo;
            while (szervezo_index < pontszamok.size() && pontszamok[szervezo_index].nev != s_szervezo)
            {
                szervezo_index++;
            }

            cout << "Tét: ";
            cin >> sv.tet_osszeg;


            double bevetel = 0;

            for (int k = 0; k < jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size(); k++)
            {
                if (k != ertek_index)
                {
                    bevetel += jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].aktualis_nyeremeny;

                }
            }
            double maxtet = 0;
            maxtet = (pontszamok[szervezo_index].pont + bevetel - jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].aktualis_nyeremeny) / jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].szorzo;

            while (sv.tet_osszeg > maxtet)
            {
                cout << "Túl nagy tétet adott meg! A maximálisan feltehető tét :" << maxtet << endl;
                cout << "Kérem,próbálja újra!" << endl;
                cout << "Tét: ";
                cin >> sv.tet_osszeg;
            }


            while (sv.tet_osszeg >= pontszamok[i].pont)     //ellenõrizni, hogy van-e elég pontja
            {
                cout << "A játékosnak nincs elég pontja." << endl;
                cout << "Kérem,próbálja újra!" << endl;
                cout << "Tét: ";
                cin >> sv.tet_osszeg;
            }



            pontszamok[i].pont -= sv.tet_osszeg;
            fogadasok.push_back(sv);
            ofstream fki("fogadasok.txt", ios::app);
            fki << sv.fogadonev << ';' << sv.jateknev << ';' << sv.tet_osszeg << ';'
                << sv.alany << ';' << sv.esemeny << ';' << sv.vart_ertek << '\n'; //FÁJLBA ÍRÁS
            fki.close();

            double ossz = jatekok[jatek_index].darab[alany_index][esemeny_index] + 1; // darab tömbből átvéve, hányan fogadtak összesen az alany-esemény párosra
            double nevezo = 0;
            double szamlalo = jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size() / 2.0; //0,5?

            jatekok[jatek_index].darab[alany_index][esemeny_index]++;
            jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].hanyan++;
            
            jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].aktualis_nyeremeny += sv.tet_osszeg * jatekok[jatek_index].esemenyter[alany_index][esemeny_index][ertek_index].szorzo;

            for (int k = 0; k < jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size(); k++)
            {


                nevezo += ossz / (jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].hanyan); //ez elvileg nem lehet nulla


            }
           
            
            for (int k = 0; k < jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size(); k++)
            {
                
                    jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].szorzo = jatekok[jatek_index].esemenyter[alany_index][esemeny_index].size() / 2.0+(szamlalo / nevezo) * (ossz / jatekok[jatek_index].esemenyter[alany_index][esemeny_index][k].hanyan);
                

            }
            

            
            cout << "A fogadás sikeresen rögzítve lett.\n";
            cin.get();

        }
        else
        {
            cout << "Erre az alany+esemény párra a játékos már fogadott." << endl;
            cin.get();
            
            

        }


    
    //cin.get(); //BEFAGYASZTÁS, HOGY OLVASHATÓ LEGYEN A HIBAÜZENET

}

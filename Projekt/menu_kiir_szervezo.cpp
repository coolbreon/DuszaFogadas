#include "fogadas.h"
void menu_kiir_szervezo(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 4) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
        jatekok.push_back(jatek_csinal());
        cout << "A játék sikeresen rögzítve lett.\n";
        cin.get();
        }
        else if (input == 2)
        {
        if (jatekok.empty())
        {
            cout << "Nincs játék, amelyet le lehetne zárni.\n";
            cin.get();
            cin.get();
        }
        else
        { 
        int i=0;
        while (i<= jatekok.size() && jatekok[i].lezart==true)
            i++;
        if(i<jatekok.size()) 
            jatek_lezarasa(jatekok, fogadasok, pontszamok);
        else
        {
            cout << "Nincs játék, amelyet le lehetne zárni.\n";
            cin.get();
            cin.get();
        }
        }
        }
        else if (input == 3)
            lekerdezesek(pontszamok, fogadasok, jatekok);
            
        system("cls");
        cout << "[1] Játék létrehozása\n";
        cout << "[2] Játék lezárása\n";
        cout << "[3] Lekérdezések\n";
        cout << "[4] Kilépés a főmenübe (Felhasználóváltás)\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}

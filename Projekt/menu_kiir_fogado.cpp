#include "fogadas.h"
void menu_kiir_fogado(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 3) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            int i=0;
            while (i<jatekok.size() && jatekok[i].lezart==true)
                i++;
            if (i<jatekok.size())
            {
            fogadas_csinal(pontszamok, fogadasok, jatekok);
            }
            else 
            {
                cout << "Nincs játék, amelyre fogadni lehetne." << endl;
                cin.get(); cin.get();
            }
        }
        else if (input==2)
           lekerdezesek(pontszamok, fogadasok, jatekok);




        system("cls");
        cout << "[1] Fogadás létrehozása\n";
        cout << "[2] Lekérdezések\n";
        cout << "[3] Kilépés a főmenübe (Felhasználóváltás)\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}

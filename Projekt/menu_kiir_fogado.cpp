#include "fogadas.h"
void menu_kiir_fogado(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 2) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            int i=0;
            while (jatekok[i].lezart)
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



        system("cls");
        cout << "[1] Fogadás létrehozása\n";
        cout << "[2] Kilépés a főmenübe (Felhasználóváltás)\n";

        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}
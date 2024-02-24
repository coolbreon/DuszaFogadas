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
        jatek_lezarasa(jatekok, fogadasok, pontszamok);
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

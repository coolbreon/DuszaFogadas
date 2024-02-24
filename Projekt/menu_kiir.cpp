#include "fogadas.h"
void menu_kiir(vector<Jatek>& jatekok, vector<Fogadas>& fogadasok, vector<Nevek>& pontszamok)
{
    int input = 0;
    while (input != 3) //ADDIG LÉPÜNK VISSZA A MENÜBE, AMÍG NEM A KILÉPÉSRE NYOMUNK
    {
        if (input == 1)
        {
            menu_kiir_fogado(jatekok, fogadasok, pontszamok);

        }
        else if (input == 2) //itt
            menu_kiir_szervezo(jatekok, fogadasok, pontszamok);


        system("cls");
        cout << "Kérem válasszon egy felhasználó típust: \n";
        cout << "[1] Fogadó\n";
        cout << "[2] Szervező\n";
        cout << "[3] Kilépés\n";
        cout << "Válasszon menüpontot: ";
        cin >> input;
    }
}